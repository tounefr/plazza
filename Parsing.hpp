//
// Created by aurelien on 19/04/17.
//

#ifndef PLAZZA_PARSING_HPP
#define PLAZZA_PARSING_HPP

#include <regex>
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
    static                          Parsing* Get();
    static                          void Kill();
    std::vector<std::string>        get_list();
    void                            set_path(std::string path);
    void                            set_field(Information field);

    std::string                     get_path();

private:
    Parsing& operator= (const Parsing&){}

    void                                        cutGoodLine(char *str, std::regex reg,
                                                            std::vector<std::string>& infosList);
    std::string                                 path;
    std::map<Information , std::string>         filter;
    Information                                 field;

    Parsing();
    ~Parsing();

protected:
    static Parsing*  m_instance;
};

#endif //PLAZZA_PARSING_HPP