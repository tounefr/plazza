//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PLAZZA_HPP
#define PLAZZA_PLAZZA_HPP

#include <queue>
#include "Thread.hpp"
#include "Scheduler.hpp"

class Plazza {
private:
    std::queue<Task> _tasks;

public:
    Plazza(int nbr_threads_per_proc);
    std::queue<Task>& getTasks();
};


#endif //PLAZZA_PLAZZA_HPP