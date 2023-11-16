#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include <algorithm>
#include <mutex>
#include <thread>

#include <D:\3rdLib\librdkafka\src-cpp\rdkafkacpp.h>

static bool run = true;
static bool exit_eof = true;
static int eof_cnt = 0;
static int partition_cnt = 0;
static int verbosity = 1;
static long msg_cnt = 0;
static int64_t msg_bytes = 0;

static void sigterm(int sig) { run = false; }

void deal_msg(const char *msg) { printf("rong  %s\n", msg); }

class ExampleEventCb : public RdKafka::EventCb {
public:
  void event_cb(RdKafka::Event &event) {
    switch (event.type()) {
    case RdKafka::Event::EVENT_ERROR:
      std::cerr << "ERROR (" << RdKafka::err2str(event.err())
                << "): " << event.str() << std::endl;
      if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
        run = false;
      break;

    case RdKafka::Event::EVENT_STATS:
      std::cerr << "\"STATS\": " << event.str() << std::endl;
      break;

    case RdKafka::Event::EVENT_LOG:
      fprintf(stderr, "LOG-%i-%s: %s\n", event.severity(), event.fac().c_str(),
              event.str().c_str());
      break;

    case RdKafka::Event::EVENT_THROTTLE:
      std::cerr << "THROTTLED: " << event.throttle_time() << "ms by "
                << event.broker_name() << " id " << (int)event.broker_id()
                << std::endl;
      break;

    default:
      std::cerr << "EVENT " << event.type() << " ("
                << RdKafka::err2str(event.err()) << "): " << event.str()
                << std::endl;
      break;
    }
  }
};

void msg_consume(RdKafka::Message *message, void *opaque) {
  // std::cout << "===msg ===" << std::endl;
  switch (message->err()) {
  case RdKafka::ERR__TIMED_OUT:
    std::cerr << "=====RdKafka::ERR__TIMED_OUT======" << std::endl;
    break;

  case RdKafka::ERR_NO_ERROR:
    /* Real message */
    msg_cnt++;
    msg_bytes += message->len();
    if (verbosity >= 3)
      std::cerr << "Read msg at offset " << message->offset() << std::endl;
    RdKafka::MessageTimestamp ts;
    ts = message->timestamp();
    if (verbosity >= 2 &&
        ts.type != RdKafka::MessageTimestamp::MSG_TIMESTAMP_NOT_AVAILABLE) {
      std::string tsname = "?";
      if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
        tsname = "create time";
      else if (ts.type ==
               RdKafka::MessageTimestamp::MSG_TIMESTAMP_LOG_APPEND_TIME)
        tsname = "log append time";
      std::cout << "Timestamp: " << tsname << " " << ts.timestamp << std::endl;
    }
    std::cout << verbosity << "---" << message->key() << std::endl;
    if (verbosity >= 2 && message->key()) {
      std::cout << "Key: " << *message->key() << std::endl;
    }
    if (verbosity >= 1) {
      std::cout << "Timestamp: "
                << " " << ts.timestamp << std::endl;
      printf("rong %d.%s\n", static_cast<int>(message->len()),
             static_cast<const char *>(message->payload()));
      if (message->key())
        std::cout << "Key: " << *message->key() << std::endl;
    }
    break;

  case RdKafka::ERR__PARTITION_EOF:
    /* Last message */
    if (exit_eof && ++eof_cnt == partition_cnt) {
      std::cerr << "%% EOF reached for all " << partition_cnt << " partition(s)"
                << std::endl;
      run = false;
    }
    break;

  case RdKafka::ERR__UNKNOWN_TOPIC:
  case RdKafka::ERR__UNKNOWN_PARTITION:
    std::cerr << "Consume failed: " << message->errstr() << std::endl;
    run = false;
    break;

  default:
    /* Errors */
    std::cerr << "Consume failed: " << message->errstr() << std::endl;
    run = false;
  }
}

class ExampleConsumeCb : public RdKafka::ConsumeCb {
public:
  void rebalance_cb(RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
                    std::vector<RdKafka::TopicPartition *> &partitions) {
    if (err == RdKafka::ERR__ASSIGN_PARTITIONS) {
      RdKafka::TopicPartition *part;
      // find the partition, through std::find() or other means
      if (part)
        part->set_offset(1234);
      consumer->assign(partitions);
    } else {
      consumer->unassign();
    }
  }
  void consume_cb(RdKafka::Message &msg, void *opaque) {
    msg_consume(&msg, opaque);
  }
};

int main() {
  std::string brokers = "localhost";
  std::string errstr;
  std::string topic_str = "test123";
  std::vector<std::string> topics;
  std::string group_id = "101";

  int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING;

  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
  // group.id必须设置
  if (conf->set("group.id", group_id, errstr) != RdKafka::Conf::CONF_OK) {
    std::cerr << errstr << std::endl;
    exit(1);
  }

  topics.push_back(topic_str);
  topics.push_back("test");
  // bootstrap.servers可以替换为metadata.broker.list
  conf->set("bootstrap.servers", brokers, errstr);
  // 设置 key

  // if (conf->set("parse.key", "true", errstr) != RdKafka::Conf::CONF_OK) {
  //   std::cerr << errstr << std::endl;
  //   exit(1);
  // }
  // if (conf->set("key.separator", "*", errstr) != RdKafka::Conf::CONF_OK) {
  //   std::cerr << errstr << std::endl;
  //   exit(1);
  // }

  ExampleConsumeCb ex_consume_cb;
  conf->set("consume_cb", &ex_consume_cb, errstr);
  ExampleEventCb ex_event_cb;
  conf->set("event_cb", &ex_event_cb, errstr);
  conf->set("default_topic_conf", tconf, errstr);
  // todo);

  signal(SIGINT, sigterm);
  signal(SIGTERM, sigterm);

  RdKafka::KafkaConsumer *consumer =
      RdKafka::KafkaConsumer::create(conf, errstr);
  // consumer->seek(consumer->assignment());
  if (!consumer) {
    std::cerr << "Failed to create consumer: " << errstr << std::endl;
    exit(1);
  }
  std::cout << "% Created consumer " << consumer->name() << std::endl;

  // set offset
  std::vector<RdKafka::TopicPartition *> partitions;
  partitions.push_back(RdKafka::TopicPartition::create("mytopic", 3, 1234));
  consumer->assign(partitions);

  RdKafka::ErrorCode err = consumer->subscribe(topics);
  if (err) {
    std::cerr << "Failed to subscribe to " << topics.size()
              << " topics: " << RdKafka::err2str(err) << std::endl;
    exit(1);
  }

  while (run) {
    // 5000毫秒未订阅到消息，触发RdKafka::ERR__TIMED_OUT
    RdKafka::Message *msg = consumer->consume(5000);
    msg_consume(msg, NULL);
    delete msg;
  }

  consumer->close();

  delete conf;
  delete tconf;
  delete consumer;

  std::cerr << "% Consumed " << msg_cnt << " messages (" << msg_bytes
            << " bytes)" << std::endl;

  //应用退出之前等待rdkafka清理资源
  RdKafka::wait_destroyed(5000);

  return 0;
}