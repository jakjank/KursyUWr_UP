#include <cstdint>
#include <iostream>

auto lucasNumber(uint64_t n)
{
    if(n < 0) return uint64_t{0};

    if (n == 0) return uint64_t{2};
    if (n == 1) return uint64_t{1};
    return lucasNumber(n - 1) + lucasNumber(n - 2);
}

int main()
{
    std::cout << lucasNumber(17) << "\n";
    return 0;
}