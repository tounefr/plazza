//
// Created by thomas on 27/04/17.
//

#include "Packet.hpp"

Packet::Packet(PacketType packetType, unsigned int packetSize, char * buffer):
    _type(packetType), _packet_size(packetSize), _buffer(buffer) {
    _stream = std::stringstream(_buffer);
}

PacketType const& Packet::getType() {
    return _type;
}

unsigned int const& Packet::getPacketSize() {
    return _packet_size;
}

std::string const& Packet::getBuffer() {
    return _buffer;
}

std::stringstream& Packet::getStream() {
    return _stream;
}
