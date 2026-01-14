#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

std::time_t to_time_t(fs::file_time_type tp)
{
    using namespace std::chrono;
    auto sctp = clock_cast<system_clock>(tp);
    return system_clock::to_time_t(sctp);
}

int main(int argc, char* argv[])
{
   for (int i = 1; i < argc; ++i)
    {
        fs::path p{argv[i]};
        std::cout << "Path: " << p << "\n";

        if (!fs::exists(p)) {
            std::cerr << argv[i] << "does not exist\n";
            continue;
        }

        std::cout << "* canonical path: " << fs::canonical(p) << "\n";
        std::cout << "* is directory: " << fs::is_directory(p) << "\n";

        if (!fs::is_directory(p))
        {
            std::cout << "* file size: " << fs::file_size(p) << " bytes\n";

            auto t = to_time_t(fs::last_write_time(p));
            std::cout << "* last modified: " << std::asctime(std::localtime(&t));
        }
        else
        {
            std::size_t file_count = 0;
            std::size_t dir_count  = 0;

            for (auto& entry : fs::directory_iterator(p))
            {
                if (entry.is_regular_file()) ++file_count;
                else if (entry.is_directory()) ++dir_count;
            }

            std::cout << "* directory contents:\n";
            std::cout << "  - files: " << file_count << "\n";
            std::cout << "  - directories: " << dir_count << "\n";
        }
    }

    return 0;
}
