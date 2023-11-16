 /*simple.cpp*/
 #include <mysql.h>
  
 extern "C" long long simple_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
 {
     int a = *((long long *)args->args[0]);
      int b = *((long long *)args->args[1]);
      return a + b;
 }
 
extern "C" my_bool simple_add_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
     return 0;
}

//canal，译意为水道/管道/沟渠，主要用途是基于 MySQL 数据库增量日志解析，提供增量数据订阅和消费。