//
// Created by thomas on 21/04/17.
//

#ifndef PLAZZA_WORKER_HPP
#define PLAZZA_WORKER_HPP

#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include "../common/Task.hpp"
#include "../common/Thread.hpp"
#include "../parsing/FileParsing.hpp"
#include "../common/Queue.hpp"
#include "../network/ISocket.hpp"

class WorkerPool;

class Worker : public Thread {
private:
    Task *_task;
    Parsing::FileParsing _fileParsing;
    std::vector<std::string> _patterns;
    WorkerPool *_workerPool;

public:
    Worker(WorkerPool *workerPool);
    ~Worker();
    virtual void run();
    bool hasTask();
    void onTaskFinished();
};

#endif //PLAZZA_WORKER_HPP
