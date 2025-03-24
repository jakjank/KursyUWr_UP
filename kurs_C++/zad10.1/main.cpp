#include "manipulatory.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void sort_rows()
{
    ifstream plik;
    plik.open("dane2.txt"); 
    string a;
    int k = 0;
    vector<pair<string,int>> v;
    while(!plik.eof())
    {
        plik >> a;
        //cout << a << " *" << endl ;
        v.push_back(make_pair(a,k));
        k++;
    }

    sort(v.begin() , v.end());
    for(int i=0;i<v.size();i++)
    {
        cout << index(v[i].second, 3) << v[i].first << endl;
    }
}

int main()
{
    string a, b, c, d;
    ifstream plik;
    plik.open("dane.txt");  
    plik >> ignore(2) >> a >> ws 
         >> ignore(7) >> b >> ws 
         >> c
         >> clearline >> d;
    //                        ^^nie dzialalo bez czyszczenia bufora
    cout << "Co zapisalismy" << colon 
         << a << coma 
         << b << coma 
         << c << coma 
         << d << endl;
    
    sort_rows();

    return 0;
}