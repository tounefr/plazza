//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_WORKER_HPP
#define PLAZZA_WORKER_HPP

#include "ProcessWrapper.hpp"
#include "Thread.hpp"
#include <queue>

class Worker : ProcessWrapper {
private:

    std::vector<Thread> _threads;

public:

    Worker();
    ~Worker();
    bool giveTask();
    bool getNbrThreads();
    std::vector<Thread>& getThreads();
    bool getNbrThreadsRunning();

};


#endif //PLAZZA_WORKER_HPP
