#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.cpp"

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false){
}
Channel::~Channel()
{
}
void Channel::handleEvent(){
    callback();
}

void Channel::enableReading(){
    events = EPOLLIN | EPOLLET;
    loop -> updateChannel(this);
    // 若Channel不在红黑树中，则添加
    // 若Channel已在红黑树中，则更新、打开允许读事件
}
int Channel::getFd(){
    return fd;
}

uint32_t Channel::getEvents(){
    return events;
}
uint32_t Channel::getRevents(){
    return revents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(){
    inEpoll = true;
}

// void Channel::setEvents(uint32_t _ev){
//     events = _ev;
// }

void Channel::setRevents(uint32_t _ev){
    revents = _ev;
}

void Channel::setCallback(std::function<void()> _cb){
    callback = _cb;
}

