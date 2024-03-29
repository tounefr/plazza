//
// Created by thomas on 24/04/17.
//

#ifndef PLAZZA_CLIENT_HPP
#define PLAZZA_CLIENT_HPP

#include "../common/Thread.hpp"
#include "../core/ProcessWrapper.hpp"
#include "../network/ISocket.hpp"
#include "../network/IServerSocket.hpp"
#include "../common/Queue.hpp"

class Scheduler;

class Client : public Thread, public ProcessWrapper {
private:
    Network::ISocket *_socket;
    Scheduler *_scheduler;
    int _nbrTasks;
    bool _ready;
    Queue<Task*> _tasks;

public:
    Client(int pid, Scheduler *scheduler, Task *task);
    int& getNbrTasks();
    bool giveTask(Task* task);
    bool isReady();
    void onGiveTaskPacket(Packet*);
    void onTaskResultPacket(Packet*);

    virtual void run();
};


#endif //PLAZZA_CLIENT_HPP
