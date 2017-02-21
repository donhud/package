TARGET=server

CFLAGS=-g -I../../build_out/include
LIBS=-L../../build_out/lib -levent 

OBJS=main.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LIBS) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -f $(TARGET) $(OBJS)



