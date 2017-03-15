#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "make_log.h"
#include "redis_op.h"

#define REDIS_OP_MODULE "test"
#define REDIS_OP_PROC "redis_op"

int main()
{
	redisContext *conn = NULL;
	int retn=0;
	conn=rop_connectdb_nopwd("127.0.0.1","6379");
	if(conn==NULL)
	{
			printf("set error");
		LOG(REDIS_OP_MODULE,REDIS_OP_PROC,"CONN ERROR");
		goto END;
	}
	retn=rop_set_string(conn,"itcast","nihao");
	if(retn!=0)
	{
		printf("set error");
		goto END;
	}
	char value[VALUES_ID_SIZE] = {0};
	retn=rop_get_string( conn, "itcast",value);
	if(retn!=0)
	{
		printf("set error");
		goto END;
	}
	printf("get string:%s\n",value);
	
	int count=5;
	RVALUES values;
	int len=0;
	values=malloc(count*1024);
	retn=rop_range_list(conn, "tsmc", 0, count-1, values, &len);
	if(retn!=0)
	{
		printf("set error");
		goto END;
	}
	int i=0;
	for(i=0;i<len;++i)
	{
		printf("lrange:%d %s\n",i,values[i]);
	}
	
	retn=rop_set_hash(conn, "smic","product", "esme ");
	if(retn!=0)
	{
		printf("set error");
		goto END;
	}
	char str[1024]={0};
	retn=rop_get_hash(conn, "smic","product", str);
	if(retn!=0)
	{
		printf("hmget error");
		goto END;
	}

	 printf("hash get:%s\n",str);
	 
	END:
		if(conn!=NULL)
		{
			rop_disconnect(conn);
		}
	return 0;
}