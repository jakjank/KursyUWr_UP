#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

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

        std::vector<fs::path> dirs_to_del;

        for (auto& obj : fs::recursive_directory_iterator(dirPath)) {
            if (obj.is_regular_file()) {
                if(obj.path().extension() == ".cbp")
                {
                    dirs_to_del.emplace_back(obj.path().parent_path() / "bin");
                }
            }
        }

        for(auto p : dirs_to_del)
        {
            if(fs::exists(p) && fs::is_directory(p))
            {
                std::cerr << "Usuwanie: " << p << '\n';
                fs::remove_all(p);
            }
        }
    }

    return 0;
}
