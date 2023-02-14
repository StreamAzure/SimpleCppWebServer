#include "Channel.h"
#include "Epoll.h"

Channel::Channel(Epoll *_ep, int _fd) : ep(_ep), fd(_fd), events(0), revents(0), inEpoll(false)
{
}
Channel::~Channel()
{
}
void Channel::enableReading(){
    events = EPOLLIN | EPOLLET;
    ep -> updateChannel(this);
    // 若Channel不在红黑树中，则添加
    // 若Channel已在红黑树中，则更新、打开允许读事件
}

