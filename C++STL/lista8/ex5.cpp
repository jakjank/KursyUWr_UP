#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string html;
    std::string line;
    
    // Wczytujemy cały dokument HTML
    while (std::getline(std::cin, line)) {
        html += line + "\n";
    }

    // Regex do znalezienia atrybutu href w <a>
    std::regex hrefRegex(R"(<a\b[^>]*\bhref="([^"]*)");

    auto begin = std::sregex_iterator(html.begin(), html.end(), hrefRegex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        std::cout << (*it)[1].str() << '\n';  // Grupa 1 = zawartość href
    }

    return 0;
}