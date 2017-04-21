//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_SCHEDULER_H
#define PLAZZA_SCHEDULER_H

#include <vector>
#include <thread>
#include "Worker.hpp"
#include "Task.hpp"

class Scheduler {
private:
    std::thread _processPopperThread;
    std::vector<Worker> _workers;
    Worker& getAvailableWorker();
    Worker& newWorker();

public:
    Scheduler();
    ~Scheduler();
    bool giveTask(Task &task);
    static void workerPopper(Scheduler*);
    void join();
};


#endif //PLAZZA_SCHEDULER_H
