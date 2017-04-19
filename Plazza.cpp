//
// Created by thomas on 19/04/17.
//

#include <iostream>
#include "Plazza.hpp"

Plazza::Plazza(int nbr_threads_per_proc) {

}

std::queue<Task>& Plazza::getTasks() {
    return _tasks;
}