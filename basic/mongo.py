import pymongo

from pymongo import MongoClient

# 服务器的连接有多种方式，一般就是直接使用第一种即可
client = MongoClient()
client = MongoClient('localhost', 27017)
client = MongoClient("mongodb://localhost:27017/")
collection1 = client['RongFirst']  # RongFirst database in mongo'
print(collection1.First.find_one())
cc = collection1.First  # First, table in RongFirst
for i in cc.find():
    print(i)
# -----worked---


list1 = [
    {"姓名": "Mars老师", "职务": "教研负责人"},
    {"姓名": "木森老师", "职务": "助教老师"},
    {"姓名": "栗子老师", "职务": "班主任"}

]
for i in list1:
    posts = collection1.First111
    id = posts.insert_one(i).inserted_id
    print(id)
