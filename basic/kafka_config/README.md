g++ -std=c++11 -o rocksdbtest.cpp rocksdbtest -lpthread -lrocksdb


add myid to zookeeper's dataDir

```
  - Linux/MacOS
  cd ..
      cd kafka/bin/
  1, open zookeeper:
   ./zookeeper-server-start.sh ../config/zookeeper.properties
  2, open kafka
    ./kafka-server-start.sh ../config/server.properties 
  3 Create topic 
   ./kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
   ./kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test123
   ./kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test456
  4, check topics
   ./kafka-topics.sh --list --zookeeper localhost:2181 
  5, create logs
    ./kafka-console-producer.sh  --broker-list localhost:9092 --topic test
  6, consumer logs
    ./kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test --from-beginning
  7, ./kafka-console-producer.sh  --broker-list localhost:9092 --topic dev_log  --property parse.key=true --property key.separator=:

```

```
  - Windows---
  cd D:\kafka-l\kafka_2.12-2.4.0\bin\windows
      cd kafka/bin/
  1, open zookeeper:
   ./zookeeper-server-start.bat ../../config/zookeeper.properties
  2, open kafka
    ./kafka-server-start.bat ../../config/server.properties 
  3 Create topic 
   ./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test

  4, check topics
   ./kafka-topics.sh --list --zookeeper localhost:2181 
  5, create logs
    ./kafka-console-producer.bat  --broker-list localhost:9092 --topic test
  6, consumer logs
    ./kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic test --from-beginning
  7, ./kafka-console-producer.bat  --broker-list localhost:9092 --topic test  --property parse.key=true --property key.separator=*

```


```
  cd ..
      cd kafka/bin/windows
  1, open zookeeper:
   ./zookeeper-server-start.bat ../../config/zookeeper.properties
  2, open kafka
    ./kafka-server-start.bat ../../config/server.properties 
  3 Create topic 
   ./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
   ./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test123
   ./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test456
  4, check topics
   ./kafka-topics.bat --list --zookeeper localhost:2181 
  5, create logs
    ./kafka-console-producer.bat  --broker-list localhost:9092 --topic test
  6, consumer logs
    ./kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic test --from-beginning

  7, kafka-console-consumer --bootstrap-server localhost:9092 --topic some-topic --formatter kafka.tools.DefaultMessageFormatter --property print.timestamp=true --property print.key=true --property print.value=true
  8, ./kafka-console-producer.bat  --broker-list localhost:9092 --topic test  --property parse.key=true --property key.separator=*

  9, ./kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic group_message --group my-console-client --property print.key=true  --property print.timestamp=true 
  10, ./kafka-consumer-groups.bat --bootstrap-server localhost:9092  --group my-console-client  --topic group_message  --reset-offsets --to-earliest
  11,kafka-topics.sh --describe --zookeeper localhost:2181 --topic my-topic
  12 --partition mypartition --offset myoffset
```
build 
cl kafka-cosume.cpp D:\3rdLib\libs\rdkafka++.lib
cl kafka-consumer_sqlite.cpp  D:\3rdLib\libs\rdkafka++.lib  D:\3rdLib\libs\sqlite3.lib


=====------------------------====
Reset offset of Kafka consumer group.

Preparations
Create sample keep-up-with-topic topic.

$ bin/kafka-topics.sh --bootstrap-server localhost:9092 --create --topic keep-up-with-topic --replication-factor 3 --partitions 5
Created topic keep-up-with-topic.
Display topic details.

$ bin/kafka-topics.sh --bootstrap-server localhost:9092 --describe --topic keep-up-with-topic
Topic: keep-up-with-topic       TopicId: oBWzsfSAQo-63ym7h2Slmw PartitionCount: 5       ReplicationFactor: 3    Configs: segment.bytes=1073741824
        Topic: keep-up-with-topic       Partition: 0    Leader: 1       Replicas: 1,2,3 Isr: 1,2,3
        Topic: keep-up-with-topic       Partition: 1    Leader: 2       Replicas: 2,3,5 Isr: 2,3,5
        Topic: keep-up-with-topic       Partition: 2    Leader: 3       Replicas: 3,5,4 Isr: 3,5,4
        Topic: keep-up-with-topic       Partition: 3    Leader: 5       Replicas: 5,4,1 Isr: 5,4,1
        Topic: keep-up-with-topic       Partition: 4    Leader: 4       Replicas: 4,1,2 Isr: 4,1,2
Publish several messages.

$ echo  "hello_msg: {'who':'$(whoami)','where':'$(hostname)','when':'$(date)'}" | bin/kafka-console-producer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --property parse.key=true --property key.separator=:
Consume these messages.

$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --group my-console-client --property print.key=true  --property print.timestamp=true 
CreateTime:1624655927380        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:18:46 UTC 2021'}
CreateTime:1624655930318        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:18:49 UTC 2021'}
CreateTime:1624656092851        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:21:31 UTC 2021'}
CreateTime:1624656142408        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:21 UTC 2021'}
CreateTime:1624656149136        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:27 UTC 2021'}
CreateTime:1624656159306        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:38 UTC 2021'}
CreateTime:1624656197636        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:16 UTC 2021'}
CreateTime:1624656214769        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:33 UTC 2021'}
CreateTime:1624656217408        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:36 UTC 2021'}
^CProcessed a total of 9 messages
Get the offset
Get the offset for the latest timestamp.

$ bin/kafka-run-class.sh kafka.tools.GetOffsetShell --broker-list localhost:9092 --topic keep-up-with-topic  --time -1
keep-up-with-topic:0:0
keep-up-with-topic:1:0
keep-up-with-topic:2:0
keep-up-with-topic:3:9
keep-up-with-topic:4:0
Get the offset for the earliest timestamp.

kafka@kafka5:~/kafka$ bin/kafka-run-class.sh kafka.tools.GetOffsetShell --broker-list localhost:9092 --topic keep-up-with-topic  --time -2
keep-up-with-topic:0:0
keep-up-with-topic:1:0
keep-up-with-topic:2:0
keep-up-with-topic:3:0
keep-up-with-topic:4:0
Get the offset for the specific timestamp.

$ bin/kafka-run-class.sh kafka.tools.GetOffsetShell --broker-list localhost:9092 --topic keep-up-with-topic  --time 1624656214765
keep-up-with-topic:0:
keep-up-with-topic:1:
keep-up-with-topic:2:
keep-up-with-topic:3:7
keep-up-with-topic:4:
Change the offset
Disconnect the consumer as it needs to be inactive to perform the assignment.

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --group my-console-client  --topic keep-up-with-topic  --reset-offsets --to-earliest
Error: Assignments can only be reset if the group 'my-console-client' is inactive, but the current state is Stable.

GROUP                          TOPIC                          PARTITION  NEW-OFFSET     
The consumer group should not have any active members.

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --describe --group my-console-client
Consumer group 'my-console-client' has no active members.

GROUP             TOPIC              PARTITION  CURRENT-OFFSET  LOG-END-OFFSET  LAG             CONSUMER-ID     HOST            CLIENT-ID
my-console-client keep-up-with-topic 4          0               0               0               -               -               -
my-console-client keep-up-with-topic 2          0               0               0               -               -               -
my-console-client keep-up-with-topic 3          9               9               0               -               -               -
my-console-client keep-up-with-topic 0          0               0               0               -               -               -
my-console-client keep-up-with-topic 1          0               0               0               -               -               -
Change offset to the earliest one.

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --group my-console-client  --topic keep-up-with-topic  --reset-offsets --to-earliest --execute
GROUP                          TOPIC                          PARTITION  NEW-OFFSET     
my-console-client              keep-up-with-topic             3          0              
my-console-client              keep-up-with-topic             2          0              
my-console-client              keep-up-with-topic             0          0              
my-console-client              keep-up-with-topic             4          0              
my-console-client              keep-up-with-topic             1          0    
Consume these messages.

$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --group my-console-client --property print.key=true  --property print.timestamp=true 
CreateTime:1624655927380        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:18:46 UTC 2021'}
CreateTime:1624655930318        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:18:49 UTC 2021'}
CreateTime:1624656092851        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:21:31 UTC 2021'}
CreateTime:1624656142408        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:21 UTC 2021'}
CreateTime:1624656149136        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:27 UTC 2021'}
CreateTime:1624656159306        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:38 UTC 2021'}
CreateTime:1624656197636        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:16 UTC 2021'}
CreateTime:1624656214769        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:33 UTC 2021'}
CreateTime:1624656217408        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:36 UTC 2021'}
^CProcessed a total of 9 messages
Change offset to the latest one.

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --group my-console-client  --topic keep-up-with-topic  --reset-offsets --to-latest --execute
GROUP                          TOPIC                          PARTITION  NEW-OFFSET     
my-console-client              keep-up-with-topic             3          9              
my-console-client              keep-up-with-topic             2          0              
my-console-client              keep-up-with-topic             0          0              
my-console-client              keep-up-with-topic             4          0              
my-console-client              keep-up-with-topic             1          0     
There are no new messages.

$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --group my-console-client --property print.key=true  --property print.timestamp=true 
^CProcessed a total of 0 messages
Change offset to the specific one.

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --group my-console-client  --topic keep-up-with-topic  --reset-offsets --to-offset 7 --execute
[2021-06-25 21:37:31,190] WARN New offset (7) is higher than latest offset for topic partition keep-up-with-topic-2. Value will be set to 0 (kafka.admin.ConsumerGroupCommand$)
[2021-06-25 21:37:31,191] WARN New offset (7) is higher than latest offset for topic partition keep-up-with-topic-0. Value will be set to 0 (kafka.admin.ConsumerGroupCommand$)
[2021-06-25 21:37:31,191] WARN New offset (7) is higher than latest offset for topic partition keep-up-with-topic-4. Value will be set to 0 (kafka.admin.ConsumerGroupCommand$)
[2021-06-25 21:37:31,191] WARN New offset (7) is higher than latest offset for topic partition keep-up-with-topic-1. Value will be set to 0 (kafka.admin.ConsumerGroupCommand$)

GROUP                          TOPIC                          PARTITION  NEW-OFFSET     
my-console-client              keep-up-with-topic             3          7              
my-console-client              keep-up-with-topic             2          0              
my-console-client              keep-up-with-topic             0          0              
my-console-client              keep-up-with-topic             4          0              
my-console-client              keep-up-with-topic             1          0    
Consume these messages.

$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --group my-console-client --property print.key=true  --property print.timestamp=true 
CreateTime:1624656214769        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:33 UTC 2021'}
CreateTime:1624656217408        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:36 UTC 2021'}
^CProcessed a total of 2 messages
Change offset to the specific datetime (1624656159306).

$ bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092  --group my-console-client  --topic keep-up-with-topic  --reset-offsets --to-datetime 2021-06-25T21:22:39.306 --execute
GROUP                          TOPIC                          PARTITION  NEW-OFFSET     
my-console-client              keep-up-with-topic             3          5              
my-console-client              keep-up-with-topic             2          0              
my-console-client              keep-up-with-topic             0          0              
my-console-client              keep-up-with-topic             4          0              
my-console-client              keep-up-with-topic             1          0    
Consume these messages.

$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic keep-up-with-topic --group my-console-client --property print.key=true  --property print.timestamp=true 
CreateTime:1624656159306        hello_msg        {'who':'kafka','where':'kafka5.example.org','when':'Fri Jun 25 21:22:38 UTC 2021'}
CreateTime:1624656197636        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:16 UTC 2021'}
CreateTime:1624656214769        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:33 UTC 2021'}
CreateTime:1624656217408        hello_msg        {'who':'kafka','where':'kafka4.example.org','when':'Fri Jun 25 21:23:36 UTC 2021'}
^CProcessed a total of 4 messages
Additional notes
You can also use kafka-streams-application-reset.sh to change current offset.

$ bin/kafka-streams-application-reset.sh --bootstrap-servers localhost:9092 --input-topics keep-up-with-topic --application-id my-console-client --to-earliest
Reset-offsets for input topics [keep-up-with-topic]
Following input topics offsets will be reset to (for consumer group my-console-client)
Topic: keep-up-with-topic Partition: 4 Offset: 0
Topic: keep-up-with-topic Partition: 2 Offset: 0
Topic: keep-up-with-topic Partition: 3 Offset: 0
Topic: keep-up-with-topic Partition: 0 Offset: 0
Topic: keep-up-with-topic Partition: 1 Offset: 0
Done.
Deleting all internal/auto-created topics for application my-console-client
Done.
I won’t repeat each detail here, you can use it to perform every operation described earlier.


hdfs?
  1 Raft
  2 Paxos
  3 2pc
  infra networking 
Data infra


boost combpile
//g++ boost_log.cpp  -L/Users/ronghuang/work/3rd_lib/boost_1_76_0/stage/lib -lboost_log_setup-mt -lboost_log-mt -lboost_thread-mt -lboost_system-mt -DBOOST_LOG_DYN_LINK -o blog


 large scale distributed systems.
 批处理系统


 high availability proxy servere
vitess.io
dynamodb != dynamo



 ./a.out  -g id1 -b 172.17.0.3  dev_log




 Familiar with Redis, Zookeeper, Kafka
Experience working on databases like MSSQL, Postgres or any other relational database