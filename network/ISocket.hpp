//
// Created by thomas on 24/04/17.
//

#ifndef PLAZZA_ISOCKET_HPP
#define PLAZZA_ISOCKET_HPP

#include "Packet.hpp"

namespace Network {
    class ISocket {
    public:
        virtual void sock_connect(std::string ip, unsigned short port) = 0;
        virtual Packet* recv_packet() = 0;
        virtual bool sock_send(PacketType const& packetType, std::string *buffer) = 0;
        virtual bool sock_close() = 0;
        virtual bool const& isRunning() = 0;
        virtual void setTimeout(size_t seconds) = 0;
    };
}


#endif //PLAZZA_ISOCKET_HPP
