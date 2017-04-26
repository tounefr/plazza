//
// Created by aurelien on 24/04/17.
//

#include <dirent.h>
#include <iostream>
#include "parsing/FileParsing.hpp"

using namespace Parsing;

static void     display_vector(std::vector<std::string> vec)
{
    while (!vec.empty()) {
        std::cout << vec.back() << std::endl;
        vec.pop_back();
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

    FileParsing *ptr = FileParsing::Get();
    ptr->set_field(EMAIL_ADDRESS);
    ptr->set_path("/home/aurelien/rendu/CPP/plazza/html_files");
    dir = opendir(ptr->get_path().c_str());
    search_in_dirctory(ptr, dir);
}