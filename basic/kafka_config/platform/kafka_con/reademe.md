# ------start multiple zookeeper---------
# server1
./zookeeper-server-start.sh ../config/zookeeper.properties
# server2
./zookeeper-server-start.sh ../config/zookeeper.properties
# server3
./zookeeper-server-start.sh ../config/zookeeper.properties
# - put a myid file under dataDir with id
"""
touch myid
echo "1" > myid
"""

# ------start multiple kafka server---------
# server1
bin/kafka-server-start.sh    config/server-1.properties
# server2
bin/kafka-server-start.sh    config/server-2.properties
# server3
bin/kafka-server-start.sh    config/server-3.properties


# -------Create Topic--------
"""
set topic replic and partition
"""
./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test


# --------Produce messages-------
"""
enable key and separator between key|value
"""
./kafka-console-producer.bat  --broker-list localhost:9092 --topic test  --property parse.key=true --property key.separator=*

# -------Consume messages-----
"""
group consumer is usefull
"""
./kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic group_message --group my-console-client --property print.key=true  --property print.timestamp=true 
./kafka-consumer-groups.bat --bootstrap-server localhost:9092  --group my-console-client  --topic group_message  --reset-offsets --to-earliest
