CC=gcc

CFLAGS=-Wall -g -pedantic -pipe -W  -Wpointer-arith -Wno-unused-parameter -Wunused-function -Wunused-variable -Wunused-value -Werror

INCLUDES=-I.

LIBS=

LINKS=

TARGET=jv_properties_main

src=$(wildcard *.c)
dir=$(notdir $(src))
C_OBJS=$(patsubst %.c, %.o,$(dir))
#C_OBJS=$(dir:%.c=%.o)

compile:$(TARGET)
	
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $*.o -c $*.c
	
$(TARGET):$(C_OBJS)
	$(CC) -o $(TARGET) $^ $(LIBS) $(LINKS) 

	@echo 
	@echo Project has been successfully compiled.
	@echo

clean:
	rm -rf $(TARGET) *.depend *.layout bin obj *.o *.stackdump *.exe *.log *~