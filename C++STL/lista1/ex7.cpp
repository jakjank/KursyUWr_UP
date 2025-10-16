#include <algorithm>
#include <iostream>
#include <vector>

class Osoba
{
public:
    Osoba(std::string nazwisko, std::string imie, int rok_urodzenia) 
        : m_nazwisko(nazwisko), m_imie(imie), m_rok(rok_urodzenia) {}

    friend bool operator<(const Osoba& l, const Osoba& r) 
    {
        return std::tie(l.m_nazwisko, l.m_imie, l.m_rok)
                < std::tie(r.m_nazwisko, r.m_imie, r.m_rok);
    }

    friend std::ostream& operator<<(std::ostream& os, const Osoba& o)
    {
        os << o.m_nazwisko << " " << o.m_imie << " " << o.m_rok;
        return os;
    }

private:
    std::string m_nazwisko; 
    std::string m_imie;
    int m_rok;
};

int main() {

    std::vector<Osoba> v{{"Kowalski", "Jan", 1988},
                         {"AKowalski", "Jan", 1988},
                         {"Kowalski", "AJan", 1988},
                         {"Kowalski", "Jban", 1988},
                         {"Kowalski", "Jan", 1989}};

    std::sort(v.begin(), v.end());

    for(auto& o : v)
    {
        std::cout << o << '\n';
    }

    return 0;
}
