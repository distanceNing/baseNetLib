obj=event_loop.o main.o poller.o channel.o tcp_socket.o

cppstd=-std=c++11

server:$(obj)
	 g++     $(obj) -o server 

main.o:main.cpp

poller.o:poller.cpp
	g++     -c $(cppstd) poller.cpp 

event_loop.o:event_loop.cpp
	g++ 	-c $(cppstd) event_loop.cpp 

channel.o:channel.cpp
	g++ 	-c $(cppstd) channel.cpp

tcp_socket.o:tcp_socket.cpp

clean:
	rm *.o server
