#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>
#include <stdio.h>

EventLoop::EventLoop(): ep(nullptr), quit(false){
    ep = new Epoll();
}

EventLoop::~EventLoop(){
    delete ep;
}

void EventLoop::loop(){
    while(!quit){
        std::vector<Channel*> chs;
        chs = ep->poll(); // 遍历就绪Channel列表
        for(auto it = chs.begin(); it != chs.end(); ++it){
            printf("Channel开始处理事件...\n");
            (*it)->handleEvent(); // 让Channel处理事件
        }
    }
}

void EventLoop::updateChannel(Channel *ch){
    ep->updateChannel(ch);
}