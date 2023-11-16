static void do_test_empty_topic_consumer () {
  std::string errstr;
  std::string topic = Test::mk_topic_name("0067_empty_topic", 1);
  const int32_t partition = 0;

  RdKafka::Conf *conf;

  Test::conf_init(&conf, NULL, 0);

  /* Create simple consumer */
  RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
  if (!consumer)
          Test::Fail("Failed to create Consumer: " + errstr);

  RdKafka::Topic *rkt = RdKafka::Topic::create(consumer, topic, NULL, errstr);
  if (!rkt)
          Test::Fail("Simple Topic failed: " + errstr);


  /* Create the topic through a metadata request. */
  Test::Say("Creating empty topic " + topic + "\n");
  RdKafka::Metadata *md;
  RdKafka::ErrorCode err = consumer->metadata(false, rkt, &md,
                                              tmout_multip(10*1000));
  if (err)
          Test::Fail("Failed to create topic " + topic + ": " + RdKafka::err2str(err));
  delete md;

  /* Start consumer */
  err = consumer->start(rkt, partition, RdKafka::Topic::OFFSET_BEGINNING);
  if (err)
          Test::Fail("Consume start() failed: " + RdKafka::err2str(err));

  /* Consume using legacy consumer, should give an EOF and nothing else. */
  Test::Say("Simple Consumer: consuming\n");
  RdKafka::Message *msg = consumer->consume(rkt, partition,
                                            tmout_multip(10 * 1000));
  if (msg->err() != RdKafka::ERR__PARTITION_EOF)
          Test::Fail("Simple consume() expected EOF, got " + RdKafka::err2str(msg->err()));
  delete msg;

  /* Nothing else should come now, just a consume() timeout */
  msg = consumer->consume(rkt, partition, 1 * 1000);
  if (msg->err() != RdKafka::ERR__TIMED_OUT)
          Test::Fail("Simple consume() expected timeout, got " + RdKafka::err2str(msg->err()));
  delete msg;

  consumer->stop(rkt, partition);

  delete rkt;
  delete consumer;


  /*
   * Now do the same thing using the high-level KafkaConsumer.
   */

  Test::conf_set(conf, "group.id", topic);

  RdKafka::KafkaConsumer *kconsumer = RdKafka::KafkaConsumer::create(conf, errstr);
  if (!kconsumer)
          Test::Fail("Failed to create KafkaConsumer: " + errstr);

  std::vector<RdKafka::TopicPartition*> part;
  part.push_back(RdKafka::TopicPartition::create(topic, partition));

  err = kconsumer->assign(part);
  if (err)
          Test::Fail("assign() failed: " + RdKafka::err2str(err));

  RdKafka::TopicPartition::destroy(part);

  Test::Say("KafkaConsumer: consuming\n");
  msg = kconsumer->consume(tmout_multip(5 * 1000));
  if (msg->err() != RdKafka::ERR__PARTITION_EOF)
          Test::Fail("KafkaConsumer consume() expected EOF, got " + RdKafka::err2str(msg->err()));
  delete msg;

  /* Nothing else should come now, just a consume() timeout */
  msg = kconsumer->consume(1 * 1000);
  if (msg->err() != RdKafka::ERR__TIMED_OUT)
          Test::Fail("KafkaConsumer consume() expected timeout, got " + RdKafka::err2str(msg->err()));
  delete msg;

  kconsumer->close();

  delete kconsumer;
  delete conf;
}