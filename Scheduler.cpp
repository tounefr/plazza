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
            if (!giveTask(*t))
                break;
        }
        sleep(1);
    }
}

bool Scheduler::giveTask(Task& task) {
    int pid;
    int status;

    if ((pid = (fork() == 0))) {
        _clients.push_back(new Client());
    } else {
    }
    return true;

    /*
    Plazza &p = Plazza::getInstance();

    p.pushTask(task);

    Worker worker;


    worker = getAvailableWorker();
     */
}
