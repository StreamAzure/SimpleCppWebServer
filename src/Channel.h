#pragma once
#include <sys/epoll.h>
#include <functional>
class EventLoop;
class Channel
{
private:
    EventLoop *loop;
    int fd;
    uint32_t events;// 希望监听的事件
    uint32_t revents;// Epoll返回该Channel时正在发生的事件
    bool inEpoll;// 本Channel是否在epoll红黑树中
    std::function<void()> callback;
public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    void handleEvent();
    void enableReading();//监听读事件

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    // void setEvents(uint32_t);
    void setRevents(uint32_t);
    void setCallback(std::function<void()>);
};