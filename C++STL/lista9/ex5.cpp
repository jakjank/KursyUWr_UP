#include <iostream>
#include <filesystem>
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

        std::uintmax_t total_size = 0;
        std::size_t file_count = 0;

        for (auto& obj : fs::recursive_directory_iterator(dirPath)) {
            if (obj.is_regular_file()) {
                ++file_count;
                total_size += obj.file_size();
            }
        }

        std::cout << "Katalog: " << dirPath << "\n";
        std::cout << "Liczba plików: " << file_count << "\n";
        std::cout << "Suma rozmiarów: " << total_size << " bytes\n";
    }

    return 0;
}
