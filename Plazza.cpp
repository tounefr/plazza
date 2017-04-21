//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/select.h>
#include <assert.h>
#include "Plazza.hpp"

Plazza::Plazza(int const& nbr_threads_per_proc) :
        _nbr_threads_per_proc(nbr_threads_per_proc),
        _running(false) {

}

Plazza& Plazza::getInstance() {
    static Plazza* instance = new Plazza(THREADS_PER_PROC);

    return *instance;
}

void Plazza::start() {
    _running = true;
    _scheduler = new Scheduler();
    while (1) {
        pushTask(*new Task("./test.html", PHONE_NUMBER));
        sleep(1);
    }
    _scheduler->join();
//    fetchInstructionsLoop();
}

void Plazza::fetchInstructionsLoop() {
    void *buffer;

    struct timeval select_timeout = {1, 100}; // wait every 100 ms
    fd_set rfds;
    int selectrv;

    buffer = malloc(1000);
    assert(buffer != NULL);

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    while (1) {
        select_timeout.tv_sec = 1;
        select_timeout.tv_usec = 0;
        selectrv = select(1, &rfds, NULL, NULL, &select_timeout);
        switch (selectrv) {
            case -1:
                std::cout << "select failed" << std::endl;
                break;
            case 0:
                std::cout << "No data" << std::endl;
                break;
            default:
                std::cout << "Data available" << std::endl;
                //read(0, buffer, 1000);
                break;

        }
    }
}

Plazza::~Plazza() {
    if (this->_scheduler)
        delete this->_scheduler;
}

std::queue<Task*>& Plazza::getTasks() {
    return _pendingTasks;
}

void Plazza::setNbrThreadsPerProc(int nbrThreadPerProc) {
    _nbr_threads_per_proc = nbrThreadPerProc;
}

Scheduler& Plazza::getScheduler() {
    return *_scheduler;
}

Task& Plazza::popTask() {
    _pendingTasks.pop();
}

Task& Plazza::pushTask(Task& task) {
    _pendingTasks.push(&task);
}

unsigned int Plazza::nbrPendingTasks() {
    return _pendingTasks.size();
}

int& Plazza::getNbrThreadsPerProc() {
    return _nbr_threads_per_proc;
}