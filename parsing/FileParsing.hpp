//
// Created by aurelien on 19/04/17.
//

#ifndef PLAZZA_FILEPARSING_HPP
#define PLAZZA_FILEPARSING_HPP

#include <regex>
#include <string>
#include "../common/Task.hpp"

namespace Parsing {
    class FileParsing {
    public:
        FileParsing();
        ~FileParsing();

        const std::vector<std::string>      get_list();

        void                                set_path(const std::string path);
        void                                set_field(const Patterns field);

        const std::string                   get_path() const;

    private:
        FileParsing &operator=(const FileParsing &) {}

        void                                cutGoodLine(char *str, std::regex reg,
                                                        std::vector<std::string> &infosList);
        std::string                         isAPhoneNumber(const char *str) const;
        void                                lineByline(std::string str, std::vector<std::string>& infosList);
        void                                decipher(std::string str, std::vector<std::string>& infosList);

        std::string path;
        std::map<Patterns, std::string>     filter;
        std::map<Patterns , std::string>    sep_chars;
        Patterns field;
    };
}

#endif //PLAZZA_FILEPARSING_HPP