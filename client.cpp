#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "util.h"
#include "Socket.h"
#include "InetAddress.h"

#define BUFFER_SIZE 1024

int main() {
    Socket* clnt_sock = new Socket();

    InetAddress* serv_addr = new InetAddress("127.0.0.1", 8888);

    errif(connect(clnt_sock->getFd(), (sockaddr*)&serv_addr->addr, serv_addr->addr_len) == -1, "socket connect error");
    // 通过自己的socket向服务器发起连接
    // 成功时返回 0，客户端可以通过读写sockfd与服务器通信

    while(true){
        char buf[BUFFER_SIZE]; // 缓冲区，大小必须大于或等于server那边的READ_SIZE，因为是非阻塞式IO
        bzero(&buf, sizeof(buf)); // 初始化

        std::cin >> buf;
        ssize_t write_bytes = write(clnt_sock->getFd(), buf, sizeof(buf)); // 向接口写数据
        errif(write_bytes == -1, "socket already disconnected");

        bzero(&buf, sizeof(buf));
        ssize_t read_bytes = read(clnt_sock->getFd(), buf, sizeof(buf)); // 读取服务器发来的数据
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }
        else if(read_bytes == 0){ // EOF，服务器断开连接
            printf("server socket disconnected\n");
            break;
        }
        else if(read_bytes == -1){
            close(clnt_sock->getFd());
            errif(true, "socket read error");
        }
    }
    return 0;
}