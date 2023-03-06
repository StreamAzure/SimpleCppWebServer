#include "Channel.h"
#include "EventLoop.h"
#include "ThreadPool.h"
#include <unistd.h>
#include <stdio.h>
Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), listen_events_(0), ready_events_(0), inEpoll(false){
    printf("创建Channel：fd = %d\n", _fd);
}
Channel::~Channel()
{
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}
void Channel::handleEvent(){
    if (ready_events_ & (EPOLLIN | EPOLLPRI)) {
        read_callback_();
    }
    if (ready_events_ & (EPOLLOUT)) {
        write_callback_();
    }
}

void Channel::enableReading(){
    listen_events_ = EPOLLIN | EPOLLET;
    loop -> updateChannel(this);
    // 若Channel不在红黑树中，则添加
    // 若Channel已在红黑树中，则更新、打开允许读事件
}
int Channel::getFd(){
    return fd;
}

uint32_t Channel::GetListenEvents() { return listen_events_; }
uint32_t Channel::GetReadyEvents() { return ready_events_; }

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(){
    inEpoll = true;
}

// void Channel::setEvents(uint32_t _ev){
//     events = _ev;
// }

void Channel::SetReadyEvents(uint32_t ev) { ready_events_ = ev; }

// void Channel::setCallback(std::function<void()> _cb){
//     callback = _cb;
// }

void Channel::SetReadCallback(std::function<void()> callback) { read_callback_ = callback; }