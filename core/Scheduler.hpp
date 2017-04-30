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
    std::list<Client*> _clients;
    Network::IServerSocket* _serverSocket;
    size_t _min_process;
    size_t _max_process;
    unsigned int _maxTaskPerClient;

public:
    Scheduler();
    ~Scheduler();
    bool giveTask(Task &task);
    Client* getLeastLoadedClient();
    virtual void run();
    size_t& getMinProcess();
    size_t& getMaxProcess();
    bool newProcess(Task*);
    void removeClient(Client *);
    Network::IServerSocket* getServerSocket();
};

#endif //PLAZZA_SCHEDULER_H
