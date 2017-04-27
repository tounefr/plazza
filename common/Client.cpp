//
// Created by thomas on 24/04/17.
//

#include <sys/types.h>
#include <iostream>
#include <sstream>
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
    std::string buffer;
    std::stringstream ss(buffer);

    if (isReady()) {
        ss << task->getPattern();
        ss << task->getFilePath();
        buffer = ss.str();
        _socket->sock_send(PACKET_GIVE_TASK, &buffer);
//        Logger::getInstance()->print(DEBUG, "Client", "sock_send " + ss.str());
        _nbrTasks++;
    }
    return true;
}

void Client::run() {
    Logger::getInstance()->print(DEBUG, "Client", "Waiting for connection");
    _socket = _serverSocket->sock_accept();
    Logger::getInstance()->print(DEBUG, "Client", "New connection !");
    while (Plazza::getInstance()->isRunning()) {
        Task *task = _tasks.dequeue();
        if (!giveTask(task))
            break;
        Logger::getInstance()->print(DEBUG, "Client", "Task sent");
    }
    waitpid(_pid, &_status, 0);
    _nbrTasks--;
}