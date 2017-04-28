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

class Worker : public Thread {
private:
    Task *_task;
    Parsing::FileParsing _fileParsing;
    Queue<Task*>& _tasks;
    std::vector<std::string> _patterns;
    Network::ISocket *_socket;

public:
    Worker(Queue<Task*>& _tasks, Network::ISocket* socket);
    ~Worker();
    virtual void run();
    bool hasTask();
    void onTaskFinished();
};

#endif //PLAZZA_WORKER_HPP
