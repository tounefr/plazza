//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_WORKER_HPP
#define PLAZZA_WORKER_HPP

#include "ProcessWrapper.hpp"
#include "Thread.hpp"
#include "Task.hpp"
#include <list>
#include <queue>

class Worker : ProcessWrapper {
private:
    std::list<Thread*> _threads;

public:

    Worker();
    ~Worker();
    bool giveTask(Task& task);
    bool getNbrThreads();
    std::list<Thread*>& getThreads();
    bool getNbrThreadsRunning();
    void initThreads(int nbr_threads_per_proc);

};


#endif //PLAZZA_WORKER_HPP
