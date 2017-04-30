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
        _instructionsParsing() {
    _pendingTasks.setTimeout(EXIT_INACTIVITY_TIMEOUT);
}

Plazza* Plazza::getInstance() {
    static Plazza* p = new Plazza();
    return p;
}

int Plazza::start(int nbr_threads_per_proc) {
    _nbr_threads_per_proc = nbr_threads_per_proc;
    _instructionsParsing.start();
    _instructionsParsing.join();
    _scheduler.start();
    _scheduler.join();
    return 1;
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