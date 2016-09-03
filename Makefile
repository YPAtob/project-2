CC=gcc
CPPFLAGS=-I./include
CFLAGS=-Wall 
LIBS= 

#找到当前目录下所有的.c文件
src = $(wildcard *.c)

#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))

fdfs_test=fdfs_test
test=test

target=$(fdfs_test) $(test)

ALL:$(target)

#生成所有的.o文件
$(obj):%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 

#test
$(test): test_main.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

#fdfs_test
$(fdfs_test): fdfs_client_test.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

#clean指令

clean:
	-rm -rf $(obj) $(target)

distclean:
	-rm -rf $(obj) $(target)

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
