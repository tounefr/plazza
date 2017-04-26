//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/select.h>
#include <assert.h>
#include "common/Queue.hpp"
#include "Plazza.hpp"

Plazza::Plazza() :
        _running(true),
        _pendingTasks(),
        _scheduler(),
        _nbr_threads_per_proc(THREADS_PER_PROC),
        _instructionsParsing()
{
}

Plazza* Plazza::getInstance() {
    static Plazza* p = new Plazza();
    return p;
}

void Plazza::start() {
    if (isRunning()) {
        _instructionsParsing.start();
        _scheduler.start();

        _scheduler.join();
        _instructionsParsing.join();
    }
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

}

Queue<Task*>& Plazza::getTasks() {
    return _pendingTasks;
}

void Plazza::setNbrThreadsPerProc(int nbrThreadPerProc) {
    _nbr_threads_per_proc = nbrThreadPerProc;
}

Scheduler& Plazza::getScheduler() {
    return _scheduler;
}

int& Plazza::getNbrThreadsPerProc() {
    return _nbr_threads_per_proc;
}

bool& Plazza::isRunning() {
    return _running;
}

void Plazza::setRunning(bool running) {
    _running = running;
}