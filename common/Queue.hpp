//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_QUEUE_HPP
#define PLAZZA_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Task.hpp"

template<class T>
class Queue {
private:
    std::queue<T> _items;
    std::mutex _lock;
    std::condition_variable _cond;

public:
    Queue() :
            _items(),
            _lock(),
            _cond() {
    };

    void enqueue(T t) {
        std::lock_guard<std::mutex> lock(_lock);
        _items.push(t);
        _cond.notify_one();
    };

    T dequeue() {
        std::unique_lock<std::mutex> lock(_lock);
        while (_items.empty())
            _cond.wait(lock);
        T item = _items.front();
        _items.pop();
        return item;
    };

    size_t size() {
        std::lock_guard<std::mutex> lock(_lock);
        return _items.size();
    };
};

// [INFO][DATE][WorkerPool] : Message
#endif //PLAZZA_QUEUE_HPP
