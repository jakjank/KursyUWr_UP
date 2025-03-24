#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>

using namespace std;

class Trojkat {
private:
    double bok1;
    double bok2;
    double bok3;
    string nazwa;

public:
    Trojkat(double a, double b, double c, string name) : bok1(a), bok2(b), bok3(c), nazwa(name) {
        if (!czyTrojkat()) {
            throw invalid_argument("Nieprawidłowe długości boków trójkąta");
        }
    }

    Trojkat() : bok1(1), bok2(1), bok3(1), nazwa("Trojkat1") {}

    double getBok1() const {return bok1; }
    double getBok2() const {return bok2; }
    double getBok3() const {return bok3; }

    double obwod() const {return bok1 + bok2 + bok3; }

    double pole() const {
        double p = obwod() / 2.0;
        return sqrt(p * (p - bok1) * (p - bok2) * (p - bok3));
    }

    friend ostream& operator<<(ostream& os, const Trojkat& trojkat) {
        os << "Nazwa: " << trojkat.nazwa << ", Boki: " << trojkat.bok1 << ", " << trojkat.bok2 << ", " << trojkat.bok3;
        return os;
    }

private:
    bool czyTrojkat() const {
        return (bok1 + bok2 > bok3 && bok2 + bok3 > bok1 && bok3 + bok1 > bok2);
    }
public:
    bool czyOstrokaktny() const {
        double longest = max(max(bok1, bok2), bok3);
        if (longest == bok1) {
            return (bok1 * bok1 < bok2 * bok2 + bok3 * bok3);
        } else if (longest == bok2) {
            return (bok2 * bok2 < bok1 * bok1 + bok3 * bok3);
        } else {
            return (bok3 * bok3 < bok1 * bok1 + bok2 * bok2);
        }
    }
};

int main() {
    vector<Trojkat> trojkaty = {
        Trojkat(3, 4, 5, "Trojkat1"),
        Trojkat(6, 8, 10, "Trojkat2"),
        Trojkat(5, 5, 5, "Trojkat3"),
        Trojkat(7, 7, 10, "Trojkat4"),
        Trojkat(5, 12, 13, "Trojkat5"),
    };

    // Sortowanie trójkątów według długości obwodu
    sort(trojkaty.begin(), trojkaty.end(), [](const Trojkat& t1, const Trojkat& t2) {
        return t1.obwod() < t2.obwod();
    });

    std::cout << "Posortowane trojkaty wedlug dlugosci obwodu:" << endl;
    for (const auto& trojkat : trojkaty) {
        std::cout << trojkat << ", Obwod: " << trojkat.obwod() << endl;
    }

    // Wskaźnik do trójkąta o maksymalnym polu
    auto maxPol = max_element(trojkaty.begin(), trojkaty.end(), [](const Trojkat& t1, const Trojkat& t2) {
        return t1.pole() < t2.pole();
    });
    cout << "Trojkat o maksymalnym polu: " << *maxPol << ", Pole: " << maxPol->pole() << endl;

    // Wskaźnik do trójkąta o minimalnym polu
    auto minPol = std::min_element(trojkaty.begin(), trojkaty.end(), [](const Trojkat& t1, const Trojkat& t2) {
        return t1.pole() < t2.pole();
    });
    std::cout << "Trojkat o minimalnym polu: " << *minPol << ", Pole: " << minPol->pole() << endl;

    // Wypisanie tylko trójkątów ostrokątnych
    cout << "Trojkat ostrokatne:" << endl;
    for_each(trojkaty.begin(), trojkaty.end(), [](const Trojkat& trojkat) {
        if (trojkat.czyOstrokaktny()) {
            cout << trojkat << endl;
        }
    });

    return 0;
}