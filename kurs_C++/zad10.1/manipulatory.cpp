#include "manipulatory.hpp"
#include <limits>
#include <iomanip>

using namespace std;

istream& clearline(istream& is)
{
    char c;
    while (is.get(c) && c != '\n')
    {
        // Pomijanie znaków w bieżącej linii
    }

    // Usunięcie znaku przejścia do nowej linii (jeśli został odczytany)
    if (c == '\n')
        is.ignore(numeric_limits<streamsize>::max(), '\n');

    return is;
}

ignore::ignore(int h)
{
    how_many = h;
}

istream &operator>>(istream &is, const ignore &ign)
{
    char c;
    int ignored = 0;

    while (ignored < ign.how_many && is.get(c) && c != '\n')
    {
        // Pomijanie znaków
        ignored++;
    }

    return is;
}

ostream& coma(ostream& ostr)
{
    return ostr << ", ";
}
ostream& colon(ostream& ostr)
{
    return ostr << ": ";
}

index::index(int x, int w)
{
    number = x;
    width  = w;
}

ostream& operator<<(ostream& ostr, const index& ind)
{
    return ostr << "[" << setw(ind.width) << ind.number << "]";
}