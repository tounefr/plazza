//
// Created by thomas on 19/04/17.
//

#include "Scheduler.hpp"

Scheduler::Scheduler(int const& nbr_threads_per_proc) :
        _nbr_threads_per_proc(nbr_threads_per_proc) {

}

Scheduler::~Scheduler() {

}

Worker& Scheduler::getAvailableWorker() {
}

bool Scheduler::giveTask(Task *task) {
    Worker worker;

    worker = getAvailableWorker();
}