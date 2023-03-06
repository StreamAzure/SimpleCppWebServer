#pragma once
#include <functional>
#include <map>
#include <vector>

class EventLoop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;
class Server{
private:
    // EventLoop *loop; // 事件循环
    EventLoop *main_reactor_;
    std::vector<EventLoop *> sub_reactors_;
    Acceptor *acceptor; // 处理请求：客户端发起连接
    std::map<int, Connection*> connections; //保存所有TCP连接的map
    ThreadPool *thread_pool_;
    std::function<void(Connection *)> on_connect_callback_;
public:
    Server(EventLoop*);
    ~Server();
    void newConnection(Socket *sock);  // 新建TCP连接
    void deleteConnection(Socket *sock); // 断开TCP连接
    void OnConnect(std::function<void(Connection *)> fn);
};