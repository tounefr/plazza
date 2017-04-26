//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_SCHEDULER_H
#define PLAZZA_SCHEDULER_H

#include <vector>
#include <map>
#include <list>
#include "WorkerPool.hpp"
#include "../network/IServerSocket.hpp"
#include "../network/ip/ServerSocket.hpp"
#include "../common/Client.hpp"

class Scheduler : public Thread {
private:
//    std::map<ISocket*, int> _clients;
    std::list<Client*> _clients;
    Network::IServerSocket* _serverSocket;
    unsigned int _maxTaskPerClient;


//    std::list<WorkerPool*> _clients;

public:
    Scheduler();
    ~Scheduler();
    bool giveTask(Task &task);
    Client* getLeastLoadedClient();
    virtual void run();
};


#endif //PLAZZA_SCHEDULER_H
