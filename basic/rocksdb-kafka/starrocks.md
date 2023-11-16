RTA / StarRocks Sync

July 20th, 2022 4-5pm PT

RTA Team Questions:
Has deploying in Docker been tested? Are there any performance issues when running in Docker?
How can we build from source code? 
Do you only support CentOS? All of our hosts are Ubuntu. (yes support ubuntu, just confirmed with team, releases binary can execute directly on Ubuntu, But the default JDK doesn’t work, should use open JDk or oracle JDk instead)
What is StarRocks roadmap for the future? Any significant features that will be rolled out soon?
Storage questions:
Compared to Druid, does starrocks require more storage space? Is there some data showing the storage space difference? (another reason use less storage in sr is because we don’t need rely on index)
Are there import methods for Druid data migration? 
What is scale limit for the data storage? like, # of tables, data size? 
What will become bottlenecks when data size grows over certain scale? Is FE leader a bottleneck?
Replication / backup:
For backup and restore, is there more advanced tools to help us do WAL backups, point in time recovery, etc.?
How long does it take to recover from a total cluster outage?
Does it support multi-AZ/ cross region replication? 
Network partition:
How does FE survive network partition? What if leader is not with the majority of quorum? 
How does BE survive network partition? 
Consistency:
What consistency do you guarantee on read/write?
CBO: 
How much of system resources does full statistics collection consume and how significant does it affect system performance? 
Is there some way to perform the collection from separate host that doesn’t affect system performance?  
Optimization
Select sum(*) from table where id = 123, if 123 accounts for 80% of the data, do we have optimizations to address these use cases?
Multiple group by columns performance degradation
Scattered timestamps in ingestion, will it affect already compacted segments? Do we have continuous compaction?

Notes:
Druid at Pinterest
Gaps/Pain Points
Less efficient, had to add a lot of capabilities
Onboarding use cases, difficult to meet SLA
Pipeline
Batch
S3
Mostly parquet
Spark, SparkSQL
500GB/day
Streaming
Kafka
JSON
Flink
Write QPS ~500k
Usually ingestion is owned by client, many different sources
All denormalized tables
Want
100-200ms, 1000QPS
Action item on StarRocks side - compile source code directly, Ubuntu
Storage compared with Druid
Use less storage
Data compaction is better
Suggest 3 replicas
If each BE has one replica, makes joins faster
MVs take up more storage
At AirBnB, use < 100 instances to replace 200-300 Druid instances, storage cost is less
StarRocks benchmark testing: https://starrocks.medium.com/starrocks-outperforms-clickhouse-apache-druid-and-trino-with-excellent-wide-table-and-multi-table-68d101ea4462
Druid data migration
Can probably provide provide migration tools, will ask community
In S3, but would be best to have a connector to extract data directly
Scale limit - production testing
Over 100,000 tables?
No limitation for data size
Biggest cluster (WeChat), about 110 servers in one cluster and keep increasing
Current bottleneck = compaction
When data size increases, need good configurations for partition size, number of tablets in partition (suggest 1GB - 2GB tablet size)
Will affect data ingestion speed
Is the FE leader a bottleneck? 
Replication/backup
HA deployment across availability zones and data centers
Replicas across zones + centers
Clients have not had full total cluster outage
Can recover if you have enough replicas
Network partitions
Paxos algorithm on FE and BE
If you lost all FE, can use CLI to find the most updated FE to use as a leader and rest will sync
Required user interaction
1 replica down, can still read + write
2 replicas down, can read but not write
On Druid, even if cluster down, can still write
If the cluster is not available, can Spark job generate data that is picked up later?
Not supported right now
Can store in S3, Kafka then ingest later
Routine load will load automatically once back up
When StarRocks cluster is down, we do not want to block clients
Consistency
Routine Load: exactly once
Stream Load: if system can guarantee at least once, StarRocks can guarantee exactly once (through label)
CBO will optimize 2-3x times
Full statistics collection will not significantly affect system performance
If you find that it does, you can configure to use just a sample for the CBO
Skewed data use case - We have optimization so that even when partition by id, it can be spread across multiple shards so that it is even
Partition layer and bucket layer 
Can set hash based on multiple columns
Can give sample of data and test together
In Druid, cannot add new data to already compacted segments
Want to compact immediately - StarRocks can do incremental compaction
