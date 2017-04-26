//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_TASK_HPP
#define PLAZZA_TASK_HPP

#include <string>

typedef enum Patterns
{
    PHONE_NUMBER,
    IP_ADDRESS,
    EMAIL_ADDRESS
} Patterns;

class Task {
private:
    std::string _file_path;
    enum Patterns _pattern;

public:
    Task(std::string const & file_path, enum Patterns pattern);
};


#endif //PLAZZA_TASK_HPP
