#include "bot.hpp"

using namespace std;

pair<int,string> maly_bot(Plansza_mala &plansza)
{
    srand(time(NULL));
    string wsp[3] = {"a", "b", "c"};
    // ale wtedy info o zlych danych...
    // while(plansza.wykonaj_ruch(rand() % 3, wsp[rand() % 3])){}
    int w1, w2;
    bool ok = false;

    while(!ok)
    {
        w1 = rand() % 3;
        w2 = rand() % 3;
        if(plansza.pola[w1][w2] == 0) ok = true;
    }
    return make_pair(w1+1, wsp[w2]);
}

pair<int,string> duzy_bot(Plansza_duza &plansza)
{
    string wsp[4] = {"a", "b", "c", "d"};
    int w1, w2;
    bool ok = false;

    while(!ok)
    {
        w1 = rand() % 4;
        w2 = rand() % 4;
        if(plansza.pola[w1][w2] == 0) ok = true;
    }
    return make_pair(w1+1, wsp[w2]);
}