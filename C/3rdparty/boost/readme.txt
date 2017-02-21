1. Install Boost C++ Libraries 

	tar xvfz boost_1_53_0.tar.gz 
	cd boost_1_53_0 
	./bootstrap.sh 
	./b2 

2. Modify ~/.bashrc to include the following 

	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/user/Development/include/boost_1_453_0/stage/lib 
	source ~/.bashrc
