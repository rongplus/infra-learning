# mongo-spark-test.py
from pyspark.sql import SparkSession
# Create Spark Session
spark = SparkSession \
    .builder \
    .appName("myApp") \
    .config("spark.mongodb.input.uri", "mongodb://127.0.0.1:27017/RongFirst.First") \
    .config("spark.mongodb.output.uri", "mongodb://127.0.0.1:27017/RongFirst.First111") \
    .getOrCreate()
# Read from MongoDB
df = spark.read.format("mongo").load()
df.show()
