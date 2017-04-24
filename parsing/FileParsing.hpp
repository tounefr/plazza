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
        static FileParsing *Get();

        static void Kill();

        std::vector<std::string> get_list();

        void set_path(std::string path);

        void set_field(Patterns field);

        std::string get_path();

    private:
        FileParsing &operator=(const FileParsing &) {}

        void cutGoodLine(char *str, std::regex reg,
                         std::vector<std::string> &infosList);

        std::string path;
        std::map<Patterns, std::string> filter;
        Patterns field;

        FileParsing();

        ~FileParsing();

    protected:
        static FileParsing *m_instance;
    };
}

#endif //PLAZZA_FILEPARSING_HPP