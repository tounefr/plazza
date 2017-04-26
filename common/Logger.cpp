//
// Created by thomas on 19/04/17.
//

#include "Logger.hpp"

std::mutex OutLock;

Logger::Logger() {

}

Logger* Logger::getInstance() {
    static Logger* l = new Logger();
    return l;
}

void Logger::print(LogType type, const std::string &where, const std::string &what) {

    OutLock.lock();

    std::string Types[] = {"INFO", "ERROR", "DEBUG"};
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::cout << ltm->tm_mday << "/"
              << 1 + ltm->tm_mon << "/"
              << 1900 + ltm->tm_year << " "
              << 1 + ltm->tm_hour << ":"
              << 1 + ltm->tm_min << ":"
              << 1 + ltm->tm_sec << " "
              << " [" << Types[type] << "] "
              << "[" << where << "] : "
              << what << std::endl;

    OutLock.unlock();
}