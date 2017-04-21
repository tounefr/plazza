//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_WORKERPOOL_HPP
#define PLAZZA_WORKERPOOL_HPP

#include <list>
#include <queue>
#include "Worker.hpp"
#include "ProcessWrapper.hpp"
#include "Task.hpp"

class WorkerPool : public ProcessWrapper {
private:
    std::list<Worker*> _threads;

public:

    WorkerPool();
    ~WorkerPool();
    bool giveTask(Task& task);
    bool getNbrThreads();
    std::list<Worker*>& getThreads();
    unsigned int getNbrThreadsRunning();
    void initThreads(int nbr_threads_per_proc);
    void waitThreads();

};


#endif //PLAZZA_WORKERPOOL_HPP
