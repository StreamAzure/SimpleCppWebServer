#pragma once

class InetAddress;
class Socket
{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void bind(InetAddress*);
    // 封装 errif(bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");
    void listen();
    // 封装 errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");
    void setnonblocking();

    int accept(InetAddress*);
    int getFd();
};
