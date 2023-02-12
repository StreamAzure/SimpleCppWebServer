#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include "util.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Epoll.h"

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void setnonblocking(int fd)
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

void handleReadEvent(int sockfd);

int main()
{
    Socket *serv_sock = new Socket();

    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);

    serv_sock->bind(serv_addr);
    serv_sock->listen();

    Epoll *epoll = new Epoll();
    epoll->addFd(serv_sock->getFd(), EPOLLIN | EPOLLET); 

    serv_sock->setnonblocking();

    while (true)
    {
        std::vector<epoll_event> events = epoll->poll();
        int nfds = events.size();

        for (int i = 0; i < nfds; i++) // 遍历就绪事件队列，作出相应处理
        {
            if (events[i].data.fd == serv_sock->getFd()) 
            { // 就绪：有新客户端连接
                InetAddress* clnt_addr = new InetAddress();
                // 会发生内存泄露！没有delete
                Socket* clnt_sock = new Socket(serv_sock->accept(clnt_addr));
                // 会发生内存泄露！没有delete
                
                printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->addr.sin_addr), ntohs(clnt_addr->addr.sin_port));
                // 记录新客户端的socket信息

                epoll->addFd(clnt_sock->getFd(), EPOLLIN | EPOLLET);
                // 将客户端socket及EPOLLIN事件也加入到epoll事件表

                clnt_sock->setnonblocking();
            }
            else if (events[i].events & EPOLLIN) 
            { // 就绪：某个客户端socket有数据进来
                handleReadEvent(events[i].data.fd);
            }
            else{ 
                // 就绪：发生了其他事件
                printf("something else happened\n");
            }
        }
    }
    return 0;
}

void handleReadEvent(int sockfd){
    char buf[READ_BUFFER];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0){
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}