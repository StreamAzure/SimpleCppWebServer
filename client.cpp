#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "util.h"

#define BUFFER_SIZE 1024

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd == -1, "socket create error");

    struct sockaddr_in serv_addr;

    bzero(&serv_addr, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    //bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)); 客户端不进行bind操作

    errif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket connect error");
    // 通过自己的socket向服务器发起连接
    // 成功时返回 0，客户端可以通过读写sockfd与服务器通信

    while(true){
        char buf[BUFFER_SIZE]; // 缓冲区，大小必须大于或等于server那边的READ_SIZE，因为是非阻塞式IO
        bzero(&buf, sizeof(buf)); // 初始化

        std::cin >> buf;
        ssize_t write_bytes = write(sockfd, buf, sizeof(buf)); // 向接口写数据
        errif(write_bytes == -1, "socket already disconnected");

        bzero(&buf, sizeof(buf));
        ssize_t read_bytes = read(sockfd, buf, sizeof(buf)); // 读取服务器发来的数据
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }
        else if(read_bytes == 0){ // EOF，服务器断开连接
            printf("server socket disconnected\n");
            break;
        }
        else if(read_bytes == -1){
            close(sockfd);
            errif(true, "socket read error");
        }
    }
    close(sockfd);
    return 0;
}