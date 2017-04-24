//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Scheduler.hpp"
#include "../common/Queue.hpp"
#include "../Plazza.hpp"
#include "../network/ip/Socket.hpp"

Scheduler::Scheduler() :
        Thread() {
    _serverSocket = new Network::IP::ServerSocket(8888);
}

Scheduler::~Scheduler() {
}

void Scheduler::run() {
    std::cout << "Starting Scheduler" << std::endl;

    Plazza *p = Plazza::getInstance();
    Queue<Packet*> packets;
    Task *t;

    while (1) {
        t = p->getTasks().dequeue();
//        _serverSocket->sock_accept(packets);
        std::cout << "Handling task " << t << std::endl;
//            std::cout << "Pending tasks : " << p.nbrPendingTasks() << std::endl;
        std::cout << "Nbr process : " << _clients.size() << std::endl;
      /*  if (!giveTask(*t))
            break;*/
    }
}

bool Scheduler::giveTask(Task& task) {
    int pid;
    int status;
    WorkerPool *workerPool;

    return true;

    if ((pid = fork()) == 0) {
        return false;
    } else {
        waitpid(pid, &status, 0);
    }
    return true;
}
