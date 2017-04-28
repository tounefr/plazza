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

# define DISP_INFO      1 << 0
# define DISP_ERROR     1 << 1
# define DISP_DEBUG     1 << 2
# define DISP_WARNING   1 << 3

enum LogType {
    INFO    = 0,
    ERROR   = 1,
    DEBUG   = 2,
    WARNING = 3
};

class Logger {
public:
    static Logger* getInstance();
    std::ofstream outFile;
    std::mutex OutLock;
    void print(LogType, const std::string &where, const std::string &what);
    ~Logger();

private:
    Logger(std::string outFile_path);
    static Logger* m_pInstance;

    unsigned char _displayMode;
    unsigned char setDisplay(unsigned char mode);
};

#endif //PLAZZA_LOGGER_HPP
