




----Start multi zookeeper---
     myid file is needed in dataDir=/home/ron/work/log/zk. 
     server id only in myid file. in 192.168.1.118, myid=1
     other myid = 2
     
 - 1 --ubuntu_dev----
    ./zookeeper-server-start.sh ../config/zookeeper.properties

 - 2 ----windows-------
    .\zookeeper-server-start.bat ..\..\config\zookeeper1.properties

----Start multi kafka----
 - 1 --ubuntu_dev----
    ./kafka-server-start.sh ../config/server.properties
 - 2 ----windows-------
    .\kafka-server-start.bat ../../config/server1.properties
    .\kafka-server-start.bat ../../config/server2.properties
    .\kafka-server-start.bat ../../config/server3.properties
    [files](D:\kafka\kafka_2.12-2.4.0\config)

----create topic
    ./kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
----Check topic----
    ./kafka-topics.sh --list --zookeeper localhost:2181 
----produce
    ./kafka-console-producer.bat  --broker-list 192.168.1.118:9092 --topic test123  --property parse.key=true --property key.separator=*   

----consumer
    ./kafka-console-consumer.bat --bootstrap-server 192.168.1.118:9092 --topic test123 --from-beginning
    ./kafka-console-consumer.sh --bootstrap-server 192.168.1.118:9092 --topic some-topic --from-beginning
    ./kafka-console-consumer.sh --bootstrap-server 192.168.135.133:9092 --topic some-topic --from-beginning

----group consumer
    ./kafka-consumer-groups.bat --bootstrap-server localhost:9092  --group my-console-client  --topic group_message  --reset-offsets --to-earliest

    


