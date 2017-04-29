//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PLAZZA_HPP
#define PLAZZA_PLAZZA_HPP

#include <queue>
#include "common/Thread.hpp"
#include "common/Task.hpp"
#include "common/Queue.hpp"
#include "common/Logger.hpp"
#include "core/Scheduler.hpp"
#include "parsing/InstructionsParsing.hpp"

# define THREADS_PER_PROC 5
# define NETWORK_LISTEN_ADDRESS "127.0.0.1"
# define NETWORK_LISTEN_PORT 8888
# define LOG_FILE_PATH "log"

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
    int start(int nbr_threads_per_proc);
    int& getNbrThreadsPerProc();
    bool& isRunning();
    void setRunning(bool running);
};

#endif //PLAZZA_PLAZZA_HPP
