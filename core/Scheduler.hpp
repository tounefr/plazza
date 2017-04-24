//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_SCHEDULER_H
#define PLAZZA_SCHEDULER_H

#include <vector>
#include "WorkerPool.hpp"
#include "../network/IServerSocket.hpp"
#include "../network/ip/ServerSocket.hpp"

class Scheduler : public Thread {
private:
    std::list<WorkerPool*> _clients;
    Network::IServerSocket *_serverSocket;

public:
    Scheduler();
    ~Scheduler();
    bool giveTask(Task &task);
    virtual void run();
};


#endif //PLAZZA_SCHEDULER_H
