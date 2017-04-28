//
// Created by thomas on 21/04/17.
//

#include "../common/Logger.hpp"
#include "Worker.hpp"

Worker::Worker(Queue<Task*>& _tasks, Network::ISocket *socket) :
        _task(NULL),
        _tasks(_tasks),
        _fileParsing(),
        _socket(socket),
        Thread() {
    start();
}

Worker::~Worker() {
}

/*
void Worker::printPatternsGrabbed() {
    if (_patterns.size() > 0) {
        Logger::getInstance()->print(DEBUG, "Worker", "Task finished");
        for (std::vector<std::string>::iterator iter = _patterns.begin(); iter != _patterns.end(); iter++) {
            std::cout << *iter << std::endl;
        }
    }
}
 */

void Worker::onTaskFinished() {
    Logger::getInstance()->print(DEBUG, "Worker", "Task finished");

    for (std::vector<std::string>::iterator iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        std::cout << *iter << std::endl;
    }
    /*
    std::string buffer;
    std::stringstream ss(buffer);
    ss << PACKET_TASK_RESULT;
    for (std::vector<std::string>::iterator iter = _patterns.begin(); iter != _patterns.end(); iter++)
        ss << *iter << ";";
    buffer = ss.str();
    _socket->sock_send(PACKET_TASK_RESULT, &buffer);
     */
}

void Worker::run() {
    Logger::getInstance()->print(DEBUG, "Worker", "Worker ready");
    while (1) {
        setRunning(false);
        _task = _tasks.dequeue();
        setRunning(true);
        Logger::getInstance()->print(DEBUG, "Worker", "Processsing task '" + std::string(_task->getFilePath()) + "'");

        _fileParsing.set_path(_task->getFilePath());
        _fileParsing.set_field(_task->getPattern());
        _patterns = _fileParsing.get_list();
        onTaskFinished();
    }
}

bool Worker::hasTask() {
    return (_task != NULL);
}