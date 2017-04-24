//
// Created by thomas on 21/04/17.
//

#ifndef PLAZZA_WORKER_HPP
#define PLAZZA_WORKER_HPP

#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include "../common/Task.hpp"
#include "../common/Thread.hpp"
#include "../parsing/FileParsing.hpp"

class Worker : public Thread {
private:
    Task *_task;

public:
    Worker();
    ~Worker();
    bool giveTask(Task& task);
    void run();
    bool hasTask();
    void display_vector(std::vector<std::string> vec);
    void search_in_dirctory(Parsing::FileParsing *ptr, DIR *dir);
};

#endif //PLAZZA_WORKER_HPP
