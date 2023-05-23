#pragma once 

#include <queue>
#include <iostream>
#include <functional>
#include <mutex>

template <typename T>
class safeQueue {
    std::queue<T> safe_queue;
    public:
    std::mutex mtx;
    safeQueue();

    bool empty();

    int size();

    T front();

    void pop();

    void push(T&& obj);

};

#include "safeQueue.tpp"

