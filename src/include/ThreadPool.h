#pragma once

#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadPool {
private:
    std::vector<std::thread> threads; // 已创建的线程
    std::queue<std::function<void()>> tasks; // 待处理任务队列
    std::mutex tasks_mtx; // 任务队列锁，防止多个线程同时访问队列取任务
    std::condition_variable cv; // 条件变量
    bool stop;
public:
    ThreadPool(int size = 10);  // 默认size最好设置为std::thread::hardware_concurrency()
    ~ThreadPool();
    void add(std::function<void()>);
};