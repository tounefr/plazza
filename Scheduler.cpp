//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Scheduler.hpp"
#include "NamedPipeEndPoint.hpp"
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

    NamedPipeEndPoint *npep;

    if ((pid = fork()) == 0) {
        npep = new NamedPipeEndPoint(getpid());
        npep->setEndPoint(true);
        npep->open_endpoint();
        //npep->recv();
        std::cout << "ok";

        // mkfifo et open pour in et out
        // read en boucle sur in
//        workerPool = new WorkerPool();
        return false;
    } else {
        npep = new NamedPipeEndPoint(pid);
        npep->setEndPoint(false);
        npep->open_endpoint();
        //npep->recv();
        //npep->start();

        while (1)
            sleep(1);
        // open sur in pour write
        // open sur out pour read
        // read en boucle sur out
    }
    return true;
}
