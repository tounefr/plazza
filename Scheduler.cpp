//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include <iostream>
#include "Scheduler.hpp"
#include "Plazza.hpp"

Scheduler::Scheduler() {
    _processPopperThread = std::thread(Scheduler::workerPopper, this);
}

Scheduler::~Scheduler() {
}

void Scheduler::workerPopper(Scheduler *scheduler) {
    Plazza &p = Plazza::getInstance();

    while (1) {
        p.popTask();
        std::cout << "Pending tasks : " << p.nbrPendingTasks() << std::endl;
        sleep(2);
    }
}

Worker& Scheduler::getAvailableWorker() {
}

bool Scheduler::giveTask(Task& task) {
    /*
    Plazza &p = Plazza::getInstance();

    p.pushTask(task);

    Worker worker;


    worker = getAvailableWorker();
     */
}

void Scheduler::join() {
    _processPopperThread.join();
}