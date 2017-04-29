//
// Created by thomas on 23/04/17.
//

#ifndef PLAZZA_XORCIPHER_HPP
#define PLAZZA_XORCIPHER_HPP

#include <string>

class XorCipher {
public:
    static std::string      decipher(std::string data, int key[]);
};


#endif //PLAZZA_XORCIPHER_HPP
