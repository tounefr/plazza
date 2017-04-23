//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_NAMEDPIPEENDPOINT_HPP
#define PLAZZA_NAMEDPIPEENDPOINT_HPP

#include "Thread.hpp"
#include "INetworkEndPoint.hpp"

enum e_packet
{
    PACKET_GIVE_ME_TASK
};

typedef struct __attribute__((__packed__)) s_packet
{
    enum e_packet type;
} t_packet;

class NamedPipeEndPoint {
private:
    int _pid;
    int _fd_in;
    int _fd_out;
    std::string _in_path;
    std::string _out_path;
    bool _endPoint;

public:
    NamedPipeEndPoint(int pid);
    void createFIFO();
    void setEndPoint(bool);
    void open_endpoint();
    void recv();
    void send();
};


#endif //PLAZZA_NAMEDPIPEENDPOINT_HPP
