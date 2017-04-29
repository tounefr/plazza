//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_CAESARCIPHER_HPP
#define PLAZZA_CAESARCIPHER_HPP

#include <string>

class CaesarCipher {
public:
    static std::string      decipher(std::string data, int key);
};


#endif //PLAZZA_CAESARCIPHER_HPP
