//
// Created by thomas on 24/04/17.
//

#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>
#include "Client.hpp"
#include <unistd.h>
#include <string.h>
#include "../core/Scheduler.hpp"
#include "../network/Packet.hpp"
#include "../Plazza.hpp"

Client::Client(int pid,
               Scheduler *scheduler,
               Task *task,
               Network::IServerSocket *serverSocket) :
        Thread(),
        ProcessWrapper(pid),
        _scheduler(scheduler),
        _socket(NULL),
        _nbrTasks(0),
        _serverSocket(serverSocket)
{
    if (task != NULL)
        _tasks.enqueue(task);
    start();
}

int& Client::getNbrTasks() {
    return _nbrTasks;
}

bool Client::isReady() {
    return (_socket != NULL);
}

bool Client::giveTask(Task* task) {
    PacketGiveTask packet;

    if (isReady()) {
        memset(packet.path, 0, sizeof(packet.path));
//    memcpy(packet.path, task->getFilePath(), strlen(task->getFilePath()));
        //  packet.type = task->getPattern();
        _socket->sock_send(&packet);
        _nbrTasks++;
    }
    return true;
}

void Client::run() {
    std::cout << "Waiting for connection" << std::endl;
    _socket = _serverSocket->sock_accept();
    std::cout << "New connection ! " << std::endl;
    while (Plazza::getInstance()->isRunning()) {
        Task *task = _tasks.dequeue();
        if (!giveTask(task))
            break;
        std::cout << "Task sent" << std::endl;
    }
    waitpid(_pid, &_status, 0);
    _nbrTasks--;
}