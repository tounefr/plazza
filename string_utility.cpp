
#include <functional>
#include <iostream>
#include <vector>
#include <string>

void split(const std::string& str, char c, std::vector<std::string>& vect)
{
    std::string::size_type i = 0;
    std::string::size_type j = str.find(c);

    while (j != std::string::npos)
    {
        vect.push_back(str.substr(i, j - i));
        i = ++j;
        j = str.find(c, j);

        if (j == std::string::npos)
            vect.push_back(str.substr(i, str.length()));
    }
}
