#include "komunikacja.hpp"
#include <ctype.h>
#include <cstdlib>
#include <ctime>

using namespace std;

pair<int,int> konwersja(char a, char b)
{
    if(isdigit(a) != 0) //a - liczba
    {
        if(isupper(b)!=0) return make_pair(a-'1', b-'A'); 
        return make_pair(a-'1', b-'a'); 
    }

    if(isupper(a) != 0) return make_pair(b-'1',a-'A');
    return make_pair(b-'1',a-'a'); 
    
}

void rysuj_plansze(Plansza plansza)
{
    string litery[9] = {"a","b","c","d","e","f","g","h","i"};
    int n = plansza.rozmiar;

    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"     "<<litery[i];
    }
    cout<<endl<<"   ";
    for(int i=0; i<n*6-1; i++)
    {
        cout<<"_";
    }
    cout<<endl;
    for(int i=0; i<4*n-1; i++)
    {
        if(i%4 == 1)
        {
            cout<< i/4+1 <<" |";
            for(int j=0; j<n;j++)
            {
                if(plansza.pola[i/4][j] == -1) cout<<"  X  ";
                if(plansza.pola[i/4][j] == 0)  cout<<"     ";
                if(plansza.pola[i/4][j] == 1)  cout<<"  O  ";
                if(j < n-1) cout<< "#";
            }
            cout<<endl;
        }
        if(i%2 == 0)
        {
            cout<<"  |";
            for(int j=1; j<6*n; j++)
            {
                if(j%6 == 0)
                {
                    cout<<"#";
                }
                else
                {
                    cout<<" ";
                }
            }
            cout<<endl;
        }
        if(i%4 == 3)
        {
            cout<<"  |";
            for(int j=0; j<6*n-1; j++) cout<<"#";
            cout<<endl;
        }
    }
}

void graj()
{
    srand(time(NULL));
    int n, poziom;
    do
    {
        cout<<"Wybierz rozmiar planszy: "; cin>>n;
        if(n<3) cout<<endl<<"Za maly rozmiar planszy"<<endl;
    } 
    while (n<3);
    
    do
    {
        cout<<"wybierz poziom: latwy(1), trudny(2): "; cin>> poziom;
        if(poziom != 1 && poziom != 2) cout<<endl<<"Wybrano zly poziom"<<endl;
    } while (poziom != 1 && poziom != 2);

    Plansza plansza = Plansza(n);
    int w1, w2;
    char a;
    char b;
    pair<int,int> p;
    rysuj_plansze(plansza);

    while(!plansza.wygrana() && plansza.tura < plansza.rozmiar*plansza.rozmiar)
    {
        if(plansza.tura % 2 == 0)
        {   
            do
            {
                cout<<"Podaj pole: "; cin>>a; cin>>b;
                p = konwersja(a,b);
            }
            while(!plansza.wykonaj_ruch(p.first, p.second));
            rysuj_plansze(plansza);
        }
        else
        {
            if(poziom == 1)
            {
                p = bot(plansza);
            }
            else
            {
                p = madry_bot(plansza);
            }
            plansza.wykonaj_ruch(p.first, p.second);
            cout<<"Ruch bota: "<<endl;
            rysuj_plansze(plansza);
        }
    }
    if(plansza.wygrana())
    {
        if(plansza.tura % 2 == 1) 
            cout<<"BRAWO WYGRALES!"<<endl;
        else 
            cout<<"BOT WYGRAL!"<<endl;     
    }
    else
    {
        cout<<"REMIS!"<<endl;;
    }
    string decyzja;
    cout<<"Czy chcesz zagrac jeszcze raz? [t/n] "; cin>>decyzja;
    if(decyzja == "t") graj();
}