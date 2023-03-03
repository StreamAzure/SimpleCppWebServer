#pragma once
#include<map>

class EventLoop;
class Socket;
class Acceptor;
class Connection;
class Server{
private:
    EventLoop *loop; // 事件循环
    Acceptor *acceptor; // 处理请求：客户端发起连接
    std::map<int, Connection*> connections; //保存所有TCP连接的map
public:
    Server(EventLoop*);
    ~Server();
    void newConnection(Socket *sock);  // 新建TCP连接
    void deleteConnection(Socket *sock); // 断开TCP连接
};