//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_SERVERSOCKET_HPP
#define PLAZZA_SERVERSOCKET_HPP

#include <list>
#include <map>
#include "Socket.hpp"
#include "../../common/Thread.hpp"
#include "../IServerSocket.hpp"

namespace Network {
    namespace IP {
        class ServerSocket : public IServerSocket, public Thread {
        private:
            int _socket;
            std::list<Network::IP::Socket *> _clients;
        public:
            ServerSocket(unsigned short listen_port);
            virtual ISocket *sock_accept(Queue<Packet*>& packets);
            virtual void run();
        };
    }
}


#endif //PLAZZA_SERVERSOCKET_HPP
