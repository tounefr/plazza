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
//    _tasks.enqueue(task);
    std::string buffer;
    std::stringstream ss(buffer);
    ss << task->getPattern();
    ss << task->getFilePath();
    buffer = ss.str();
    if (!_socket->sock_send(PACKET_TASK, &buffer))
        return false;
    Logger::getInstance()->print(DEBUG, "Client", "PACKET_TASK sent");
    return true;
}

void Client::onGiveTaskPacket(Packet* packet) {

/*    Logger::getInstance()->print(DEBUG, "Client", "PACKET_GIVE_TASK");
    Task *task = _tasks.dequeue();

    std::string buffer;
    std::stringstream ss(buffer);
    ss << task->getPattern();
    ss << task->getFilePath();
    buffer = ss.str();
    if (!_socket->sock_send(PACKET_TASK, &buffer))
        return;
    Logger::getInstance()->print(DEBUG, "Client", "PACKET_TASK sent");
    _nbrTasks++;*/
}

void Client::onTaskResultPacket(Packet* packet) {
    std::string buffer;
    std::stringstream ss(buffer);
    std::string tasks;

    ss >> tasks;
    Logger::getInstance()->print(DEBUG, "Client", "Tasks result : " + tasks);
    Logger::getInstance()->print(DEBUG, "Client", "PACKET_TASK_RESULT");
}

void Client::run() {
    Logger::getInstance()->print(DEBUG, "Client", "Waiting for connection");
    _socket = _serverSocket->sock_accept();
    Logger::getInstance()->print(DEBUG, "Client", "New connection !");

    Packet *packet;
    while ((packet = _socket->recv_packet())) {
        Logger::getInstance()->print(DEBUG, "Client", "Recv packet");
        switch (packet->getType()) {
            case PACKET_GIVE_TASK:
                onGiveTaskPacket(packet);
                break;
            case PACKET_TASK_RESULT:
                onTaskResultPacket(packet);
                break;
            default:
                Logger::getInstance()->print(DEBUG, "Client", "Recv unknown packet");
                _socket->sock_close();
                break;
        }
    }
    waitpid(_pid, &_status, 0);
    Logger::getInstance()->print(DEBUG, "Client", "Child Process pid='"+std::to_string(_pid)+"'");
    if (WIFSTOPPED(_status)) {
        Logger::getInstance()->print(DEBUG, "Client", "WSTOPPED == true");
    }
    _exited = true;
    _nbrTasks--;
}