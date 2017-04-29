//
// Created by aurelien on 19/04/17.
//

#include <iostream>
#include <fstream>
#include "FileParsing.hpp"
#include "../common/Logger.hpp"
#include "../encryption/CaesarCipher.hpp"
#include "../encryption/XorCipher.hpp"

using namespace Parsing;

FileParsing::FileParsing()
{
    this->filter.insert(std::make_pair(PHONE_NUMBER, "^0[1-6]{1}(([0-9]{2}){4})|((\\s[0-9]{2}){4})|((-[0-9]{2}){4})$"));
    this->filter.insert(std::make_pair(EMAIL_ADDRESS, "([0-9a-z_]+)(\\.|)?([0-9a-z_]*)@([0-9a-z_]+)(\\.([0-9a-z_]+))+"));
    this->filter.insert(std::make_pair(IP_ADDRESS, "\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b"));
    this->sep_chars.insert(std::make_pair(PHONE_NUMBER, "\":,/\\%<>|-"));
    this->sep_chars.insert(std::make_pair(EMAIL_ADDRESS, " \":,/\\%<>|"));
    this->sep_chars.insert(std::make_pair(IP_ADDRESS, " \":,/\\%<>|"));
}

FileParsing::~FileParsing() {}

//setter

void FileParsing::set_field(Patterns field) {
    this->field = field;
}

void FileParsing::set_path(std::string path) {
    this->path = path;
}

//getter

std::string FileParsing::get_path() {
    return this->path;
}

std::string FileParsing::isAPhoneNumber(const char *str) {
    std::string iostr(str);
    std::string  nbr_string;

    for (int i = 0; iostr[i]; i++)
    {
        if (iostr[i] >= '0' && iostr[i] <= '9')
            nbr_string += iostr[i];
    }
    if (nbr_string.length() == 10)
        return (nbr_string.c_str());
    return "";
}

void FileParsing::cutGoodLine(char *str, std::regex reg,
                          std::vector<std::string>& infosList)
{
    const char  *cut_str;
    const char  *sep;
    std::string to_string("");

    sep = this->sep_chars[this->field].c_str();
    cut_str = std::strtok(str, sep);
    while (cut_str != NULL)
    {
        if (this->field == PHONE_NUMBER)
        {
            to_string = isAPhoneNumber(cut_str);
            if (!to_string.empty())
            {
                infosList.push_back(to_string);
            }
        }
        else if (std::regex_match(cut_str, reg)) {
            to_string = cut_str;
            infosList.push_back(to_string);
        }
        cut_str = std::strtok(NULL, sep);
    }
}

void           FileParsing::lineByline(std::string str, std::vector<std::string>& infosList) {
    std::regex                      reg(this->filter[this->field]);
    std::vector<char>               pchar;
    std::istringstream              split(str);


    while (getline(split, str))
    {
        if (std::regex_search(str, reg)) {
            pchar.assign(str.begin(), str.end());
            pchar.push_back('\0');
            this->cutGoodLine(&pchar[0], reg, infosList);
        }
    }
}

void FileParsing::decipher(std::string data, std::vector<std::string> &infosList) {
    int key[2];

    key[0] = 0;
    while (infosList.empty() && key[0] <= 255)
    {
        data = CaesarCipher::decipher(data, key[0]);
        this->lineByline(data, infosList);
        key[0]++;
    }
    key[1] = 0;
    while (infosList.empty() && key[1] <= 255) {
        key[0] = 0;
        while (infosList.empty() && key[0] <= 255) {
            data = XorCipher::decipher(data, key);
            this->lineByline(data, infosList);
            key[0]++;
        }
        key[1]++;
    }
}

std::vector<std::string>            FileParsing::get_list() {
    std::ostringstream              ostrm;
    std::string                     data;
    std::ifstream                   file(this->path, std::ios::in);
    std::vector<std::string>        infosList;

    if (!file)
    {
        //Logger::getInstance()->print(ERROR, "FileParsing", "Failed to open file '" + std::string(this->path) + "'");
        exit(0);
    }
    ostrm << file.rdbuf();
    data = ostrm.str();

    this->decipher(data, infosList);

    file.close();
    return infosList;
}
