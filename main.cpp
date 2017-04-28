#include "Plazza.hpp"
#include <functional>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

int main(int ac, char **av) {
    int nb_threads = -1;
    int returnv;

    if (ac == 2) {
        if ((nb_threads = atoi(av[1])) <= 0) {
            std::cout << "ERROR: number of threads must be greater than 0\n";
            return -1;
        }
        Plazza *p = Plazza::getInstance();
        returnv = p->start(nb_threads);
        delete p;
        return returnv;
    }
    std::cout << "USAGE: " << av[0] << " nbr_of_threads\n";
    return 0;
}