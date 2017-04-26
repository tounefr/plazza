//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_SERVERSOCKET_HPP
#define PLAZZA_SERVERSOCKET_HPP

#include <list>
#include <map>
#include "Socket.hpp"
#include "../../common/Thread.hpp"
#include "../ISocket.hpp"
#include "../IServerSocket.hpp"

namespace Network {
    namespace IP {
        class ServerSocket : public IServerSocket, public Thread {
        private:
            int _socket;
            unsigned short _listen_port;
            bool _listening;
            std::list<Network::ISocket *> _clients;
        public:
            ServerSocket(unsigned short listen_port);
            virtual bool sock_listen();

            virtual Network::ISocket *sock_accept();
            virtual void run();
            virtual bool isListening();
        };
    }
}


#endif //PLAZZA_SERVERSOCKET_HPP
