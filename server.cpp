#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include "util.h"

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void setnonblocking(int fd)
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // 建立一个socket套接字，返回socket文件描述符
    // IP版本，数据传输方式，协议
    // AF_INET IPv4,，AF_INET6 IPv6
    // SOCK_STREAM 流、面向连接， SOCK_DGRAM 数据报、无连接
    // 0|IPPROTO_TCP|IPPTOTO_UDP 自动推导协议类型|TCP|UDP
    errif(sockfd == -1, "socket create error");

    // 将套接字绑定到一个IP地址和端口上（命名socket）
    struct sockaddr_in serv_addr;
    // 与sockaddr相比，sockaddr_in区分了地址和端口
    // 但实际使用时还是要强制转换回sockaddr
    bzero(&serv_addr, sizeof(serv_addr)); // 初始化，置为全0
    serv_addr.sin_family = AF_INET;       // 地址族 IPv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");
    // socket描述符与地址端口绑定
    // 地址+端口需要强制转换为sockaddr

    errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");
    // 监听socket，SOMAXCONN最大监听队列长度（128）

    int epfd = epoll_create1(0); // epoll事件表，以一个文件描述符指代
    errif(epfd == -1, "epoll create error");

    epoll_event events[MAX_EVENTS], ev;
    bzero(&events, sizeof(events));
    bzero(&ev, sizeof(ev));
    ev.events = EPOLLIN | EPOLLET;               // 事件：有数据到达。默认ET模式：事件发生只通知内核一次
    ev.data.fd = sockfd;                         // 事件关联的socket
    setnonblocking(sockfd);                      // 设置为非阻塞式socket，配合ET模式使用
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev); // 将指定socket及监听事件添加到epfd的监听红黑树中

    while (true)
    {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1); // 返回就绪事件的个数
        // 就绪事件相关信息保存在events[]中，对应socket通过events[i].data.fd获取
        errif(nfds == -1, "epoll wait error");

        for (int i = 0; i < nfds; i++) // 遍历就绪事件队列，作出相应处理
        {
            if (events[i].data.fd == sockfd) 
            { // 就绪：有新客户端连接
                struct sockaddr_in clnt_addr;
                bzero(&clnt_addr, sizeof(clnt_addr));
                socklen_t clnt_addr_len = sizeof(clnt_addr);

                int clnt_sockfd = accept(sockfd, (sockaddr *)&clnt_addr, &clnt_addr_len);
                errif(clnt_sockfd == -1, "socket accept error");
                printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
                // 记录新客户端的socket信息

                bzero(&ev, sizeof(ev));
                ev.data.fd = clnt_sockfd;
                ev.events = EPOLLIN | EPOLLET;
                setnonblocking(clnt_sockfd);
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sockfd, &ev);
                // 将客户端socket及EPOLLIN事件也加入到epoll事件表
            }
            else if (events[i].events & EPOLLIN) 
            { // 就绪：某个客户端socket有数据进来
                char buf[READ_BUFFER];
                while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
                    bzero(&buf, sizeof(buf));
                    ssize_t bytes_read = read(events[i].data.fd, buf, sizeof(buf));
                    if(bytes_read > 0){
                        printf("message from client fd %d: %s\n", events[i].data.fd, buf);
                        write(events[i].data.fd, buf, sizeof(buf));
                    } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
                        printf("continue reading");
                        continue;
                    } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
                        printf("finish reading once, errno: %d\n", errno);
                        break;
                    } else if(bytes_read == 0){  //EOF，客户端断开连接
                        printf("EOF, client fd %d disconnected\n", events[i].data.fd);
                        close(events[i].data.fd);   //关闭socket会自动将文件描述符从epoll树上移除
                        break;
                    }
                }
            }
            else{ 
                // 就绪：发生了其他事件
                printf("something else happened\n");
            }
        }
    }
    close(sockfd);
    return 0;
}