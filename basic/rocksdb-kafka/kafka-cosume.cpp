#include <iostream>
#include <string>
#include <list>
#include <stdint.h>
#include <D:\3rdLib\librdkafka\src-cpp\rdkafkacpp.h>

static bool run = true;
static bool exit_eof = false;

void dump_config(RdKafka::Conf* conf) {
    std::list<std::string> *dump = conf->dump();

    printf("config dump(%d):\n", (int32_t)dump->size());
    for (auto it = dump->begin(); it != dump->end(); ) {
        std::string name = *it++;
        std::string value = *it++;
        printf("%s = %s\n", name.c_str(), value.c_str());
    }

    printf("---------------------------------------------\n");
}

class my_event_cb : public RdKafka::EventCb {
public:
    void event_cb(RdKafka::Event &event) override {
        switch (event.type())
        {
        case RdKafka::Event::EVENT_ERROR:
            std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
                event.str() << std::endl;
            if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
                run = false;
            break;

        case RdKafka::Event::EVENT_STATS:
            std::cerr << "\"STATS\": " << event.str() << std::endl;
            break;

        case RdKafka::Event::EVENT_LOG:
            fprintf(stderr, "LOG-%i-%s: %s\n",
                event.severity(), event.fac().c_str(), event.str().c_str());
            break;

        default:
            std::cerr << "EVENT " << event.type() <<
                " (" << RdKafka::err2str(event.err()) << "): " <<
                event.str() << std::endl;
            break;
        }
    }
};

class my_hash_partitioner_cb : public RdKafka::PartitionerCb {
public:
    int32_t partitioner_cb(const RdKafka::Topic *topic, const std::string *key,
        int32_t partition_cnt, void *msg_opaque) override {
        return djb_hash(key->c_str(), key->size()) % partition_cnt;
    }
private:
    static inline unsigned int djb_hash(const char *str, size_t len) {
        unsigned int hash = 5381;
        for (size_t i = 0; i < len; i++)
            hash = ((hash << 5) + hash) + str[i];
        return hash;
    }
};

namespace consumer_ts
{
void msg_consume(RdKafka::Message* message, void* opaque)
{
    switch (message->err())
    {
    case RdKafka::ERR__TIMED_OUT:
        break;

    case RdKafka::ERR_NO_ERROR:
        /* Real message */
        std::cout << "Read msg at offset " << message->offset() << std::endl;
        if (message->key())
        {
            std::cout << "Key: " << *message->key() << std::endl;
        }
        printf("%.*s\n", static_cast<int>(message->len()), static_cast<const char *>(message->payload()));
        break;
    case RdKafka::ERR__PARTITION_EOF:
        /* Last message */
        if (exit_eof)
        {
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

class my_consumer_cb : public RdKafka::ConsumeCb {
public:
    void consume_cb(RdKafka::Message &msg, void *opaque) override
    {
        msg_consume(&msg, opaque);
    }
};

void consumer_test() {
    printf("conumer test\n");

    int32_t partition = RdKafka::Topic::PARTITION_UA;

    printf("input brokers list(127.0.0.1:9092;127.0.0.1:9093;127.0.0.1:9094):\n");
    std::string broker_list;

    //std::cin >> broker_list;
    broker_list = "127.0.0.1:9092";

    printf("inpute partition:");

    //std::cin >> partition;
    partition = 0;

    // config 
    RdKafka::Conf* global_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf* topic_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    my_hash_partitioner_cb          hash_partitioner;
    my_event_cb                     event_cb;
    my_consumer_cb                  consume_cb;

    int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING;

    std::string err_string;
    if (topic_conf->set("partitioner_cb", &hash_partitioner, err_string) != RdKafka::Conf::CONF_OK){
        printf("set partitioner_cb error: %s\n", err_string.c_str());
        return;
    }

    global_conf->set("metadata.broker.list", broker_list, err_string);
    global_conf->set("event_cb", &event_cb, err_string);
    //global_conf->set("debug", "all", err_string);
    //global_conf->set("debug", "topic,msg", err_string);
    //global_conf->set("debug", "topic,msg,queue", err_string);

    dump_config(global_conf);
    dump_config(topic_conf);

    // create consumer
    RdKafka::Consumer* consumer = RdKafka::Consumer::create(global_conf, err_string);
    if (!consumer) {
        printf("failed to create consumer, %s\n", err_string.c_str());
        return;
    }

    printf("created consumer %s\n", consumer->name().c_str());

    // create topic
    printf("input topic name:\n");

    std::string topic_name;
    std::cin >> topic_name;

    RdKafka::Topic* topic = RdKafka::Topic::create(consumer, topic_name, topic_conf, err_string);
    if (!topic) {
        printf("try create topic[%s] failed, %s\n", topic_name.c_str(), err_string.c_str());
        return;
    }

    // Start consumer for topic+partition at start offset
    RdKafka::ErrorCode resp = consumer->start(topic, partition, start_offset);
    if (resp != RdKafka::ERR_NO_ERROR) {
        printf("Failed to start consumer: %s\n", 
            RdKafka::err2str(resp).c_str());
        return;
    }

    int use_ccb = 0;
    while (run) {
        //consumer->consume_callback(topic, partition, 1000, &consume_cb, &use_ccb);
        //consumer->poll(0);

        RdKafka::Message *msg = consumer->consume(topic, partition, 2000);
        msg_consume(msg, NULL);
        delete msg;
    }

    // stop consumer
    consumer->stop(topic, partition);
    consumer->poll(1000);

    delete topic;
    delete consumer;
}
};


int main()
{
    return 0;
}