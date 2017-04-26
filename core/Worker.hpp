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

class Worker : public Thread {
private:
    Task *_task;
    Parsing::FileParsing _fileParsing;
    Queue<Task*>& _tasks;
    std::vector<std::string> _patterns;

public:
    Worker(Queue<Task*>& _tasks);
    ~Worker();
    virtual void run();
    bool hasTask();
    void printPatternsGrabbed();

    void display_vector(std::vector<std::string> vec);
    void search_in_dirctory(Parsing::FileParsing *ptr, DIR *dir);
};

#endif //PLAZZA_WORKER_HPP
