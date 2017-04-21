//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include <unistd.h>
#include "Thread.hpp"

Thread::Thread() {
    init();
}

Thread::~Thread() {

}

void Thread::run() {
    for (int i = 0; i < 10; i++) {
        std::cout << "Processing task" << std::endl;
        sleep(1);
    }
    _isRunning = false;
}

void Thread::init() {
    _isRunning = false;
    _task = NULL;
}

void Thread::join() {
    _thread.join();
}

bool Thread::start() {
    if (!_isRunning && _task) {
        _isRunning = true;
        _thread = std::thread([=] {
            run();
        });
        return true;
    }
    return false;
}

bool Thread::isRunning() {
    return _isRunning;
}

bool Thread::giveTask(Task &task) {
    if (!_isRunning && !_task) {
        _task = &task;
        return true;
    }
    return false;
}