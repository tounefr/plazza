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
        Logger::getInstance()->print(ERROR, "Socket", "socket error : '" + std::string(strerror(errno)) + "'");
        return;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    inet_aton(ip.c_str(), &sockaddr.sin_addr);

    if (-1 == (connect(_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)))) {
        Logger::getInstance()->print(ERROR, "Socket", "connect error : '" + std::string(strerror(errno)) + "'");
        return;
    }
    Logger::getInstance()->print(DEBUG, "Socket", "Connected to " + ip + ":" + std::to_string(port));
}

Packet* Socket::recv_packet() {
    Packet *packet;
    PacketType packet_type;
    unsigned int packet_size;
    char *packet_content;
    unsigned int buffer_size;

    if (-1 == recv(_socket, (char*)&packet_type, sizeof(packet_type), 0)) {
        Logger::getInstance()->print(ERROR, "Socket", "Recv failed : '"+ std::string(strerror(errno)) +"'");
        return NULL;
    }
    if (-1 == recv(_socket, (char*)&packet_size, sizeof(packet_size), 0)) {
        Logger::getInstance()->print(ERROR, "Socket", "Recv failed : '"+ std::string(strerror(errno)) +"'");
        return NULL;
    }
    packet_content = new char[packet_size + 1];
    memset(packet_content, 0, packet_size + 1);
    if (-1 == recv(_socket, packet_content, packet_size, 0)) {
        Logger::getInstance()->print(ERROR, "Socket", "Recv failed : '"+ std::string(strerror(errno)) +"'");
        return NULL;
    }
    packet = new Packet(packet_type, packet_size, packet_content);
    return packet;
}

bool Socket::sock_send(PacketType const& packetType, std::string *buffer) {
    unsigned int packet_size = buffer->size();

    if (-1 == send(_socket, (char*)&packetType, sizeof(packetType), 0) ||
        -1 == send(_socket, (char*)&packet_size, sizeof(packet_size), 0) ||
        -1 == send(_socket, (char*)buffer->c_str(), buffer->size(), 0)) {
        Logger::getInstance()->print(ERROR, "Socket", "Send failed : '"+ std::string(strerror(errno)) +"'");
        return false;
    }

    return true;
}

bool Socket::sock_close() {
    if (-1 == close(_socket)) {
        Logger::getInstance()->print(ERROR, "Socket", "close error : '"+ std::string(strerror(errno)) +"'");
        return false;
    }
    return true;
}