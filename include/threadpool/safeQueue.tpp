template<typename T>
safeQueue<T>::safeQueue() {}


template <typename T>
bool safeQueue<T>::empty() {
    std::scoped_lock<std::mutex> lock(mtx);
    return safe_queue.empty();
}

template <typename T>
int safeQueue<T>::size() {
    std::scoped_lock<std::mutex> lock(mtx);
    return safe_queue.size();
}

template <typename T>
T safeQueue<T>::front() {
    std::scoped_lock<std::mutex> lock(mtx);
    return safe_queue.front();
}

template <typename T>
void safeQueue<T>::pop() {
    std::scoped_lock<std::mutex> lock(mtx);
    return safe_queue.pop();
}


template <typename T>
void safeQueue<T>::push(T&& obj) {
    std::scoped_lock<std::mutex> lock(mtx);
    return safe_queue.push(std::forward<T>(obj));
}

