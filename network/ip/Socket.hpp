//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_SOCKET_HPP
#define PLAZZA_SOCKET_HPP

#include <iostream>
#include "../../common/Thread.hpp"
#include "../Packet.hpp"
#include "../../common/Queue.hpp"
#include "../ISocket.hpp"

namespace Network
{
    namespace IP
    {
        class Socket : public Thread, public ISocket {
        private:
            Queue<Packet*>& _pendingPackets;
            int _socket;
        public:
            Socket(Queue<Packet*>& pendingPackets);
            Socket(Queue<Packet*>& pendingPackets, int _socket);
            void sock_connect(std::string& ip, unsigned short& port);
            virtual void run();
        };
    }
}


#endif //PLAZZA_SOCKET_HPP
