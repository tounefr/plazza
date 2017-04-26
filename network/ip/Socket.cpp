//
// Created by thomas on 23/04/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#include "Socket.hpp"

using namespace Network::IP;

Socket::Socket(Queue<Packet*>& pendingPackets) :
    _pendingPackets(pendingPackets)
{

}

Socket::Socket(Queue<Packet*>& pendingPackets, int socket) :
    Socket(pendingPackets)
{
    _socket = socket;
}

void Socket::sock_connect(std::string& ip, unsigned short& port) {
    if (-1 == (_socket = socket(AF_INET, SOCK_STREAM, 0))) {
        std::cerr << strerror(errno) << std::endl;
        return;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    inet_aton(ip.c_str(), &sockaddr.sin_addr);

    if (-1 == (connect(_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)))) {
        std::cerr << strerror(errno) << std::endl;
        return;
    }
}

void Socket::run() {
    Packet *packet;

    while (1) {
        packet = new Packet;
        memset(packet, 0, sizeof(Packet));
        if (recv(_socket, packet, sizeof(Packet), 0) <= 0) {
            std::cout << "Recv failed" << std::endl;
            break;
        }
        _pendingPackets.enqueue(packet);
        std::cout << "Recv packet : " << packet->type << std::endl;
    }
}