//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PLAZZA_HPP
#define PLAZZA_PLAZZA_HPP

#include <queue>
#include "Thread.hpp"
#include "Task.hpp"
#include "Scheduler.hpp"

# define THREADS_PER_PROC 5

class Plazza {
private:
    std::queue<Task*> _pendingTasks;
    Scheduler *_scheduler;
    int _nbr_threads_per_proc;
    bool _running;

public:
    Plazza(int const& nbr_threads_per_proc);
    static Plazza& getInstance();
    ~Plazza();
    std::queue<Task*>& getTasks();
    void setNbrThreadsPerProc(int nbrThreadPerProc);
    Scheduler& getScheduler();
    void fetchInstructionsLoop();
    Task& popTask();
    Task& pushTask(Task &);
    unsigned int nbrPendingTasks();
    void start();
    int& getNbrThreadsPerProc();
};

#endif //PLAZZA_PLAZZA_HPP