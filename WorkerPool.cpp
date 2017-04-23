//
// Created by thomas on 19/04/17.
//

#include <thread>
#include <iostream>
#include "WorkerPool.hpp"
#include "Plazza.hpp"

WorkerPool::WorkerPool() :
    ProcessWrapper(getpid()) {

    Plazza &p = Plazza::getInstance();
    initThreads(p.getNbrThreadsPerProc());
}

void WorkerPool::initThreads(int nbr_threads_per_proc) {
    for (int i = 0; i < nbr_threads_per_proc; i++) {
        _threads.push_back(new Worker());
    }
}

WorkerPool::~WorkerPool() {
    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        delete _threads.back();
        _threads.pop_back();
    }
}

bool WorkerPool::giveTask(Task & task) {
    Worker *t;

    for (std::list<Worker*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        t = *iter;
        if (!t->isRunning()) {
            if (t->giveTask(task))
                return true;
        }
    }
    return false;
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

void WorkerPool::setRecvEndPoint(INetworkEndPoint *recv) {
    _recvEndPoint = recv;
}

void WorkerPool::setSendEndPoint(INetworkEndPoint *send) {
    _sendEndPoint = send;
}