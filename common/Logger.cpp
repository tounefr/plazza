//
// Created by thomas on 19/04/17.
//

#include "Logger.hpp"
#include <sstream>

std::mutex OutLock;
std::ofstream outfile;

Logger::Logger(const std::string outFile_path) {
    outFile.open(outFile_path, std::ofstream::out | std::ofstream::trunc);
    outFile.close();
}

Logger::~Logger() {
    outFile.close();
}

Logger* Logger::getInstance() {
    if (!m_pInstance)
        m_pInstance = new Logger(LOG_FILE_PATH);
    return m_pInstance;
}

void Logger::print(LogType type, const std::string &where, const std::string &what) {

    OutLock.lock();
    outFile.open(LOG_FILE_PATH, std::ofstream::out | std::ofstream::app);

    std::string Types[] = {"INFO", "ERROR", "DEBUG", "WARNING"};
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::stringstream ss;

    ss << ltm->tm_mday << "/"
       << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year << " "
       << 1 + ltm->tm_hour << ":"
       << 1 + ltm->tm_min << ":"
       << 1 + ltm->tm_sec << " "
       << " [" << Types[type] << "] "
       << where << ": "
       << what << std::endl;

    if (outFile.is_open())
        outFile << ss.str();
    std::cout << ss.str();

    outFile.close();
    OutLock.unlock();
}