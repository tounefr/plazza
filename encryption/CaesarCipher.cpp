//
// Created by thomas on 23/04/17.
//

#include "CaesarCipher.hpp"

std::string         CaesarCipher::decipher(std::string data, int key) {
    std::string     decrypt("");

    for (int i(0); i < data.length(); i++) {
        decrypt += char(data[i] + key);
    }
    return decrypt;
}