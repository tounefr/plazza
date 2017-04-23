//
// Created by thomas on 19/04/17.
//

#include "Task.hpp"

Task::Task(std::string const & file_path, enum Patterns pattern) :
        _file_path(file_path),
        _pattern(pattern) {

}