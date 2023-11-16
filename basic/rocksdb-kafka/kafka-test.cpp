// kafka_test_win32_nomfc.cpp 
// 

#include "stdafx.h" 
#include <iostream> 
#include "librdkafka/rdkafkacpp.h" 


int static producer_1() 
{ 
    std::string brokers = "127.0.0.1"; 
    std::string errstr; 
    std::string topic_str = "linli"; 
    std::string mode; 
    std::string debug; 
    int32_t partition = RdKafka::Topic::PARTITION_UA; 
    int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING; 
    bool do_conf_dump = false; 
    int opt; 
    // MyHashPartitionerCb hash_partitioner; 
    int use_ccb = 0; 

    /* 
    * Create configuration objects 
    */ 
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL); 
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC); 

    conf->set("metadata.broker.list", brokers, errstr); 

    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr); 
    if (!producer) { 
     std::cerr << "Failed to create producer: " << errstr << std::endl; 
     exit(1); 
    } 

    std::cout << "% Created producer " << producer->name() << std::endl; 

    /* 
    * Create topic handle. 
    */ 
    RdKafka::Topic *topic = NULL; 
    if (!topic_str.empty()) { 
     topic = RdKafka::Topic::create(producer, topic_str, tconf, errstr); 
     if (!topic) { 
      std::cerr << "Failed to create topic: " << errstr << std::endl; 
      exit(1); 
     } 
    } 

    RdKafka::ErrorCode resp = producer->produce(topic, partition, 
     RdKafka::Producer::RK_MSG_COPY /* Copy payload */, 
     const_cast<char *>("hello worlf"), 11, 
     NULL, NULL); 

    delete topic; 
    delete producer; 
    return 0; 
} 


int static producer_2() 
{ 
    std::string brokers = "127.0.0.1"; 
    std::string errstr; 
    std::string topic_str = "linli"; 
    std::string mode; 
    std::string debug; 
    int32_t partition = RdKafka::Topic::PARTITION_UA; 
    int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING; 
    bool do_conf_dump = false; 
    int opt; 
    // MyHashPartitionerCb hash_partitioner; 
    int use_ccb = 0; 

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL); 
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC); 

    conf->set("metadata.broker.list", brokers, errstr); 

    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr); 
    if (!producer) { 
     std::cerr << "Failed to create producer: " << errstr << std::endl; 
     exit(1); 
    } 

    std::cout << "% Created producer " << producer->name() << std::endl; 

    RdKafka::ErrorCode resp = producer->produce(topic_str, partition, 
     RdKafka::Producer::RK_MSG_COPY /* Copy payload */, 
     (void *)"hi", 2, 
     NULL, 0, 0, NULL); 



    std::string errs(RdKafka::err2str(resp)); 
    std::cout << errs << std::endl; 
    //producer->poll(0); 


    delete producer; 

    return 0; 
} 


int main() 
{ 

    producer_2(); 

    return 0; 
} 