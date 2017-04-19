//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include "Plazza.hpp"

Plazza::Plazza(int const& nbr_threads_per_proc) :
        _nbr_threads_per_proc(nbr_threads_per_proc) {

    _scheduler = new Scheduler(nbr_threads_per_proc);

    _scheduler->giveTask(new Task("./test.html", PHONE_NUMBER));
    _scheduler->giveTask(new Task("./test.html", PHONE_NUMBER));

}

Plazza::~Plazza() {
    if (this->_scheduler)
        delete this->_scheduler;
}

std::queue<Task>& Plazza::getTasks() {
    return _tasks;
}