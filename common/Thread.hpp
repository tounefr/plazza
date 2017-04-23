//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_THREAD_HPP
#define PLAZZA_THREAD_HPP

#include <thread>
#include "Task.hpp"

class Thread {
private:
    Task *_task;
    std::thread _thread;
    bool _isRunning;
public:
    Thread();
    ~Thread();
    bool isRunning();
    virtual void run() = 0;
    bool start();
    void join();
    void setRunning(bool);
};


#endif //PLAZZA_THREAD_HPP
