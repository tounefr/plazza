//
// Created by aurelien on 19/04/17.
//

#include <iostream>
#include <fstream>
#include "Parsing.hpp"

Parsing* Parsing::m_instance=0;

Parsing::Parsing()
{
    this->filter.insert(std::make_pair(PHONE_NUMBER, "^0[1-6]{1}(([0-9]{2}){4})|((\\s[0-9]{2}){4})|((-[0-9]{2}){4})$"));
    this->filter.insert(std::make_pair(EMAIL_ADDRESS, "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
    this->filter.insert(std::make_pair(IP_ADDRESS, "\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b"));
    this->sep_chars.insert(std::make_pair(PHONE_NUMBER, "\":,/\\%<>|-"));
    this->sep_chars.insert(std::make_pair(EMAIL_ADDRESS, " \":,/\\%<>|"));
    this->sep_chars.insert(std::make_pair(IP_ADDRESS, " \":,/\\%<>|"));

    std::cout << "Creation"<< std::endl;
}

Parsing::~Parsing() {
    std::cout << "Destruction" << std::endl;
}

void Parsing::set_field(Information field) {
    this->field = field;
}

void Parsing::set_path(std::string path) {
    this->path = path;
}

std::string Parsing::get_path() {
    return this->path;
}

Parsing* Parsing::Get() {
    if (m_instance == 0)
        m_instance = new Parsing();
    return m_instance;
}

void Parsing::Kill() {
    delete m_instance;
    m_instance = 0;
}

char            *Parsing::isAPhoneNumber(char *str) {
    std::string iostr(str);
    std::string  nbr_string;

    for (int i = 0; iostr[i]; i++)
    {
        if (iostr[i] >= '0' && iostr[i] <= '9')
            nbr_string += iostr[i];
    }
    if (nbr_string.length() == 10) {
        return strdup(nbr_string.c_str());
    }
    else
        return NULL;
}

void Parsing::cutGoodLine(char *str, std::regex reg,
                          std::vector<std::string>& infosList)
{
    char        *cut_str;
    const char  *sep;
    std::string to_string("");

    sep = this->sep_chars[this->field].c_str();
    cut_str = std::strtok(str, sep);
    while (cut_str != NULL)
    {
        if (this->field == PHONE_NUMBER)
        {
            if ((cut_str = isAPhoneNumber(cut_str)))
            {
                to_string = cut_str;
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

std::vector<std::string>            Parsing::get_list() {
    std::vector<std::string>        infosList;
    std::string                     str;
    std::ifstream                   file(this->path, std::ios::in);
    std::vector<char>               pchar;
    std::regex                      reg(this->filter[this->field]);

    if (!file)
    {
        std::cerr << "Error open file !" << std::endl;
        exit(0);
    }
    while (getline(file, str))
    {
        if (std::regex_search(str, reg)) {
            pchar.assign(str.begin(), str.end());
            pchar.push_back('\0');
            this->cutGoodLine(&pchar[0], reg, infosList);
        }
    }
    file.close();
    return infosList;
}
