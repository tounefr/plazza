//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Scheduler.hpp"
#include "Plazza.hpp"

Scheduler::Scheduler() :
        Thread() {
}

Scheduler::~Scheduler() {
}

void Scheduler::run() {
    Plazza &p = Plazza::getInstance();
    Task *t;

    while (1) {
        if (p.getTasks().size() > 0) {
            t = &p.popTask();
            std::cout << "Handling task " << t << std::endl;
            std::cout << "Pending tasks : " << p.nbrPendingTasks() << std::endl;
            std::cout << "Nbr process : " << _clients.size() << std::endl;
            if (!giveTask(*t))
                break;
        }
        sleep(1);
    }
}

bool Scheduler::giveTask(Task& task) {
    int pid;
    int status;
    WorkerPool *workerPool;

    if ((pid = fork()) == 0) {
        return false;
    } else {

    }
    return true;
}
