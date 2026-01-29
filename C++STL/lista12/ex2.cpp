#include <iostream>
#include <chrono>
#include <unistd.h>

int main()
{
    using clock = std::chrono::steady_clock;
    using namespace std::chrono;

    auto start = clock::now();
    auto end   = start + seconds(10);

    bool warned5 = false;
    bool warned3 = false;
    bool warned1 = false;

    sleep(5);
    std::cout << "5\n";
    sleep(2);
    std::cout << "3\n";
    sleep(2);
    std::cout << "1\n";
    sleep(1);
    // while (clock::now() < end)
    // {
    //     auto remaining = duration_cast<seconds>(end - clock::now()).count();

    //     if (remaining <= 5 && !warned5) {
    //         std::cout << "5\n";
    //         warned5 = true;
    //     }

    //     if (remaining <= 3 && !warned3) {
    //         std::cout << "3\n";
    //         warned3 = true;
    //     }

    //     if (remaining <= 1 && !warned1) {
    //         std::cout << "1\n";
    //         warned1 = true;
    //     }
    // }

    std::cout << "Done\n";
    return 0;
}