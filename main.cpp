#include <iostream>
#include <stdlib.h>
#include <string>

static int  proceed_plazza(int nb_threads)
{
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << "got line: \"" << line << "\"" << std::endl;
    }
    return 0;
}

int main(int ac, char **av) {
    int     nb_threads = -1;

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
