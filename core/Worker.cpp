//
// Created by thomas on 21/04/17.
//

#include "../common/Logger.hpp"
#include "WorkerPool.hpp"
#include "Worker.hpp"

Worker::Worker(Queue<Task*>& _tasks, WorkerPool *workerPool) :
        _task(NULL),
        _tasks(_tasks),
        _fileParsing(),
        _workerPool(workerPool),
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
    Logger::getInstance()->print(DEBUG, "Worker", "Task finished '"+ std::string(_task->getFilePath()) +"'");

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
    Packet *packet;
    Logger::getInstance()->print(DEBUG, "Worker", "Worker ready");
    while (1) {
        /*
        std::string buffer;
        std::stringstream ss(buffer);
        buffer = ss.str();
        _workerPool->getSocket()->sock_send(PACKET_GIVE_TASK, &buffer);
        Logger::getInstance()->print(DEBUG, "Worker", "PACKET_GIVE_TASK");
         */

        setRunning(false);
        _task = _tasks.dequeue();
        setRunning(true);
        Logger::getInstance()->print(DEBUG, "Worker", "Processsing task '" + std::string(_task->getFilePath()) + "'");
        _fileParsing.set_path(_task->getFilePath());
        _fileParsing.set_field(_task->getPattern());
        _patterns = _fileParsing.get_list();
        onTaskFinished();
    }
    Logger::getInstance()->print(DEBUG, "Worker", "Worker end");
}

bool Worker::hasTask() {
    return (_task != NULL);
}