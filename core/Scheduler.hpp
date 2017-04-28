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

    void infos_process() {
        /*
        std::cout << "Nbr de process : " << _clients.size();
        Client *client;
        int i = 0;
        int tasks = 0;
        for (std::list<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); iter++) {
            client = *iter;
            std::cout << "Client " << i << " : tasks=" << client->getNbrTasks() << std::endl;
            tasks += client->getNbrTasks();
            i++;
        }
        std::cout << "Total tasks : " << tasks << std::endl;
        std::cout << std::endl;
         */
    };
};

#endif //PLAZZA_SCHEDULER_H
