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
        std::vector<std::string>    get_list();

        void                        set_path(std::string path);
        void                        set_field(Patterns field);
        FileParsing();
        ~FileParsing();

        std::string                 get_path();

    private:
        FileParsing &operator=(const FileParsing &) {}

        void                        cutGoodLine(char *str, std::regex reg,
                                                std::vector<std::string> &infosList);
        static char                 *isAPhoneNumber(char *str);

        std::string path;
        std::map<Patterns, std::string>             filter;
        std::map<Patterns , std::string>         sep_chars;
        Patterns field;
    };
}

#endif //PLAZZA_FILEPARSING_HPP