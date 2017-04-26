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

#include "../ISocket.hpp"
#include "Socket.hpp"
#include "../../common/Logger.hpp"

using namespace Network::IP;

Socket::Socket(std::string ip, unsigned short port)
{
    sock_connect(ip, port);
}

Socket::Socket(int socket)
{
    _socket = socket;
}

void Socket::sock_connect(std::string ip, unsigned short port) {
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
    Logger::getInstance()->print(DEBUG, "Socket", "Connected to " + ip + ":" + std::to_string(port));
}

PacketGiveTask* Socket::recv_packet() {
    PacketGiveTask *packet = (PacketGiveTask*)malloc(sizeof(PacketGiveTask));
    if (packet == NULL)
        return NULL;
    memset(packet, 0, sizeof(PacketGiveTask));
    if (recv(_socket, packet, sizeof(PacketGiveTask), 0) == -1) {
        // TODO: fix the log msg
        // Logger::getInstance()->print(ERROR, "Socket", "Recv failed : " + std::to_string(strerror(errno)));
        return NULL;
    }
    return packet;
}

bool Socket::sock_send(PacketGiveTask *packet) {
    if (send(_socket, (void*)packet, sizeof(PacketGiveTask), 0) == -1)
        return false;
    return true;
}