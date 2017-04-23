//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_INETWORKENDPOINT_HPP
#define PLAZZA_INETWORKENDPOINT_HPP


class INetworkEndPoint {
public:
    virtual void send() = 0;
    virtual void recv() = 0;
    virtual void listen() = 0;
    virtual void serverMode() = 0;
    virtual void clientMode() = 0;
};


#endif //PLAZZA_INETWORKENDPOINT_HPP
