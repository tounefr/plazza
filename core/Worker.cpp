//
// Created by thomas on 21/04/17.
//

#include "Worker.hpp"

Worker::Worker() :
        _task(NULL),
        Thread() {

}

Worker::~Worker() {

}

void Worker::run() {
    for (int i = 0; i < 10; i++) {
        /*
         *     Parsing *ptr = Parsing::Get();
    ptr->set_field(PHONE_NUMBER);
    ptr->set_path("/home/aurelien/rendu/CPP/plazza/srcs");
    DIR      *dir;

    dir = opendir(ptr->get_path().c_str());
    search_in_dirctory(ptr, dir);
}
         */
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