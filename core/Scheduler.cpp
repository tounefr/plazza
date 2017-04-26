//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Plazza.hpp"
#include "Scheduler.hpp"
#include "../common/Queue.hpp"
#include "../network/ip/Socket.hpp"

Scheduler::Scheduler() :
        Thread(),
        _clients(),
        _min_process(3),
        _maxTaskPerClient(10)
{
    _serverSocket = new Network::IP::ServerSocket(8888);
    if (!_serverSocket->sock_listen()) {
        Plazza::getInstance()->setRunning(false);
    }
}

Scheduler::~Scheduler() {
}

size_t& Scheduler::getMinProcess() {
    return _min_process;
}

void Scheduler::run() {
    std::cout << "Starting Scheduler" << std::endl;
    Task *t;

    // On initialise <_min_process> à l'avance
    for (int i = 0; i < getMinProcess(); i++)
        newProcess(NULL);
    sleep(1);
    infos_process();

    while (Plazza::getInstance()->isRunning()) {
        t = Plazza::getInstance()->getTasks().dequeue();
        std::cout << "Handling task " << t << std::endl;
        if (!giveTask(*t))
            break;
    }
}

Client* Scheduler::getLeastLoadedClient() {
    Client *least;
    Client *client;

    least = NULL;
    for (std::list<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); iter++) {
        client = *iter;
        if (client->isReady() && (least == NULL || least->getNbrTasks() > client->getNbrTasks()))
            least = client;
    }
    return least;
}

bool Scheduler::newProcess(Task* task) {
    Client *client;
    int pid;
    WorkerPool *workerPool;

    if ((pid = fork()) == 0) {
        workerPool = new WorkerPool();
        return false;
    } else {
        client = new Client(pid, this, task, _serverSocket);
        _clients.push_back(client);
    }
}

bool Scheduler::giveTask(Task& task) {
    Client *client;


    if ((NULL == (client = getLeastLoadedClient())) || (client->getNbrTasks() >= _maxTaskPerClient)) {
        newProcess(&task);
    } else {
        client->giveTask(&task);
    }
    infos_process();
    return true;
}
