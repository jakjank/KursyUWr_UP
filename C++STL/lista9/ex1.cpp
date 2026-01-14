#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <iostream>

int main()
{
    std::ifstream file("liczby.txt");
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku\n";
        return 1;
    }

    std::vector<double> v;

    std::copy(
        std::istream_iterator<double>(file),
        std::istream_iterator<double>(),
        std::back_inserter(v));

    double sum = 0;
    for (auto& n : v)
        sum += n;

    auto mean = sum / v.size();

    double tmp = 0;
    std::for_each(v.begin(), v.end(), [&tmp, &mean](double& x){tmp += pow((x - mean), 2); });
    auto variance = tmp / v.size();
    auto deviation = std::sqrt(variance);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Srednia: " << mean << '\n';
    std::cout << "Odchylenie standardowe: " << deviation << '\n';

    return 0;
}