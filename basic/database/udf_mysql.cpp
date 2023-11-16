#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn\connection.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn\sqlstring.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn/resultset.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn/datatype.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn/resultset.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn/resultset_metadata.h"
#include "D:\softwares\MySQL\MySQConnector\include\jdbc\cppconn/exception.h"

using namespace std;

extern "C" {
    char *hello_world (UDF_INIT *initid, UDF_ARGS *args,char *result, unsigned long *length,char *is_null, char *error);
    my_bool hello_world_init (UDF_INIT *initid, UDF_ARGS *args, char *message);
    void hello_world_deinit (UDF_INIT *initid);
    //template <typename T>  T adder (UDF_INIT *initid, UDF_eARGS *args,string result, unsigned long length,string is_null, string error,T v);
}

char *hello_world (UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
    string res;
    res = args->args[0];
    res.append(" hello");
    char *c = new char[res.size()];
    strcpy(c, res.c_str());
    return c;
}

my_bool hello_world_init (UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    return 0;
    //cout<<"success"<<endl;
}

void hello_world_deinit (UDF_INIT *initid)
{
    return;
}