//
// Created by thomas on 19/04/17.
//

#include <thread>
#include <iostream>
#include <sstream>
#include "WorkerPool.hpp"
#include "../Plazza.hpp"
#include "../network/ip/Socket.hpp"

WorkerPool::WorkerPool() :
    ProcessWrapper(getpid()),
    _tasks()
{
    Plazza *p = Plazza::getInstance();
    _tasks.setTimeout(EXIT_INACTIVITY_TIMEOUT);
    _socket = new Network::IP::Socket(NETWORK_LISTEN_ADDRESS, NETWORK_LISTEN_PORT);
    _socket->setTimeout(EXIT_INACTIVITY_TIMEOUT);
    initThreads(p->getNbrThreadsPerProc());
    recvPackets();
    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        (*iter)->join();
    }
}

Queue<Task*>& WorkerPool::getTasks() {
    return _tasks;
}

Network::ISocket *WorkerPool::getSocket() {
    return _socket;
}

void WorkerPool::onTaskPacket(Packet *packet) {
    std::string path;
    unsigned int pattern;
    std::stringstream &stream = packet->getStream();

    stream >> pattern;
    stream >> path;
    Logger::getInstance()->print(DEBUG, "WorkerPool", "Recv PACKET_GIVE_TASK '"+ path+"'");
    _tasks.enqueue(new Task(path, (Patterns)pattern));
}

void WorkerPool::recvPackets() {
    Packet *packet;
    Logger::getInstance()->print(DEBUG, "WorkerPool", "recv packet start");
    while ((packet = _socket->recv_packet())) {
        switch (packet->getType()) {
            case PACKET_TASK:
                onTaskPacket(packet);
                break;
            default:
                Logger::getInstance()->print(ERROR, "WorkerPool", "Recv unknown packet");
                _socket->sock_close();
                break;
        }
    }
    Logger::getInstance()->print(ERROR, "WorkerPool", "recv packet end");
}

void WorkerPool::initThreads(int nbr_threads_per_proc) {
    for (int i = 0; i < nbr_threads_per_proc; i++) {
        _threads.push_back(new Worker(this));
    }
}

WorkerPool::~WorkerPool() {
    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        delete _threads.back();
        _threads.pop_back();
    }
}

bool WorkerPool::getNbrThreads() {
    return _threads.size();
}

std::list<Worker*>& WorkerPool::getThreads() {
    return _threads;
}

unsigned int WorkerPool::getNbrThreadsRunning() {
    int c;
    Worker *t;

    c = 0;
    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        t = *iter;
        if (t->isRunning())
            c++;
    }
    return c;
}

void WorkerPool::waitThreads() {
    Worker *t;

    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        t = *iter;
        t->join();
    }
}