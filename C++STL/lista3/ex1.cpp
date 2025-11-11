#include <climits>
#include <cmath>
#include <iostream>
#include <type_traits>

int main()
{
    long long int x = LLONG_MIN;
    std::cout << x << "\n";

    x = LLONG_MAX;
    std::cout << x << "\n";

    std::cout << "# bits = " << sizeof(long long int) * 8 << "\n";

    std::cout << "# decimal digits = " << floor(std::log10(x)) + 1 << "\n";

    std::cout << "is signed " << std::is_signed<long long>() << "\n";
}