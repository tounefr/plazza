//
// Created by thomas on 19/04/17.
//

#include <thread>
#include <iostream>
#include "WorkerPool.hpp"
#include "../Plazza.hpp"
#include "../network/ip/Socket.hpp"

WorkerPool::WorkerPool() :
    ProcessWrapper(getpid()),
    _tasks()
{
    Plazza *p = Plazza::getInstance();
    initThreads(p->getNbrThreadsPerProc());
    recvPackets();
    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        (*iter)->join();
    }
}

void WorkerPool::recvPackets() {
    _socket = new Network::IP::Socket("127.0.0.1", 8888);
    PacketGiveTask *packetGiveTask;

    while ((packetGiveTask = _socket->recv_packet())) {
        _tasks.enqueue(new Task(std::string(packetGiveTask->path), packetGiveTask->type));
        std::cout << "Recv task : " << packetGiveTask->path << " " << packetGiveTask->type << std::endl;
    }
}

void WorkerPool::initThreads(int nbr_threads_per_proc) {
    for (int i = 0; i < nbr_threads_per_proc; i++) {
        _threads.push_back(new Worker(_tasks));
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