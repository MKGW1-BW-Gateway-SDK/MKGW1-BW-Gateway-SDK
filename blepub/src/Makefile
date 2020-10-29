PROGRAM := blepub
LIBS := -lmosquitto -lssl -lcrypto -ldl -lpthread -losapi -lcrypt -luci -ljson-c -lubox -liw -lm -lrt 
INS:=-I../ins -I../inc
LIB_PATH:=-L../lib
export STAGING_DIR:=
CROSS_COMPILE := mipsel-openwrt-linux-uclibc-
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar

SRCS := $(wildcard *.c) 
OBJS := $(patsubst %.c,%.o,$(SRCS))
.PHONY: clean

$(PROGRAM): $(OBJS) 
	$(CC) $(LIB_PATH) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(INS)

clean:
	rm *.o $(PROGRAM) -f

