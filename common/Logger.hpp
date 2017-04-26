//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_LOGGER_HPP
#define PLAZZA_LOGGER_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <mutex>

enum LogType {
    INFO,
    ERROR,
    DEBUG
};

class Logger {

public:
    Logger();
    Logger* getInstance();
    static void print(LogType, const std::string &where, const std::string &what);
};

#endif //PLAZZA_LOGGER_HPP
