//
// Created by thomas on 19/04/17.
//

#include "Logger.hpp"

Logger::Logger() {

}

Logger const& Logger::getInstance() {
    return _instance;
}