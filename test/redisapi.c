#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

int main(int argc, char **argv) 
{
    redisContext *c;
    redisReply *reply;

    //创建一个客户端连接句柄
    c = redisConnect("127.0.0.1",6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = redisCommand(c,"PING");
    if (reply == NULL) {
        printf("ping error\n");
        printf("error: %s\n", c->errstr);
        goto END;
    }
    printf("PING: %s:len = %d\n", reply->str, (int)reply->len);
    freeReplyObject(reply);

    //set 操作
    reply = redisCommand(c, "SET %s %s", "key12123", "abced");
    if (reply == NULL) {
        printf("set error");
        goto END;
    }
    printf("set succ: %s\n", reply->str);
    freeReplyObject(reply);
    
    reply = redisCommand(c, "GET %s", "key12123");
    if (reply == NULL) {
        printf("set error");
        goto END;
    }
    printf("set succ: %s\n", reply->str);
    freeReplyObject(reply);
    
     reply = redisCommand(c, "LPUSH %s %s %s", "lyc","hello","world");
    if (reply == NULL) {
        printf("set error");
        goto END;
    }
    printf("lpush succ: %lld\n", reply->integer);
    freeReplyObject(reply);
    
    int j=0; 
    reply = redisCommand(c, "LRANGE lyc %d %d",0,-1);
    if(reply->type == REDIS_REPLY_ARRAY) 
    	{
           for (j = 0; j < reply->elements; j++)
            {
               printf("%u %s\n", j, reply->element[j]->str);
           }
         }

    freeReplyObject(reply);
END:

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}