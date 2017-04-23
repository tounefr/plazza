//
// Created by aurelien on 19/04/17.
//

#ifndef PLAZZA_PARSING_HPP
#define PLAZZA_PARSING_HPP

#include <string>

enum Information
{
    PHONE_NUMBER,
    EMAIL_ADDRESS,
    IP_ADDRESS
};

class Parsing
{
public:
    static  Parsing* Get();
    static  void Kill();
    void    get_list();
    void    set_path(std::string path);
    void    set_field(Information field);

private:
    Parsing& operator= (const Parsing&){}
    std::string     path;
    Information     field;

    Parsing();
    ~Parsing();

protected:
    static Parsing*  m_instance;
};

#endif //PLAZZA_PARSING_HPP