#include <iostream>
#include "kolornazwany.hpp"
#include <stdexcept>

using namespace std;

kolornazwany::kolornazwany():kolor()
{
    nazwa  = "";
}
kolornazwany::kolornazwany(int r, int g, int b, string n):kolor(r,g,b)
{
    for(int i = 0; i < n.length(); i++)
    {
        if (n[i] - 'a' < 0 or n[i] - 'z' > 0){
            throw invalid_argument("nazwa powinna sie składac z malych liter");
        }
    }
    nazwa = n;
}

void kolornazwany::set_name(string n)
{
    for(int i = 0; i < n.length(); i++)
    {
        if (n[i] - 'a' < 0 or n[i] - 'z' > 0){
            throw invalid_argument("nazwa powinna sie składac z malych liter");
        }
    }
    nazwa = n;
}
string kolornazwany::get_name()
{
    return nazwa;
}