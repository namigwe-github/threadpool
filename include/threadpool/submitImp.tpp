template<typename F, typename... Args>
auto Threadpool::submitWork(F&& f, Args&&...args) -> std::future<decltype(f(args...))> {
    std::cout << "Submiting Work..." <<"\n";
    std::function<decltype(f(args...)) ()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto ptr = std::make_shared<std::packaged_task<decltype(f(args...)) ()>>(func);

    auto res = (*ptr).get_future();

    std::function<void ()> wrapper = [ptr]() {
        (*ptr)();
    };
    
    safe_queue.push(std::move(wrapper));
    workAvailable =true;
    cv.notify_one();
    std::cout << "Work submitted." <<"\n";
    return res;
}