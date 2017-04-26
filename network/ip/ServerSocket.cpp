//
// Created by thomas on 23/04/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../../Plazza.hpp"
#include "ServerSocket.hpp"

using namespace Network::IP;

ServerSocket::ServerSocket(unsigned short listen_port) :
        _listen_port(listen_port),
        _listening(false) {
}


Network::ISocket *ServerSocket::sock_accept() {
    struct sockaddr_in sin;
    socklen_t sinsize = sizeof(struct sockaddr_in);
    int client_socket;
    Network::ISocket *clientSocket;

    client_socket = accept(_socket, (struct sockaddr*)&sin, &sinsize);
    if (client_socket == -1) {
        std::cerr << strerror(errno) << std::endl;
        return NULL;
    }
    Logger::getInstance()->print(DEBUG, "ServerSocket", "New socket client");
    clientSocket = new Socket(client_socket);
    _clients.push_back(clientSocket);
    return clientSocket;
}

bool ServerSocket::sock_listen() {
    if (-1 == (_socket = socket(AF_INET, SOCK_STREAM, 0))) {
        std::cerr << strerror(errno) << std::endl;
        return false;
    }
    int option = -1;
    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    Logger::getInstance()->print(DEBUG, "ServerSocket", "Starting ServerSocket on " + std::string(std::to_string(_listen_port)));
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(_listen_port);
    inet_aton(NETWORK_LISTEN_ADDRESS, &sockaddr.sin_addr);

    if (bind(_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cerr << strerror(errno) << std::endl;
        return false;
    }

    if (-1 == listen(_socket, 3))
        return false;

    _listening = true;
    return true;
}

bool ServerSocket::isListening() {
    return _listening;
}

void ServerSocket::run() {

}