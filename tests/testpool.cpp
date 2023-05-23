#include <iostream>
#include "threadpool.hpp"
#include <string>
#include <string_view>
#include <gtest/gtest.h>


static std::mutex strlock;
void func(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
void func2(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 2 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
void func3(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 3 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
int func4(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 3 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));
    return 100;
}

int main() {
    std::cout << "This is threadpool main" <<"\n";
    Threadpool tp(3);

    std::string str("Nam ");
    int num = 4;

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    tp.submitWork(func, std::move(num), std::move(str));
    tp.submitWork(func2, std::move(num-1), std::move(str));
    tp.submitWork(func3, std::move(num-3), std::move(str));
    auto obj = tp.submitWork(func4, std::move(num-3), std::move(str));
    
    obj.wait();
    std::cout << "The value retuned is "<< obj.get() << "\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //tp.shutdown();
    
    return 0;
}