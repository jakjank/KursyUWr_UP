#include <iostream>
#include <list>
#include <vector>

int main()
{
    auto sum = []<typename T>(T& container)
    {
        using value_t = typename T::value_type;
        value_t result{};
        for (auto& x : container)
            result += x;
        return result;
    };

    std::vector<int> v {1, 2, 3, 4};
    std::list<double> l {1.5, 2.5, 3.5};

    std::cout << "Suma vector<int>: "  << sum(v) << "\n";
    std::cout << "Suma list<double>: " << sum(l) << "\n";

    return 0;
}