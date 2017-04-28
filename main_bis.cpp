//
// Created by aurelien on 24/04/17.
//

#include <dirent.h>
#include <iostream>
#include "parsing/FileParsing.hpp"
#include <fstream>

using namespace Parsing;

static void     display_vector(std::vector<std::string> vec)
{
    while (!vec.empty()) {
        std::cout << vec.back() << std::endl;
        vec.pop_back();
    }
}

std::string    Cryptchar(std::string str, int index, int key) {
    std::string eclu_char = "#!^$()[]{}|?+*.\\";
    std::string rt_str("");

    if (eclu_char.find(str[index]) == eclu_char.npos) {
        //if (index > 0) {
            if (str[index] ^ key == '\\')
                return (rt_str += '\\' + str[index] ^ key);
        //}
        return (rt_str += str[index] ^ key);
    }
    return (rt_str += str[index]);
}

void    read_picture_regex(FileParsing *ptr) {
    std::map<Patterns, std::string> filt = ptr->get_filter();
    std::string                     str = filt[ptr->get_field()];
    std::string                     tmp;
    int key[2];

    //for (key[1] = 0; key[1] <= 255; key[1]++) {
        for (key[0] = 0; key[0] <= 255; key[0]++) {
            for (int i(0); i < str.length(); i++) {
                tmp += Cryptchar(str, i, key[0]);
            }
            std::cout << tmp << std::endl;
            filt[ptr->get_field()] = tmp;
            ptr->set_filter(filt);
            display_vector(ptr->get_list());
            tmp = "";
        }
    //}
}

void    read_picture(FileParsing *ptr) {
    std::string         str;
    std::string         decrypt;
    std::string         path = ptr->get_path();
    std::vector<std::string> list;
    int key[2];


    ptr->set_path("/home/aurelien/rendu/CPP/html_files/file.txt");
    //for (key[1] = 0; key[1] <= 255; key[1]++) {
        for (key[0] = 0; key[0] <= 255; key[0]++) {
            std::ifstream       file(path, std::ios::in);
            std::ofstream       myFile("/home/aurelien/rendu/CPP/html_files/file.txt");

            if (!file) {
                std::cerr << "Error open file !" << std::endl;
                exit(0);
            }
            while (getline(file, str)) {
                for (int i(0); i < str.length(); i++) {
                    decrypt += str[i] ^ key[0];
                }
            }
            myFile << decrypt;
            list = ptr->get_list();
            display_vector(list);
            if (!list.empty()) {
                std::cout << "RETURN!!" << std::endl;
                return;
            }
            decrypt = "";
            myFile.close();
        }
    //}
}

void    decryptCesard(FileParsing *ptr) {
    std::string         str;
    std::ostringstream  ostrm;
    std::string         decrypt;
    std::string         path = ptr->get_path();
    std::vector<std::string> list;
    int                 key;

    ptr->set_path("/home/aurelien/rendu/CPP/html_files/file.txt");
    for (key = 0; key <= 26; key++) {
        std::ifstream       file(path, std::ios::binary);
        std::ofstream       myFile("/home/aurelien/rendu/CPP/html_files/file.txt",
                                   std::ofstream::out | std::ofstream::trunc);

        if (!file) {
            std::cerr << "Error open file !" << std::endl;
            exit(0);
        }
        ostrm << file.rdbuf();
        str = ostrm.str();
        for (int i(0); i < str.length(); i++) {
                decrypt += char(str[i] + key);
        }

        myFile << decrypt;
        //std::cout << decrypt << std::endl;
        list = ptr->get_list();
        display_vector(list);
        if (!list.empty()) {
            std::cout << "RETURN!!" << std::endl;
            return;
        }
        decrypt = "";
        ostrm.str("");
        myFile.close();
    }
}

static void     search_in_dirctory(FileParsing *ptr, DIR *dir)
{
    struct dirent   *dir_infos;
    std::string     mem_str;

    while ((dir_infos = readdir(dir)))
    {
        if (dir_infos->d_name[0] != '.') {
            mem_str = ptr->get_path();
            ptr->set_path(mem_str + "/" + dir_infos->d_name);
            if (dir_infos->d_type != DT_DIR) {
                std::cout << dir_infos->d_name << std::endl;
                //decryptCesard(ptr);
                //read_picture(ptr);
                //read_picture_regex(ptr);
                display_vector(ptr->get_list());
            }
            else
                search_in_dirctory(ptr, opendir(ptr->get_path().c_str()));
            ptr->set_path(mem_str);
        }
    }
}

int     main()
{
    DIR      *dir;

    FileParsing *ptr = new FileParsing();
    ptr->set_field(EMAIL_ADDRESS);
    ptr->set_path("/home/aurelien");
    dir = opendir(ptr->get_path().c_str());
    //ptr->set_path("/home/aurelien/rendu/CPP");
    //decryptCesard(ptr);
    //search_in_dirctory(ptr, dir);
    //std::cout << next_char('m', 20) << std::endl;
    //read_picture(ptr->get_path());
    return 0;
}
