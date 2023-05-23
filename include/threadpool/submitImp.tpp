template<typename F, typename... Args>
auto Threadpool::submitWork(F&& f, Args&&...args) -> std::future<decltype(f(args...))> {
    std::cout << "Running Submit Function" <<"\n";
    

    //std::function<decltype(f(args...))(decltype(args)...)> func(f);
    std::function<decltype(f(args...)) ()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    //decltype(f(args...)) returnVal =  task.get_future();
    /*std::function<void ()> wrapper = [func,&args...] () {
        func(std::forward<Args>(args)...);
    };*/
    
    auto ptr = std::make_shared<std::packaged_task<decltype(f(args...)) ()>>(func);

    auto res = (*ptr).get_future();

    std::function<void ()> wrapper = [ptr]() {
        //std::cout<<std::boolalpha<<task.valid()<<"\n";
        //task(std::forward<Args>(args)...);
        //func1();
        (*ptr)();
    };
    
    safe_queue.push(std::move(wrapper));
    workAvailable =true;
    cv.notify_one();
    std::cout << "Done Submit Function" <<"\n";
    return res;
}