#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define READ_BUFFER 1024

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), sock(_sock), channel(nullptr){
    channel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    channel->setCallback(cb); // 绑定回调函数echo
    channel->enableReading(); // 打开读事件监听

    readBuffer = new Buffer(); //初始化缓冲区
}

Connection::~Connection(){
    delete channel;
    delete sock;
}

void Connection::echo(int sockfd){
    printf("Connection::echo被回调...\n");
    char buf[READ_BUFFER];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0){
            // write(sockfd, buf, sizeof(buf));
            // 原方法是来一点就write一点，buf也是就地声明的
            // 新方法是来了就统一读到Connection的缓冲区里，等读完了再从缓冲区统一write回去
            readBuffer->append(buf, bytes_read);
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once\n");
            printf("message from client fd %d: %s\n", sockfd, readBuffer->c_str());
            write(sockfd, readBuffer->c_str(), readBuffer->size());
            // 全部读到缓冲区里后，再统一write回给客户端
            readBuffer->clear();
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            // close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            deleteConnectionCallback(sock);
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _cb){
    deleteConnectionCallback = _cb;
}