#include "ThreadPool.h"

ThreadPool::ThreadPool(int size) : stop(false){
    for(int i = 0; i < size; ++i){
        // 对于每个加入线程池的线程
        threads.emplace_back(std::thread([this](){
            while(true){
                std::function<void()> task;
                { // 临界区
                    std::unique_lock<std::mutex> lock(tasks_mtx);
                    cv.wait(lock, [this](){
                        return stop || !tasks.empty();
                    });
                    if(stop && tasks.empty()) return;
                    // 取一个任务
                    task = tasks.front();
                    tasks.pop();
                }
                // 执行任务
                task();
            }
        }));
    }
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        stop = true;
    }
    cv.notify_all();
    for(std::thread &th : threads){
        if(th.joinable())
            th.join();
    }
}

void ThreadPool::add(std::function<void()> func){
    {
        // 临界区
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if(stop)
            throw std::runtime_error("ThreadPool already stop, can't add task any more");
        tasks.emplace(func); 
        // 不采用push，因为push会先产生一个副本，再将该副本入队；
        // 而emplace直接在队尾构造对象，避免push()产生的额外的复制或移动操作
        // 减小开销
    }
    cv.notify_one();
}