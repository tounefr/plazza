//
// Created by thomas on 21/04/17.
//

#include <iostream>
#include <unistd.h>
#include "Worker.hpp"

Worker::Worker() :
        _task(NULL),
        Thread() {

}

Worker::~Worker() {

}

void Worker::run() {
    for (int i = 0; i < 10; i++) {
        std::cout << "[thread " << i << "]" << "Processing task " << _task << std::endl;
        sleep(1);
    }
    setRunning(false);
}

bool Worker::giveTask(Task& task) {
    setRunning(true);
    _task = &task;
    start();
}

bool Worker::hasTask() {
    return (_task != NULL);
}