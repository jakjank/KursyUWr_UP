#include "stan_gry.hpp"
using namespace std;

Plansza_mala::Plansza_mala()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            pola[i][j] = 0;
        }
    }
    tura = 0;
}

Plansza_duza::Plansza_duza()
{
    for(int i=0; i<16; i++)
    {
        pola[i/4][i%4] = 0;
    }
    tura = 0;
}
// troche glupio ze wykonaj ruch bierze int i string a nie dwa int ale
// uswiadomilem to sobie dopiero w polowie pisania
bool Plansza_mala::wykonaj_ruch(int wsp1, string wsp2)
{
    if(wsp1 < 1 || wsp1>3 || (wsp2 != "a" && wsp2 != "b" && wsp2 != "c"))
    {
        cout << "Wprowadzono zle dane"<<endl;
        return false;
    }
    int tmp1 = wsp1 - 1;
    int tmp2;
    if(wsp2 == "a") tmp2 = 0;
    if(wsp2 == "b") tmp2 = 1;
    if(wsp2 == "c") tmp2 = 2;

    if(pola[tmp1][tmp2] != 0)
    {
        cout << "Wybrane pole jest juz zajete"<<endl;
        return false;
    }
    if(tura % 2 == 0)
    {
        pola[tmp1][tmp2] = 1;
    }
    else
    {
        pola[tmp1][tmp2] = -1;
    }
    tura++;
    return true;
}

bool Plansza_duza::wykonaj_ruch(int wsp1, string wsp2)
{
    if(wsp1 < 1 || wsp1>4 || (wsp2 != "a" && wsp2 != "b" && wsp2 != "c" && wsp2 != "d"))
    {
        cout << "Wprowadzono zle dane"<<endl;
        return false;
    }
    int tmp1 = wsp1 - 1;
    int tmp2;
    if(wsp2 == "a") tmp2 = 0;
    if(wsp2 == "b") tmp2 = 1;
    if(wsp2 == "c") tmp2 = 2;
    if(wsp2 == "d") tmp2 = 3;

    if(pola[tmp1][tmp2] != 0)
    {
        cout << "Wybrane pole jest juz zajete"<<endl;
        return false;
    }
    if(tura % 2 == 0)
    {
        pola[tmp1][tmp2] = 1;
    }
    else
    {
        pola[tmp1][tmp2] = -1;
    }
    tura++;
    return true;
}

bool Plansza_mala::wygrana()
{
    // przekatne
    if(pola[0][0] == pola[1][1] && pola[1][1] == pola[2][2] && pola[1][1] != 0) return true;
    if(pola[2][0] == pola[1][1] && pola[1][1] == pola[0][2] && pola[1][1] != 0) return true;

    int suma;
    for(int i=0;i<3;i++)
    {
        suma = 0;
        for(int j=0;j<3;j++)
        {
            suma += pola[i][j];
        }
        if(suma == 3 || suma == -3) return true;
    }
    for(int i=0;i<3;i++)
    {
        suma = 0;
        for(int j=0;j<3;j++)
        {
            suma += pola[j][i];
        }
        if(suma == 3 || suma == -3) return true;
    }
    return false;
}

bool Plansza_duza::wygrana()
{
    if(pola[0][0]+pola[1][1]+pola[2][2]+pola[3][3] == 4 || pola[0][0]+pola[1][1]+pola[2][2]+pola[3][3] == -4) return true;
    if(pola[3][0]+pola[2][1]+pola[1][2]+pola[0][3] == 4 || pola[3][0]+pola[2][1]+pola[1][2]+pola[0][3] == -4) return true;
    
    int suma;
    for(int i=0;i<4;i++)
    {
        suma = 0;
        for(int j=0;j<4;j++)
        {
            suma += pola[i][j];
        }
        if(suma == 4 || suma == -4) return true;
    }
    for(int i=0;i<4;i++)
    {
        suma = 0;
        for(int j=0;j<4;j++)
        {
            suma += pola[j][i];
        }
        if(suma == 4 || suma == -4) return true;
    }
    

    return false;
}