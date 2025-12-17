#include <regex>
#include <iostream>

int main()
{
    std::string maybeHour;
    std::cin >> maybeHour;

    std::cout << (std::regex_match(maybeHour, std::regex("^([01]?[0-9]|2[0-3])(:([0-5][0-9])){1,2}$")) 
                    ? "poprawny format" : "niepoprawny format") << '\n';
    return 0;
}