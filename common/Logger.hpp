//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_LOGGER_HPP
#define PLAZZA_LOGGER_HPP

#include "../Plazza.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>

enum LogType {
    INFO,
    ERROR,
    DEBUG,
    WARNING
};

class Logger {
public:
    static Logger* getInstance();
    std::ofstream outFile;
    void print(LogType, const std::string &where, const std::string &what);
    ~Logger();

private:
    Logger(std::string outFile_path);
    static Logger* m_pInstance;
};

#endif //PLAZZA_LOGGER_HPP
