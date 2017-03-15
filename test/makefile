src=$(wildcard ./*.c)
obj=$(patsubst %.c,%.o,$(src))

memcached=memcached
redisapi=redisapi
redis_op_test=redis_op_test

target=$(memcached) $(redisapi) $(redis_op_test)

all:$(target)

$(redisapi):redisapi.o
	gcc $^ -o $@  -lhiredis
	
$(memcached):memcached.o
	gcc $^ -o $@ -lmemcached 

$(redis_op_test):redis_op_test.o make_log.o redis_op.o
	gcc $^ -o $@ -lhiredis
	
$(obj):%.o:%.c
	gcc $< -c -o $@  -I /usr/local/include/hiredis/  -I ../include
.PHONY:clean
clean:
	-rm $(obj) $(target) -f
