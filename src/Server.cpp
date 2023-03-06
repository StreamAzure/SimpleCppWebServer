#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"
#include "EventLoop.h"
#include <string.h>
#include <functional>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) : main_reactor_(_loop), acceptor(nullptr){    
    acceptor = new Acceptor(main_reactor_);   //Acceptor由且只由mainReactor负责
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    // 定义回调函数，即对客户端新连接的处理方式
    acceptor->setNewConnectionCallback(cb);

    int size = std::thread::hardware_concurrency();     //线程数量，也是subReactor数量
    thread_pool_ = new ThreadPool(size);                //新建线程池
    for(int i = 0; i < size; ++i){
        sub_reactors_.push_back(new EventLoop());     //每一个线程是一个EventLoop
    }
    for(int i = 0; i < size; ++i){
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, sub_reactors_[i]);
        thread_pool_->add(sub_loop);      //开启所有线程的事件循环
    }
}

Server::~Server(){
    delete acceptor;
    delete thread_pool_;
}

// void Server::newConnection(Socket *serv_sock){
//     InetAddress *clnt_addr = new InetAddress();      //会发生内存泄露！没有delete
//     Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));       //会发生内存泄露！没有delete
//     printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->addr.sin_addr), ntohs(clnt_addr->addr.sin_port));
//     clnt_sock->setnonblocking();
//     Channel *clntChannel = new Channel(loop, clnt_sock->getFd());
//     std::function<void()> cb = std::bind(&Server::handleReadEvent, this, clnt_sock->getFd());
//     clntChannel->setCallback(cb);
//     clntChannel->enableReading();
// }

void Server::newConnection(Socket *sock){
    printf("Server::newConnection被回调...\n");
    int random = sock->getFd() % sub_reactors_.size();    //调度策略：全随机
    Connection *conn = new Connection(sub_reactors_[random], sock);   //分配给一个subReactor
    // Connection *conn = new Connection(loop, sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb); // 允许灵活定义每个连接的断开方式
    conn->SetOnConnectCallback(on_connect_callback_); // 允许灵活定义连接的业务
    connections[sock->getFd()] = conn; 
}

void Server::deleteConnection(Socket * sock){
    int sockfd = sock->getFd();
    auto it = connections.find(sockfd);
    if (it != connections.end()) {
        Connection *conn = connections[sockfd];
        connections.erase(sockfd);
        delete conn;
        conn = nullptr;
    }
    // Connection *conn = connections[sock->getFd()];
    // connections.erase(sock->getFd());
    // delete conn;
    // conn = nullptr;
}

void Server::OnConnect(std::function<void(Connection *)> fn) { on_connect_callback_ = fn; }