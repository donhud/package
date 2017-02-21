tar -zxvf libiconv-1.14.tar.gz

mkdir build_out

cd libiconv-1.14

以下可以加： --disable-shared --enable-static
./configure --prefix=/home/darkblue/Github/src/3rdparty/libiconv/build_out

make

make install

