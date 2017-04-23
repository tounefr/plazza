#include <iostream>
#include <dirent.h>
#include "Parsing.hpp"

static void display_vector(std::vector<std::string> vec)
{
    std::string     infos;
    while (!vec.empty()) {
        std::cout << vec.back() << std::endl;
        vec.pop_back();
    }
}

int     read_directory(std::string path, Parsing* ptr1, DIR* rep)
{
    struct      dirent *ent;
    std::string name;

    if (rep)
    {
        while ((ent = readdir(rep)))
        {
            name.assign(ent->d_name);
            ptr1->set_field(EMAIL_ADDRESS);
            ptr1->set_path(path + "/" + name);
            //std::cout << ptr1->get_path() <<  " | " << ent->d_name << std::endl;
            if (ent->d_name[0] != '.') {
                if (ent->d_type != DT_DIR)
                    display_vector(ptr1->get_list());
                else
                    read_directory(ptr1->get_path(), ptr1, opendir(ptr1->get_path().c_str()));
            }
        }
        closedir(rep);
    }
}

int main()
{
    Parsing* ptr1=Parsing::Get();
    std::string path("/home/aurelien/rendu/CPP/plazza/srcs");
    read_directory(path, ptr1, opendir(path.c_str()));
}