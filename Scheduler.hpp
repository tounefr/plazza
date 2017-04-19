//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_SCHEDULER_H
#define PLAZZA_SCHEDULER_H

#include <vector>
#include "Worker.hpp"
#include "Task.hpp"

class Scheduler {
private:
    int _nbr_threads_per_proc;
    std::vector<Worker> _workers;
    Worker& getAvailableWorker();
    Worker& newWorker();

public:
    Scheduler(int const& nbr_threads_per_proc);
    bool giveTask(Task& task);
};


#endif //PLAZZA_SCHEDULER_H
