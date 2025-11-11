#include <iostream>
#include <limits>

int main()
{
    std::cout << "min. pos. long double = " << std::numeric_limits<long double>::min() << "\n";

    std::cout << "max. pos. long double = " << std::numeric_limits<long double>::max() << "\n";

    // long double x = std::numeric_limits<long double>::infinity();
    std::cout << "does long double have infinity? " << std::numeric_limits<long double>::has_infinity << "\n";

    std::cout << "1 and smallest >1 diff = " << std::numeric_limits<long double>::epsilon() << "\n";
}