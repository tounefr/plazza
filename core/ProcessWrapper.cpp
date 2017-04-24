//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include "ProcessWrapper.hpp"

ProcessWrapper::ProcessWrapper(int pid) :
    _pid(pid)
{
}

void ProcessWrapper::setPid(int pid) {
    _pid = pid;
}

int& ProcessWrapper::getPid() {
    return _pid;
}