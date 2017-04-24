//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PLAZZA_HPP
#define PLAZZA_PLAZZA_HPP

#include <queue>
#include "common/Thread.hpp"
#include "common/Task.hpp"
#include "common/Queue.hpp"
#include "core/Scheduler.hpp"
#include "parsing/InstructionsParsing.hpp"

# define THREADS_PER_PROC 5

class Plazza {
private:
    Queue<Task*> _pendingTasks;
    Scheduler _scheduler;
    int _nbr_threads_per_proc;
    Parsing::InstructionsParsing _instructionsParsing;
    bool _running;

public:
    Plazza();
    static Plazza *getInstance();
    ~Plazza();
    Queue<Task*>& getTasks();
    void setNbrThreadsPerProc(int nbrThreadPerProc);
    Scheduler& getScheduler();
    void fetchInstructionsLoop();
    void start();
    int& getNbrThreadsPerProc();
};

#endif //PLAZZA_PLAZZA_HPP
