#include "Epoll.h"
#include "util.h"
#include <unistd.h>
#include <cstring>
#include "Channel.h"

#define MAX_EVENTS 1024

/**
 * 封装Epoll机制
 * 构造：1.epoll_create初始化eventpoll对象；2.new一个events数组用于返回就绪socket
 * 析构：1.close(epfd)；2. delete掉events数组
 * 通知与轮询：1.调用一次epoll_wait 2.将返回的就绪socket逐个封装成Channel
 * 随后对Channel的处理都交给EventLoop
*/
Epoll::Epoll(): epfd(-1), events(nullptr)
{
    epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll()
{
    if(epfd != -1){
        close(epfd);
        epfd = -1;
    }
    delete [] events;
}

// void Epoll::addFd(int fd, uint32_t op){
//     epoll_event ev;
//     bzero(&ev, sizeof(ev));
//     ev.data.fd = fd;
//     ev.events = op;
//     errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add event error");
// }
// 已被updateChannel代替

std::vector<Channel*> Epoll::poll(int timeout){
    // std::vector<epoll_event> activeEvents; //?
    // int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    // errif(nfds == -1, "epoll wait error");
    // for(int i = 0; i < nfds; ++i){
    //     activeEvents.push_back(events[i]);
    // }
    // return activeEvents;
    std::vector<Channel*> activeChannels; // 所有有事件发生的Channel
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    for(int i = 0;i < nfds; i++){
        Channel *ch = (Channel*)events[i].data.ptr;
        ch->SetReadyEvents(events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel *channel){
    int fd = channel->getFd(); // 拿Channel的文件描述符
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->GetListenEvents(); // 需要监听的事件
    if(!channel->getInEpoll()){ // 若Channel未加入epoll的红黑树，则添加
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
        channel->setInEpoll();
        // debug("Epoll: add Channel to epoll tree success, the Channel's fd is: ", fd);
    } else{ // 若Channel已在epoll的红黑树中，则更新
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
        // debug("Epoll: modify Channel in epoll tree success, the Channel's fd is: ", fd);
    }
}