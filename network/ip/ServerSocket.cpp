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
#include "ServerSocket.hpp"

using namespace Network::IP;

ServerSocket::ServerSocket(unsigned short listen_port) {
    if (-1 == (_socket = socket(AF_INET, SOCK_STREAM, 0))) {
        std::cerr << strerror(errno) << std::endl;
        return;
    }
    std::cout << "Starting ServerSocket on " << listen_port << std::endl;

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(listen_port);
    inet_aton("127.0.0.1", &sockaddr.sin_addr);

    if (-1 == (bind(_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)))) {
        std::cerr << strerror(errno) << std::endl;
        return;
    }
    listen(_socket, 5);
}

ISocket *ServerSocket::sock_accept(Queue<Packet*>& packets) {
    struct sockaddr_in sin = {0};
    socklen_t sinsize = sizeof(sin);
    int client_socket;
    Socket *clientSocket;

    client_socket = accept(_socket, (struct sockaddr*)&sin, &sinsize);
    std::cout << "New socket client " << std::endl;
    if (client_socket == -1) {
        std::cerr << strerror(errno) << std::endl;
        return NULL;
    }
    clientSocket = new Socket(packets, client_socket);
    _clients.push_back(clientSocket);
    return clientSocket;
}

void ServerSocket::run() {

}