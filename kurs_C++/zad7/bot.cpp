#include "bot.hpp"

using namespace std;

pair<int, int> bot(Plansza plansza)
{
    int w1, w2;
    bool ok = false;

    while(!ok)
    {
        w1 = rand() % plansza.rozmiar;
        w2 = rand() % plansza.rozmiar;
        if(plansza.pola[w1][w2] == 0) ok = true;
    }
    return make_pair(w1, w2);
}

int sztuczna_gra(Plansza plansza, int a, int b)
{   
    int n = plansza.rozmiar;
    Plansza kopia = Plansza(n);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            kopia.pola[i][j] = plansza.pola[i][j];
        }
    }
    kopia.tura = plansza.tura;
    kopia.wykonaj_ruch(a,b);
    //cout<<a<<" "<<b<<endl;
    //rysuj_plansze(kopia);
    pair<int,int> p;
    while(!kopia.wygrana() && kopia.tura <n*n)
    {
        p = bot(kopia);
        if(rand()%2 == 0)
        {
            kopia.wykonaj_ruch(p.first, p.second);
        }
        //rysuj_plansze(kopia);
    }
    //rysuj_plansze(kopia);
    if(kopia.wygrana() && kopia.tura % 2 == 0) 
    {
        kopia.~Plansza();
        return 6;
    }
    //rysuj_plansze(kopia);
    if(kopia.wygrana() && kopia.tura % 2 == 1) 
    {
        kopia.~Plansza();
        return -5;
    }
    kopia.~Plansza();
    return 1;
}

pair<int,int> madry_bot(Plansza plansza)
{
    int n = plansza.rozmiar;
    pair<int,int> naj_ruch;
    int ile_wygranych = 0;
    int ile_max = -1000000;

    for(int i=0; i<n;i++)
    {
        for(int j=0; j<n; j++)
        {
            if(plansza.pola[i][j] == 0)
            {
                //cout<<"pole["<<i<<"]"<<"["<<j<<"] ";
                for(int k=0; k<10000; k++)
                {   
                    //cout<<"SZTUCZNA GRA NA "<<i<<" "<<j<<endl;
                    ile_wygranych += sztuczna_gra(plansza, i ,j);
                    //cout<<ile_wygranych<<endl;
                }
                //cout<<": punktow "<<ile_wygranych<<endl;
                if(ile_wygranych>=ile_max)
                {
                    ile_max = ile_wygranych;
                    naj_ruch = make_pair(i,j);
                }
                //cout<<"Po petli: "<<ile_wygranych<<endl<<endl;
                ile_wygranych = -1000000;
            }
        }
    }
    return naj_ruch;
}