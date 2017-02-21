TARGET=test
#TARGET=client

CFLAGS=-g -I./  -I../libjson
LIBS= -L../libjson -ljson

OBJS= test.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LIBS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)



