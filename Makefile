server:
	g++ src/util.cpp server.cpp src/Epoll.cpp src/InetAddress.cpp src/Socket.cpp src/Channel.cpp src/EventLoop.cpp src/Server.cpp src/Acceptor.cpp -o server

.PHONY : clean
clean:
	rm server