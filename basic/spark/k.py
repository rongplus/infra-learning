# Subscribe to 1 topic
from pyspark.sql import SparkSession
from pyspark.sql.functions import explode
from pyspark.sql.functions import split

spark = SparkSession \
    .builder \
    .appName("StructuredNetworkWordCount") \
    .getOrCreate()


df = spark \
    .readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "host1:port1,host2:port2") \
    .option("subscribe", "topic1") \
    .load()
df.selectExpr("CAST(key AS STRING)", "CAST(value AS STRING)")

# Subscribe to 1 topic, with headers
df = spark \
    .readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "host1:port1,host2:port2") \
    .option("subscribe", "topic1") \
    .option("includeHeaders", "true") \
    .load()
df.selectExpr("CAST(key AS STRING)", "CAST(value AS STRING)", "headers")

# Subscribe to multiple topics
df = spark \
    .readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "host1:port1,host2:port2") \
    .option("subscribe", "topic1,topic2") \
    .load()
df.selectExpr("CAST(key AS STRING)", "CAST(value AS STRING)")

# Subscribe to a pattern
df = spark \
    .readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "host1:port1,host2:port2") \
    .option("subscribePattern", "topic.*") \
    .load()
df.selectExpr("CAST(key AS STRING)", "CAST(value AS STRING)")
