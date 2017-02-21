TARGET=test

#此Makefile主要特点是使用了pkg-config方式获取库的路径等相关信息

#CFLAGS=-g -I../../build_out/include
CFLAGS=-g `pkg-config libwebsockets --cflags`
#LIBS=-L../../build_out/lib -levent 
LIBS= `pkg-config libwebsockets --libs`

OBJS=main.o

all: $(TARGET)
export PKG_CONFIG_PATH=/home/darkblue/Github/src/3rdparty/libwebsockets/build_out/lib64/pkgconfig
#echo 'set evironment value $PKG_CONFIG_PATH'
#echo $(PKG_CONFIG_PATH)

$(TARGET):$(OBJS)
	$(CC) $(LIBS) -o $@ $^
	@echo PKG_CONFIG_PATH = $(PKG_CONFIG_PATH)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -f $(TARGET) $(OBJS)



