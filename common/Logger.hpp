//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_LOGGER_HPP
#define PLAZZA_LOGGER_HPP

#include <iostream>
#include <string>

class Logger {
private:
    Logger const& _instance = Logger();

public:
    Logger();
    Logger const& getInstance();
};


#endif //PLAZZA_LOGGER_HPP
