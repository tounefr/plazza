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
#include "INetworkEndPoint.hpp"
#include "Task.hpp"

class WorkerPool : public ProcessWrapper {
private:
    std::list<Worker*> _threads;
    INetworkEndPoint *_recvEndPoint;
    INetworkEndPoint *_sendEndPoint;

public:

    WorkerPool();
    ~WorkerPool();
    bool giveTask(Task& task);
    bool getNbrThreads();
    std::list<Worker*>& getThreads();
    unsigned int getNbrThreadsRunning();
    void initThreads(int nbr_threads_per_proc);
    void waitThreads();
    void setRecvEndPoint(INetworkEndPoint *);
    void setSendEndPoint(INetworkEndPoint *);


};


#endif //PLAZZA_WORKERPOOL_HPP
