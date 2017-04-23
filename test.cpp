
#include <iostream>
#include <string>

int main() {
  std::string *s = new std::string("Hello world");

  std::cout << s << std::endl;
  std::string &s2 = *s;

  std::cout << &s2 << std::endl;

}
