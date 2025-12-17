#include <regex>
#include <iostream>
#include <string>

int main()
{
    std::string maybeCity;
    std::getline(std::cin, maybeCity);

    std::regex reg{"^(\\s*([A-Z][a-z]*(-[A-Z][a-z]*)*))*$"};

    std::cout << (std::regex_match(maybeCity, reg) ? "poprawny format" : "niepoprawny format") << '\n';
    return 0;
}