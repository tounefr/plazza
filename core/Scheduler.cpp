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
        Thread(),
        _clients(),
        _maxTaskPerClient(10)
{
    _serverSocket = new Network::IP::ServerSocket(8888);
    _serverSocket->sock_listen();
}

Scheduler::~Scheduler() {
}

void Scheduler::run() {
    std::cout << "Starting Scheduler" << std::endl;

    Plazza *p = Plazza::getInstance();
    Task *t;

    while (_serverSocket->isListening()) {
        t = p->getTasks().dequeue();
//        _serverSocket->sock_accept(packets);
        std::cout << "Handling task " << t << std::endl;
        if (!giveTask(*t))
            break;
    }
}

Client* Scheduler::getLeastLoadedClient() {
    Client *least;

    least = NULL;
    for (std::list<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); iter++) {
        Client *client = *iter;
        if (least == NULL || least->getNbrTasks() > client->getNbrTasks())
            least = client;
    }
    return least;
}

bool Scheduler::giveTask(Task& task) {
    int pid;
    int status;
    WorkerPool *workerPool;
    Client *client;

    //if (NULL == (client = getLeastLoadedClient()) || client->getNbrTasks() > _maxTaskPerClient) {
        if ((pid = fork()) == 0) {
            workerPool = new WorkerPool();
            return false;
        } else {
            client = new Client(pid, this, &task, _serverSocket);
            _clients.push_back(client);
        }
   /* } else {
        client->giveTask(&task);
    }*/
    return true;
}
