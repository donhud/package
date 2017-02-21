TARGET=client

CFLAGS=-g -I/root/3rdparty_libevent/include 
LIBS=-L/root/3rdparty_libevent/lib -levent 

OBJS=main.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LIBS) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -f $(TARGET) $(OBJS)



