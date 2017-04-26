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

Client::Client(int pid,
               Scheduler *scheduler,
               Task *task,
               Network::IServerSocket *serverSocket) :
        Thread(),
        ProcessWrapper(pid),
        _scheduler(scheduler),
        _nbrTasks(0),
        _serverSocket(serverSocket)
{
    _tasks.enqueue(task);
    start();
}

int& Client::getNbrTasks() {
    return _nbrTasks;
}

bool Client::giveTask(Task* task) {
    PacketGiveTask packet;

    memset(packet.path, 0, sizeof(packet.path));
    memcpy(&packet.path, task->getFilePath(), strlen(task->getFilePath()));
    packet.type = task->getPattern();
    std::cout << _socket << std::endl;
    return  _socket->sock_send(&packet);
}

void Client::run() {
    std::cout << "Waiting for connection" << std::endl;
    _socket = _serverSocket->sock_accept();
    std::cout << "New connection ! " << std::endl;
    while (1) {
        Task *task = _tasks.dequeue();
        if (!giveTask(task))
            break;
        std::cout << "Task sent" << std::endl;
        _nbrTasks++;
    }
    waitpid(_pid, &_status, 0);
    _nbrTasks--;
}