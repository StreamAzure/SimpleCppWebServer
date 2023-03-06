#pragma once
#include <sys/epoll.h>
#include <functional>
class EventLoop;
class Channel
{
private:
    EventLoop *loop;
    int fd;
    uint32_t listen_events_;
    uint32_t ready_events_;
    bool inEpoll;// 本Channel是否在epoll红黑树中
    std::function<void()> read_callback_;
    std::function<void()> write_callback_;
public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    void handleEvent();
    void enableReading();//监听读事件
    uint32_t GetListenEvents();
    uint32_t GetReadyEvents();

    int getFd();

    bool getInEpoll();
    void setInEpoll();

    void SetReadyEvents(uint32_t ev);
    void SetReadCallback(std::function<void()>);
};