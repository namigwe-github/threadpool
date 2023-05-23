#include "threadpool.hpp"
#include <memory>

Threadpool::Threadpool(size_t numThreads): numWorkers(numThreads){
    std::cout <<"Threadpool created and "<<  numThreads << " workers operational."<< "\n";

    for (int i = 0; i < numWorkers; i++) {
        workers.emplace_back(std::move(std::thread(&Threadpool::executeTask,this, i)));
    }

}

//Threadpool::WorkerThread::~WorkerThread(){ std::cout << "Destructor Called" << "\n";};

void Threadpool::executeTask(const int & id) {
    
    while(true) {
        std::function<void ()> task;
        {
            std::unique_lock<std::mutex> lock(conditional_lock);
            std::cout<< "Thread " << id << " waiting to work..." <<"\n";
            (cv).wait(lock, [this]() { return workAvailable||shtdwn;});
            if (shtdwn && !workAvailable) {
                return;
            }
            task = std::move((safe_queue).front());
            (safe_queue).pop();

            if((safe_queue).empty()) {
                workAvailable = false;
                std::cout << "No more work available." <<"\n";
            } else {
                std::cout << "More work available!" <<"\n";
            }
        }
        std::cout <<"Starting work..." << "\n";
        task();

    }
    std::cout <<"Work completed" << "\n";
    
}




Threadpool::~Threadpool() {
    shtdwn = true;
    cv.notify_all();
    std::cout<<"Threads notified \n";

    for (int i =0; i < numWorkers; i++) {
        workers[i].join();
    }
    std::cout<<"Threadpool terminated \n";
}


size_t& Threadpool::getNumWorkers() {
    return numWorkers;
}
