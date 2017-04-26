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
//        Socket *ServerSocket::sock_accept(Queue<Packet*>& packets);
        virtual ISocket *sock_accept(Queue<Packet*>& packets) = 0;
    };
}

#endif //PLAZZA_ISERVERSOCKET_HPP
