//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_WORKERPOOL_HPP
#define PLAZZA_WORKERPOOL_HPP

#include <list>
#include <queue>
#include <sys/types.h>
#include <unistd.h>
#include "Worker.hpp"
#include "ProcessWrapper.hpp"
#include "../common/Task.hpp"
#include "../network/ISocket.hpp"
#include "../network/ip/Socket.hpp"

class WorkerPool : public ProcessWrapper {
private:
    std::list<Worker*> _threads;
    Network::ISocket *_socket;
    Queue<Task*> _tasks;

public:

    WorkerPool();
    ~WorkerPool();
    bool getNbrThreads();
    std::list<Worker*>& getThreads();
    unsigned int getNbrThreadsRunning();
    void initThreads(int nbr_threads_per_proc);
    void waitThreads();
    void recvPackets();
    void onTaskPacket(Packet *packet);
    Network::ISocket *getSocket();

};


#endif //PLAZZA_WORKERPOOL_HPP
