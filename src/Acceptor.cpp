#include "Acceptor.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"

/**
 * 初始化工作：在服务器新建一个socket，专用于监听客户端连接请求
*/
Acceptor::Acceptor(EventLoop *_loop) : loop(_loop) // Acceptor应该存在于一个EventLoop对象中
{
    sock = new Socket();
    addr = new InetAddress("127.0.0.1", 8888);
    sock->bind(addr);
    sock->listen(); 
    sock->setnonblocking();
    acceptChannel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
    delete sock;
    delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    newConnectionCallback(sock); 
    // 使用一个回调函数来处理连接请求
    // 这个回调函数可以通过下面的setNewConnectionCallback灵活修改
    // 这就允许不同的Acceptor对象以自己定义的方式处理连接请求
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb){
    newConnectionCallback = _cb;
}