#include "Acceptor.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"
#include <stdio.h>

/**
 * 初始化工作：在服务器新建一个socket，专用于监听客户端连接请求
*/
Acceptor::Acceptor(EventLoop *_loop) : loop(_loop) // Acceptor应该存在于一个EventLoop对象中
{
    sock = new Socket();
    InetAddress *addr = new InetAddress("127.0.0.1", 8888);
    sock->bind(addr);
    sock->listen(); 
    sock->setnonblocking();
    acceptChannel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this); // accept
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
    delete addr;
}

Acceptor::~Acceptor(){
    delete sock;
    // delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    InetAddress *clnt_addr = new InetAddress();      
    Socket *clnt_sock = new Socket(sock->accept(clnt_addr));      
    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->getAddr().sin_addr), ntohs(clnt_addr->getAddr().sin_port));
    clnt_sock->setnonblocking();
    newConnectionCallback(clnt_sock); 
    // 自定义的Acceptor回调函数，使得不同的Acceptor对象在accept连接后进行不同的处理
    // 这里是在Server构造函数中通过acceptor->setNewConnectionCallback设定的
    // 调用的其实是Server::newConnection
    // 其功能为：为新连接新建Connection对象封装起来，绑定新Connection的断开方式，
    delete clnt_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb){
    newConnectionCallback = _cb;
}