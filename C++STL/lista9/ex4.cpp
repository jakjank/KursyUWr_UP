#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string input;

    while (true) {
        std::cout << "Podaj sciezke: ";
        
         if (!std::getline(std::cin, input) || input.empty()) {
            break;
        }

        fs::path dirPath(input);

        if (!fs::exists(dirPath)) {
            std::cerr << "Katalog '" << input << "' nie istnieje.\n";
            continue;
        }

        if (!fs::is_directory(dirPath)) {
            std::cerr << input << "' nie jest katalogiem.\n";
            continue;
        }

        std::vector<fs::path> dirs;
        std::vector<fs::path> files;

        for (auto& obj : fs::directory_iterator(dirPath)) {
            if (obj.is_directory())
                dirs.push_back(obj.path().filename());
            else if (obj.is_regular_file())
                files.push_back(obj.path().filename());
        }

        std::sort(dirs.begin(), dirs.end());
        std::sort(files.begin(), files.end());

        std::cout << "Zawartosc:\n";

        std::cout << "Katalogi:\n";
        for (const auto& d : dirs)
            std::cout << "  " << d.string() << "\n";

        std::cout << "Pliki:\n";
        for (const auto& f : files)
            std::cout << "  " << f.string() << "\n";
    }
    return 0;
}
