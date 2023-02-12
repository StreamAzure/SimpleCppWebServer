#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main() {
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
    serv_addr.sin_family = AF_INET; // 地址族 IPv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");
    // socket描述符与地址端口绑定
    // 地址+端口需要强制转换为sockaddr

    errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");
    // 监听socket，SOMAXCONN最大监听队列长度（128）
    
    struct sockaddr_in clnt_addr; // 用于保存客户端的地址+端口信息
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    bzero(&clnt_addr, sizeof(clnt_addr));

    int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
    // 第三个参数是socket长度，但传地址而非传值
    errif(clnt_sockfd == -1, "socket accept error");

    printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
    
    while(true){
        char buf[1024]; // 缓冲区
        bzero(&buf, sizeof(buf)); // 初始化
        ssize_t read_bytes = read(clnt_sockfd, buf, sizeof(buf)); // 从客户端读数据，返回数据大小
        if(read_bytes > 0){
            printf("message from client fd %d: %s\n", clnt_sockfd, buf);
            write(clnt_sockfd, buf, sizeof(buf)); // 将收到的数据回复给客户端
        }
        else if(read_bytes == 0){ // EOF
            printf("client fd %d disconnected\n", clnt_sockfd);
            close(clnt_sockfd);
            break;
        }
        else if(read_bytes == -1){
            close(clnt_sockfd);
            errif(true, "socket read error");
        }
    }
    return 0;
}