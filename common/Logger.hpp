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
private:
    Logger const& _instance = Logger();

public:
    Logger();
    Logger const& getInstance();
    static void push(LogType, const std::string &where, const std::string &what);
};

#endif //PLAZZA_LOGGER_HPP
