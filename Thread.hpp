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
    void run();
    bool start();
    void init();
    void join();
    bool giveTask(Task &task);
};


#endif //PLAZZA_THREAD_HPP
