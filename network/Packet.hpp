//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_PACKET_HPP
#define PLAZZA_PACKET_HPP

#include "../common/Task.hpp"

typedef struct PacketGiveTask
{
    char path[200];
    Patterns type;
} PacketGiveTask;


#endif //PLAZZA_PACKET_HPP
