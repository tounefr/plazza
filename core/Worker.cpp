//
// Created by thomas on 21/04/17.
//

#include "Worker.hpp"

Worker::Worker(Queue<Task*>& _tasks) :
        _task(NULL),
        _tasks(_tasks),
        _fileParsing(),
        Thread() {
    start();
}

Worker::~Worker() {
}

void Worker::printPatternsGrabbed() {
    std::cout << "[thread] task finished : " << _patterns.size() << std::endl;
    for (std::vector<std::string>::iterator iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        std::cout << *iter << std::endl;
    }
}

void Worker::run() {
    Task *task;

    while (1) {
        setRunning(false);
        task = _tasks.dequeue();
        setRunning(true);
        std::cout << "[thread] Processing task " << task->getFilePath() << std::endl;
        _fileParsing.set_path(task->getFilePath());
        _fileParsing.set_field(task->getPattern());
        _patterns = _fileParsing.get_list();
        printPatternsGrabbed();
    }
}

bool Worker::hasTask() {
    return (_task != NULL);
}


void Worker::display_vector(std::vector<std::string> vec)
{
    while (!vec.empty()) {
        std::cout << vec.back() << std::endl;
        vec.pop_back();
    }
}

void Worker::search_in_dirctory(Parsing::FileParsing *ptr, DIR *dir)
{
    struct dirent   *dir_infos;
    std::string     mem_str;

    while ((dir_infos = readdir(dir)))
    {
        if (dir_infos->d_name[0] != '.') {
            mem_str = ptr->get_path();
            ptr->set_path(mem_str + "/" + dir_infos->d_name);
            if (dir_infos->d_type != DT_DIR) {
                display_vector(ptr->get_list());
            }
            else
                search_in_dirctory(ptr, opendir(ptr->get_path().c_str()));
            ptr->set_path(mem_str);
        }
    }
}