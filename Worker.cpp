//
// Created by thomas on 19/04/17.
//

#include <thread>
#include "Worker.hpp"
#include "Plazza.hpp"

Worker::Worker() :
    ProcessWrapper() {

    Plazza &p = Plazza::getInstance();
    initThreads(p.getNbrThreadsPerProc());
}

void Worker::initThreads(int nbr_threads_per_proc) {
    for (int i = 0; i < nbr_threads_per_proc; i++) {
        _threads.push_back(new Thread());
    }
}

Worker::~Worker() {
    for (std::list<Thread*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        delete _threads.back();
        _threads.pop_back();
    }
}

bool Worker::giveTask(Task & task) {
    Thread *t;

    for (std::list<Thread*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        t = *iter;
        if (!t->isRunning()) {
            if (t->giveTask(task))
                return true;
        }
    }
    return false;
}

bool Worker::getNbrThreads() {
    return _threads.size();
}

std::list<Thread*>& Worker::getThreads() {
    return _threads;
}

bool Worker::getNbrThreadsRunning() {
    int c;
    Thread *t;

    c = 0;
    for (std::list<Thread*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++) {
        t = *iter;
        if (t->isRunning())
            c++;
    }
    return c;
}
