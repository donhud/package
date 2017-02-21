TARGET=test
#TARGET=client

CFLAGS=-g -I./  -I../../libcstl-2.3.0/
LIBS= -L../../libcstl-2.3.0/src/.libs -lcstl

OBJS= test.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)



