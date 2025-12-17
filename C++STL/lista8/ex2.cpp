#include <regex>
#include <iostream>

int main()
{
    std::string maybeDate;
    std::cin >> maybeDate;

    std::cout << (std::regex_match(maybeDate, std::regex("^(((0[1-9]|[12][0-9]|3[01])-(01|03|05|07|08|10|12))|"
                                                                  "((0[1-9]|[12][0-9]|30)-(04|06|09|11))|"
                                                                  "(0[1-9]|1[0-9]|2[0-8])-02)-\\d{4}$")) 
                    ? "poprawny format" : "niepoprawny format") << '\n';
    return 0;
}