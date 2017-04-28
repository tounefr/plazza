//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_SOCKET_HPP
#define PLAZZA_SOCKET_HPP

#include <iostream>
#include <list>
#include "../../common/Thread.hpp"
#include "../Packet.hpp"
#include "../../common/Queue.hpp"
#include "../ISocket.hpp"

namespace Network
{
    namespace IP
    {
        class Socket : public Network::ISocket {
        private:
            int _socket;

        public:
            Socket(std::string ip, unsigned short port);
            Socket(int _socket);

            virtual void sock_connect(std::string ip, unsigned short port);
            virtual Packet* recv_packet();
            virtual bool sock_send(PacketType const& packetType, std::string *buffer);
            virtual bool sock_close();
        };
    }
}


#endif //PLAZZA_SOCKET_HPP
