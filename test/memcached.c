#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <libmemcached/memcached.h> 
int main()
{
	memcached_return rc;
	memcached_st *memc;
	
	memc=memcached_create(NULL);
	memcached_server_st *servers;
	servers=memcached_server_list_append(NULL,(char *)"127.0.0.1",11211,&rc);
	rc=memcached_server_push(memc,servers);
	memcached_server_free(servers);
	rc=memcached_set(memc,"FOO",3,"abcde",5,(time_t)18,(uint32_t)0);
	printf("rc %s\n",memcached_strerror(memc,rc));
	char *m;
	uint32_t n;
	size_t len=5;
	m=memcached_get(memc,"FOO",3,&len,&n,&rc);
	printf("%s\n",m);
	memcached_free(memc);
	return 0;

}