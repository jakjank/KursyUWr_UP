#include <regex>
#include <iostream>
#include <string>

int main()
{
    std::string maybeImag;
    std::getline(std::cin, maybeImag);

    std::regex reg{"^\\("
                      "[+-]?[0-9]+(\\.[0-9]+)?"
                      "[+-]"
                      "[+-]?[0-9]+(\\.[0-9]+)?"
                      "[iI]"
                      "\\)$"};

    std::cout << (std::regex_match(maybeImag, reg) ? "poprawny format" : "niepoprawny format") << '\n';
    return 0;
}