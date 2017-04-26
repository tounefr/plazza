//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_PACKET_HPP
#define PLAZZA_PACKET_HPP

typedef enum e_packet_type
{
    HELLO
} e_packet_type;

typedef struct s_packet
{
    e_packet_type type;

} Packet;

#endif //PLAZZA_PACKET_HPP
