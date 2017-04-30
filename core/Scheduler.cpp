
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../Plazza.hpp"
#include "Scheduler.hpp"
#include "../common/Queue.hpp"
#include "../network/ip/Socket.hpp"

Scheduler::Scheduler() :
        Thread(),
        _clients(),
        _min_process(_SC_NPROCESSORS_ONLN),
        _max_process(1),
        _maxTaskPerClient(10)
{
    _serverSocket = new Network::IP::ServerSocket(NETWORK_LISTEN_PORT);
    if (!_serverSocket->sock_listen())
        Plazza::getInstance()->setRunning(false);
}

Scheduler::~Scheduler() {
}

size_t& Scheduler::getMinProcess() {
    return _min_process;
}

size_t& Scheduler::getMaxProcess() {
    return _max_process;
}

void Scheduler::run() {
    Logger::getInstance()->print(DEBUG, "Scheduler", "Starting Scheduler");
    Task *t;

    // On initialise <_min_process> à l'avance
    for (int i = 0; i < getMinProcess(); i++) {
        if (!newProcess(NULL))
            return;
    }
    sleep(1); // TODO: crade: cond vars
    while (1) {
        try {
            t = Plazza::getInstance()->getTasks().dequeue();
        }  catch (std::runtime_error const& e) {
            break;
        }
        Logger::getInstance()->print(DEBUG, "Scheduler", "Handling task '"+std::string(t->getFilePath())+"'");
        try {
            if (!giveTask(*t))
                break;
        } catch (std::runtime_error const &e) {
            break;
        }
    }
    Logger::getInstance()->print(ERROR, "Scheduler", "Ending");
}

Client* Scheduler::getLeastLoadedClient() {
    Client *least;
    Client *client;

    least = NULL;
    for (std::list<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); iter++) {
        client = *iter;
        if (client->isReady() && (least == NULL ||
                (least->getNbrTasks() > client->getNbrTasks())))
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
        client = new Client(pid, this, task);
        _clients.push_back(client);
    }
    return true;
}

void Scheduler::removeClient(Client *client) {
    _clients.remove(client);
}

Network::IServerSocket* Scheduler::getServerSocket() {
    return _serverSocket;
}

bool Scheduler::giveTask(Task& task) {
    Client *client;

    if (!(client = getLeastLoadedClient()))
        return false;
    if (client->hasExited() || !client->giveTask(&task)) {
        removeClient(client);
        return giveTask(task);
    }
    return true;
}
