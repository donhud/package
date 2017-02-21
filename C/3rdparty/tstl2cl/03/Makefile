TARGET=test
#TARGET=client

CFLAGS=-g -I./  -I../tstl2cl-1.0/include
LIBS= -L../tstl2cl-1.0 -ltstl2cl

OBJS= test.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)



