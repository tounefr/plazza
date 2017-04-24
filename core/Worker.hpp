//
// Created by thomas on 21/04/17.
//

#ifndef PLAZZA_WORKER_HPP
#define PLAZZA_WORKER_HPP

#include "../common/Task.hpp"
#include "../common/Thread.hpp"

class Worker : public Thread {
private:
    Task *_task;

public:
    Worker();
    ~Worker();
    bool giveTask(Task& task);
    void run();
    bool hasTask();
};

#endif //PLAZZA_WORKER_HPP
