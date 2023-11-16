from pyspark.sql import SparkSession
from pyspark import SparkContext, SparkConf
import pandas as pd
import findspark
findspark.init()
# Creating a spark context class
sc = SparkContext()
# Creating a spark session
spark = SparkSession.builder.appName(
    "Python Spark DataFrames basic example").getOrCreate()
