#pragma once
#include <sys/epoll.h>

class Epoll;
class Channel{
    private:
    Epoll *ep; // 负责本文件描述符的Epoll
    int fd; // 文件描述符
    uint32_t events; // 希望监听的事件
    uint32_t revents; // Epoll返回该Channel时正在发生的事件
    bool inEpoll; // 本Channel是否在epoll红黑树中
    public:
    Channel(Epoll *_ep, int _fd);
    ~Channel();

    void enableReading(); //监听读事件
    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t);
};