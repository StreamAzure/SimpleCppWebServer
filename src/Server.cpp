#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include <string.h>
#include <functional>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) : loop(_loop), acceptor(nullptr){    
    // Socket *serv_sock = new Socket();
    // InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    // serv_sock->bind(serv_addr);
    // serv_sock->listen(); 
    // serv_sock->setnonblocking();
       
    // Channel *servChannel = new Channel(loop, serv_sock->getFd());
    // std::function<void()> cb = std::bind(&Server::newConnection, this, serv_sock);
    // 定义回调函数，即对客户端新连接的处理方式
    // servChannel->setCallback(cb);
    // servChannel->enableReading();

    // 原来的连接请求处理被封装为Acceptor类
    // 一个Server实例应至少有一个Acceptor
    acceptor = new Acceptor(loop);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    // 定义回调函数，即对客户端新连接的处理方式
    acceptor->setNewConnectionCallback(cb);

}

Server::~Server(){
    delete acceptor;
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
    Connection *conn = new Connection(loop, sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb); // 允许灵活定义每个连接的断开方式
    connections[sock->getFd()] = conn; 
    // 一个Server示例使用一个map<int, *Connection>管理所有的TCP连接
    // 其中int是TCP连接关联的Socket文件描述符
    // 也就是说，将（来自客户端的一个）Socket与一条TCP连接建立映射
    // 每个Connecion实例都固定有一个echo成员函数，绑定到对应Channel的回调函数
    // 这样就把原来Server的成员函数handleReadEvent封装到了Connection里
}

void Server::deleteConnection(Socket * sock){
    Connection *conn = connections[sock->getFd()];
    connections.erase(sock->getFd());
    delete conn;
}