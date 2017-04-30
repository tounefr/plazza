//
// Created by thomas on 21/04/17.
//

#include "../common/Logger.hpp"
#include "WorkerPool.hpp"
#include "Worker.hpp"

Worker::Worker(WorkerPool *workerPool) :
        _task(NULL),
        _fileParsing(),
        _workerPool(workerPool),
        Thread() {
    start();
}

Worker::~Worker() {
}

void Worker::onTaskFinished() {
    std::cout << "task finished " << _task->getFilePath() << std::endl;
    Logger::getInstance()->print(DEBUG, "Worker", "Task finished '"+ std::string(_task->getFilePath()) +"'");
    for (std::vector<std::string>::iterator iter = _patterns.begin(); iter != _patterns.end(); iter++) {
          std::cout << *iter << std::endl;
    }
}

void Worker::run() {
    Packet *packet;
    Logger::getInstance()->print(DEBUG, "Worker", "Worker ready");
    while (1) {
        setRunning(false);
        try {
            _task = _workerPool->getTasks().dequeue();
        } catch (std::runtime_error const &e) {
            break;
        }
        setRunning(true);
        Logger::getInstance()->print(DEBUG, "Worker", "Processsing task field='"+std::to_string(_task->getPattern())+"' path='" + std::string(_task->getFilePath()) + "'");

        /*
        Parsing::FileParsing parsing = Parsing::FileParsing();
        parsing.set_path(_task->getFilePath());
        parsing.set_field(_task->getPattern());
        _patterns = parsing.get_list();
         */

        onTaskFinished();
    }
    Logger::getInstance()->print(DEBUG, "Worker", "Worker end");
}

bool Worker::hasTask() {
    return (_task != NULL);
}