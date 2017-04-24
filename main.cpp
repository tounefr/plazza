#include "Plazza.hpp"
#include "Scheduler.hpp"
#include "Worker.hpp"
#include <functional>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

void split(const std::string& str, char c, std::vector<std::string>& vect)
{
    std::string::size_type i = 0;
    std::string::size_type j = str.find(c);

    while (j != std::string::npos)
    {
        vect.push_back(str.substr(i, j - i));
        i = ++j;
        j = str.find(c, j);

        if (j == std::string::npos)
            vect.push_back(str.substr(i, str.length()));
    }
}

void    sanitize_string(std::string &line)
{
    bool bSpace = false;
    int i = 0;

    while (line.data()[0] == ' ' || line.data()[0] == '\t')
        line.erase(0, 1);
    while (line.data()[i] != '\0')
    {
        if (bSpace) {
            line.insert(i - 1, " ");
            bSpace = false;
            i++;
        }
        while (line.data()[i] == ' ' || line.data()[i] == '\t')
        {
            line.erase(i, 1);
            bSpace = true;
        }
        i++;
    }
}

bool get_pattern(const std::string &word, Patterns &pattern)
{
    if (word.compare("PHONE_NUMBER") == 0) {
        pattern = PHONE_NUMBER;
        return true;
    }

    if (word.compare("IP_ADDRESS") == 0) {
        pattern = IP_ADDRESS;
        return true;
    }

    if (word.compare("EMAIL") == 0) {
        pattern = EMAIL;
        return true;
    }

    return false;
}

int get_task(const std::string &task, std::queue<Task> &taskList)
{
    std::vector<std::string> wordTab;
    split(task, ' ', wordTab);
    Patterns pattern;

    if (!get_pattern(wordTab.back(), pattern)) {
        std::cout << "ERROR: Unknown pattern: \"" << wordTab.back() << "\"" << std::endl;
    }
    else if (wordTab.size() > 0)
        for (int i = 0; i < wordTab.size() - 1; i++) {
            taskList.push(Task(wordTab[i], pattern));
            std::cout << "NEW TASK: " << pattern << " | " << wordTab[i] << std::endl;
        }
}

static int  proceed_plazza(int nb_threads)
{
    Plazza plazza(nb_threads);
    std::queue<Task> tasklist = plazza.getTasks();

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
    std::cout << "Number of task registered: " << tasklist.size() << std::endl;
    return 0;
}

int main(int ac, char **av) {
    int nb_threads = -1;

    if (ac == 2) {
        if ((nb_threads = atoi(av[1])) <= 0) {
            std::cout << "ERROR: number of threads must be greater than 0\n";
            return -1;
        }
        return (proceed_plazza(nb_threads));
    }
    std::cout << "USAGE: " << av[0] << " nbr_of_threads\n";
    return 0;
}
