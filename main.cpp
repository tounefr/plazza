
#include "Plazza.hpp"
#include "core/Scheduler.hpp"
#include "core/WorkerPool.hpp"
#include <iostream>

int main() {

//    Plazza &p = Plazza::getInstance();

    Plazza &p = Plazza::getInstance();
    p.pushTask(*new Task("./test.html", PHONE_NUMBER));
    p.start();

//    std::cout << &Plazza::getInstance() << std::endl;
    return 0;
    /*
    p.setNbrThreadsPerProc(5);

    Scheduler *scheduler = p.getScheduler();
    scheduler->giveTask(new Task("./test.html", PHONE_NUMBER));
    scheduler->giveTask(new Task("./test.html", EMAIL));
     */

    return 0;
}