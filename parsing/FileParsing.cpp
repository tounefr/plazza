//
// Created by aurelien on 19/04/17.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "FileParsing.hpp"

Parsing* Parsing::m_instance=0;

Parsing::Parsing() {
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

Parsing* Parsing::Get() {
    //mutex lock
    if (m_instance == 0)
        m_instance = new Parsing();
    return m_instance;
}

void Parsing::Kill() {
    delete m_instance;
    m_instance = 0;
}

void Parsing::get_list() {
    std::string   str;
    std::ifstream file(this->path, std::ios::in);
    std::regex    email("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    if (!file)
    {
        std::cerr << "Error open file !" << std::endl;
        exit(0);
    }
    while (getline(file, str))
    {
        if (std::regex_search(str, email))
            std::cout << str << std::endl;
    }
    //std::cout << "Une list de " << this->field << " depuis le fichier "
      //        << this->path << std::endl;
    file.close();
}
