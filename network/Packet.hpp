//
// Created by thomas on 27/04/17.
//

#ifndef PLAZZA_PACKET_HPP
#define PLAZZA_PACKET_HPP

#include <iostream>
#include <sstream>
#include "../common/Task.hpp"

typedef enum PacketType
{
    PACKET_GIVE_TASK,
    PACKET_TASK_RECV,
    PACKET_TASK_ERROR,
    PACKET_TASK_RESULT
} PacketType;

class Packet
{
private:
    PacketType const& _type;
    unsigned int const& _packet_size;
    std::string const& _buffer;
    std::stringstream _stream;

public:
    Packet(PacketType packetType, unsigned int packetSize, char * buffer);
    PacketType const& getType();
    unsigned int const& getPacketSize();
    std::string const& getBuffer();
    std::stringstream& getStream();
};

class PacketGiveTask {
};

#endif //PLAZZA_PACKET_HPP
