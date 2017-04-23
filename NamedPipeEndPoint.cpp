//
// Created by thomas on 23/04/17.
//

#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include "iostream"
#include "NamedPipeEndPoint.hpp"

NamedPipeEndPoint::NamedPipeEndPoint(int pid) :
        _pid(pid)
{
    createFIFO();
}

void NamedPipeEndPoint::createFIFO()
{
    std::ostringstream ss;

    ss << "./fifo/" << _pid;
    _in_path = ss.str() + "_in";
    if (access(_in_path.c_str(), S_IRWXU) == -1)
        mkfifo(_in_path.c_str(), S_IRWXU);
    _out_path = ss.str() + "_out";
    if (access(_out_path.c_str(), S_IRWXU) == -1)
        mkfifo(_out_path.c_str(), S_IRWXU);
}

void NamedPipeEndPoint::setEndPoint(bool endPoint) {
    _endPoint = endPoint;
}

void NamedPipeEndPoint::open_endpoint() {
    _fd_in = open(((_endPoint) ? _in_path.c_str() : _out_path.c_str()), O_RDONLY);
    _fd_out = open(((_endPoint) ? _out_path.c_str() : _in_path.c_str()), O_WRONLY);
}

void NamedPipeEndPoint::send() {
    t_packet *packet = new t_packet;
    packet->type = PACKET_GIVE_ME_TASK;

    write(((_endPoint) ? _fd_in : _fd_out), packet, sizeof(t_packet));
}

void NamedPipeEndPoint::recv() {
    bool running = true;

    while (1) {
        if (_endPoint) {
            std::cout << "Reading on " << _in_path << std::endl;
        } else {
            std::cout << "Reading on " << _out_path << std::endl;
        }
        t_packet *packet = new t_packet;
        if (-1 == read(((_endPoint) ? _fd_in : _fd_out), packet, sizeof(t_packet)))
            break;
        std::cout << "[" << _pid << "] Recv packet " << packet->type << std::endl;
        delete packet;
    }
}