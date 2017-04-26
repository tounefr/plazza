//
// Created by thomas on 24/04/17.
//

#include "../Plazza.hpp"
#include "../common/Thread.hpp"
#include "InstructionsParsing.hpp"

using namespace Parsing;

InstructionsParsing::InstructionsParsing() :
        Thread() {
}

void InstructionsParsing::split(const std::string &str, char c, std::vector <std::string> &vect) {
    std::string::size_type i = 0;
    std::string::size_type j = str.find(c);

    while (j != std::string::npos) {
        vect.push_back(str.substr(i, j - i));
        i = ++j;
        j = str.find(c, j);

        if (j == std::string::npos)
            vect.push_back(str.substr(i, str.length()));
    }
}

void InstructionsParsing::sanitize_string(std::string &line) {
    bool bSpace = false;
    int i = 0;

    while (line.data()[0] == ' ' || line.data()[0] == '\t')
        line.erase(0, 1);
    while (line.data()[i] != '\0') {
        if (bSpace) {
            line.insert(i - 1, " ");
            bSpace = false;
            i++;
        }
        while (line.data()[i] == ' ' || line.data()[i] == '\t') {
            line.erase(i, 1);
            bSpace = true;
        }
        i++;
    }
}

bool InstructionsParsing::get_pattern(const std::string &word, Patterns &pattern) {
    if (word.compare("PHONE_NUMBER") == 0) {
        pattern = PHONE_NUMBER;
        return true;
    }

    if (word.compare("IP_ADDRESS") == 0) {
        pattern = IP_ADDRESS;
        return true;
    }

    if (word.compare("EMAIL_ADDRESS") == 0) {
        pattern = EMAIL_ADDRESS;
        return true;
    }

    return false;
}

int InstructionsParsing::get_task(const std::string &task, Queue<Task *> &taskList) {
    std::string DataType[] = {"PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS"};
    std::vector <std::string> wordTab;
    split(task, ' ', wordTab);
    Patterns pattern;

    if (wordTab.size() >= 2) {
        if (!get_pattern(wordTab.back(), pattern)) {
            Logger::push(ERROR, "InstructionsParsing", "Unknown data type: \"" + wordTab.back() + "\"");
        } else if (wordTab.size() > 0) {
            for (int i = 0; i < wordTab.size() - 1; i++) {
                taskList.enqueue(new Task(wordTab[i], pattern));
                Logger::push(INFO, "InstructionsParsing", "Task created (Type = " + DataType[pattern] + " in " + wordTab[i] + ")");
            }
        }
    } else {
        Logger::push(ERROR, "InstructionsParsing", "Not enough information to create a task.");
    }
}

void InstructionsParsing::run() {

    Logger::push(INFO, "InstructionsParsing", "Starting Intruction Parsing.");
    Plazza *plazza = Plazza::getInstance();
    Queue<Task*>& tasklist = plazza->getTasks();
    while (plazza->isRunning()) {
        for (std::string line; std::getline(std::cin, line);) {
            if (!line.empty()) {
                std::vector <std::string> vect;
                split(line, ';', vect);
                if (vect.size() > 0)
                    for (int i = 0; i < vect.size(); i++) {
                        sanitize_string(vect[i]);
                        get_task(vect[i], tasklist);
                    }
                else {
                    sanitize_string(line);
                    get_task(line, tasklist);
                }
            }
        }
    }
}
