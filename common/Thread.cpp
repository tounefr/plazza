//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include <unistd.h>
#include "Thread.hpp"

Thread::Thread() :
    _isRunning(false) {

}

Thread::~Thread() {

}

void Thread::join() {
    if (_isRunning)
        _thread.join();
}

bool Thread::start() {
    if (!_isRunning) {
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

void Thread::setRunning(bool running) {
    _isRunning = running;
}