//
// Created by thomas on 24/04/17.
//

#ifndef PLAZZA_INSTRUCTIONSPARSING_HPP
#define PLAZZA_INSTRUCTIONSPARSING_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include "../common/Queue.hpp"
#include "../common/Task.hpp"

namespace Parsing {
    class InstructionsParsing : public Thread {
    public:
        InstructionsParsing();

        void split(const std::string &str, char c, std::vector<std::string> &vect);

        void sanitize_string(std::string &line);

        bool get_pattern(const std::string &word, Patterns &pattern);

        int get_task(const std::string &task, Queue<Task *> &taskList);

        virtual void run();
    };
}


#endif //PLAZZA_INSTRUCTIONSPARSING_HPP
