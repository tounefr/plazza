//
// Created by thomas on 19/04/17.
//

#include <unistd.h>
#include "ProcessWrapper.hpp"

ProcessWrapper::ProcessWrapper() {
    _pid = getpid();
}