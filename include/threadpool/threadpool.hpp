#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <future>
#include "safeQueue.hpp"
#include <type_traits>
#include <condition_variable>
#include <algorithm>
#include <utility>

class Threadpool {
    safeQueue<std::function<void ()>> safe_queue;
    size_t numWorkers;
    //std::vector<WorkerThread> workers;
    std::vector<std::thread> workers;
    std::mutex conditional_lock;
    std::condition_variable cv;
    bool shtdwn = false;
    bool notified = false;
    bool workAvailable = false;
    void executeTask(const int & id);
    public:
    Threadpool(size_t numThreads);
    Threadpool(const Threadpool & other) = delete;
    Threadpool(Threadpool&& other) = delete;
    Threadpool operator= (const Threadpool& other) = delete;
    Threadpool operator= (Threadpool&&) = delete;
    ~Threadpool();

    template<typename F, typename... Args>
    auto submitWork(F&& f, Args&&...args) -> std::future<decltype(f(args...))>;

    size_t& getNumWorkers();

   
};

#include "submitImp.tpp"