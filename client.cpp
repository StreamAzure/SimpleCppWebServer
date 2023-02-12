#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "util.h"

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
    
    return 0;
}