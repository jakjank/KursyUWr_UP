#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <random>
#include <chrono>

using namespace std::chrono_literals;

std::atomic<bool> running{true};

void worker(std::string name)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(500, 1000);

    while (running.load())
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(dist(rng))
        );

        std::cout << "Thread: " << name << std::endl;
    }
}

int main()
{
    std::vector<std::thread> threads;

    std::vector<std::string> names = {
        "A", "B", "C", "D"
    };

    for (const auto& name : names)
        threads.emplace_back(worker, name);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    running.store(false);

    for (auto& t : threads)
        t.join();

    std::cout << "Done\n";
    return 0;
}
