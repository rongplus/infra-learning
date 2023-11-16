from pyspark.sql import SparkSession
from pyspark import SparkContext, SparkConf
import pandas as pd
import findspark
findspark.init()
# Creating a spark context class
sc = SparkContext()
# Creating a spark session
spark = SparkSession.builder.appName("Python Spark DataFrames basic example").config(
    "spark.some.config.option", "RongTest").getOrCreate()

print("Step 1")
# Reading the file using `read_csv` function in pandas
mtcars = pd.read_csv(
    'D:/Dowdload2022/mtcars.csv')
print(mtcars.head())
mtcars.rename(columns={'Unnamed: 0': 'name'}, inplace=True)
print(mtcars.head())
print("Step 2")
sdf = spark.createDataFrame(mtcars)
print("step 3")
sdf.createTempView("cars")
spark.sql("SELECT * FROM cars").show()
