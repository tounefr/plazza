//
// Created by thomas on 23/04/17.
//

#include <iostream>
#include "XorCipher.hpp"

std::string XorCipher::decipher(std::string data, int key[]) {
    std::string     decrypt("");
    for (int i(0); i < data.length(); i++) {
        decrypt += char(data[i] ^ key[i % 2]);
    }
    return decrypt;
}