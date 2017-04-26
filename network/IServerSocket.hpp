//
// Created by thomas on 24/04/17.
//

#ifndef PLAZZA_ISERVERSOCKET_HPP
#define PLAZZA_ISERVERSOCKET_HPP

#include "ISocket.hpp"
#include "Packet.hpp"
#include "../common/Queue.hpp"

namespace Network {
    class IServerSocket {
    public:
        virtual ISocket *sock_accept() = 0;
        virtual bool sock_listen() = 0;
        virtual bool isListening() = 0;
    };
}

#endif //PLAZZA_ISERVERSOCKET_HPP
