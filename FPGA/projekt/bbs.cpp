#include <chrono>
#include <iostream>
#include <cstdint>

void bbs(uint64_t seed, uint64_t p, uint64_t q)
{
    uint64_t M = p * q;
    uint64_t x = seed;
    uint64_t count = 0;
    auto start = std::chrono::system_clock::now();

    while (std::chrono::system_clock::now() - start < std::chrono::seconds(1))
    {
        __uint128_t tmp = ( __uint128_t )x * x;
        x = (uint64_t)(tmp % M);
        count++;
        // std::cout << (x & 1);
    }
    std::cout << "Produced " << count << " bits in 1 second";
}

int main()
{
    bbs(
        65537,
        2147483647,
        2147483629
    );
    return 0;
}