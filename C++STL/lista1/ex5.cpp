#include <iostream>
#include <cmath>

int main() {
    double a, b, c;

    std::cout << "a, b, c: ";
    std::cin >> a >> b >> c;

    if (double delta = b * b - 4 * a * c; delta > 0) {
        double x1 = (-b + std::sqrt(delta)) / (2 * a);
        double x2 = (-b - std::sqrt(delta)) / (2 * a);
        std::cout << "dwa miejsca zerowe: x1 = " << x1 << ", x2 = " << x2 << "\n";
    } else if (delta == 0) {
        double x = -b / (2 * a);
        std::cout << "jedno miejsce zerowe: x = " << x << "\n";
    } else {
        std::cout << "brak miejsc zerowych." << "\n";
    }

    return 0;
}