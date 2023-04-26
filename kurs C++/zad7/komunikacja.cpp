#include "komunikacja.hpp"
using namespace std;

void rysuj_mala_plansze(Plansza_mala plansza)
{
    cout<<endl;
    cout<<"    a   b   c  "<<endl<<"   ____________"<<endl;
    for(int i=0; i<11; i++){
        if(i == 1 || i == 5 || i == 9)
        {
            cout << i/4+1<<" |";
            for(int j=0; j<3;j++){
                if(plansza.pola[i/4][j] == -1) cout<<" X ";
                if(plansza.pola[i/4][j] == 0)  cout<<"   ";
                if(plansza.pola[i/4][j] == 1)  cout<<" O ";
                if(j < 2) cout<< "#";
            }
            cout<<endl;
        }
        if(i % 2 == 0) 
        {
            cout<<"  |   #   #   "<<endl;
        }
        if(i ==3 || i == 7)
        {
            cout<<"  |###########"<<endl;
        }   
    }
    cout<<endl;
    // cout << plansza.pola[0][0]<<" "<<plansza.pola[0][1]<<" "<<plansza.pola[0][2]<<endl<<
    //         plansza.pola[1][0]<<" "<<plansza.pola[1][1]<<" "<<plansza.pola[1][2]<<endl<<
    //         plansza.pola[2][0]<<" "<<plansza.pola[2][1]<<" "<<plansza.pola[2][2]<<endl;
}

void mala_gra()
{
    Plansza_mala plansza = Plansza_mala();
    int w1;
    string w2;
    pair <int,string> p;
    rysuj_mala_plansze(plansza);
    while(!plansza.wygrana() && plansza.tura < 9)
    {   
        if(plansza.tura % 2 == 0)
        {
            do
            {
                cout<<"Podaj pole: "; cin>>w1; cin>>w2;
            }
            while(!plansza.wykonaj_ruch(w1,w2));
            rysuj_mala_plansze(plansza);
        }
        else
        {
            p = maly_bot(plansza);
            plansza.wykonaj_ruch(p.first, p.second);
            cout<<"Ruch bota: "<<endl;
            rysuj_mala_plansze(plansza);
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
        cout<<"REMIS!";
    }
    string decyzja;
    cout<<"Czy chcesz zagrac jeszcze raz? [t/n] "; cin>>decyzja;
    if(decyzja == "t") graj();
}

void rysuj_duza_plansze(Plansza_duza plansza)
{
    cout<<endl;
    cout<<"     a     b     c     d  "<<endl<<"   _______________________"<<endl;
    for(int i=0; i<16; i++){
        if(i == 1 || i == 5 || i == 9 || i == 13)
        {
            cout<< i/4+1 <<" |";
            for(int j=0; j<4;j++){
                if(plansza.pola[i/4][j] == -1) cout<<"  X  ";
                if(plansza.pola[i/4][j] == 0)  cout<<"     ";
                if(plansza.pola[i/4][j] == 1)  cout<<"  O  ";
                if(j < 3) cout<< "#";
            }
            cout<<endl;
        }
        if(i % 2 == 0) 
        {
            cout<<"  |     #     #     #     "<<endl;
        }
        if(i ==3 || i == 7 || i == 11)
        {
            cout<<"  |#######################"<<endl;
        }   
    }
    cout<<endl;
}

void duza_gra()
{
    Plansza_duza plansza = Plansza_duza();
    int w1;
    string w2;
    pair <int,string> p;
    rysuj_duza_plansze(plansza);
    while(!plansza.wygrana() && plansza.tura < 16)
    {   
        if(plansza.tura % 2 == 0)
        {
            do
            {
                cout<<"Podaj pole: "; cin>>w1; cin>>w2;
            }
            while(!plansza.wykonaj_ruch(w1,w2));
            rysuj_duza_plansze(plansza);
        }
        else
        {
            p = duzy_bot(plansza);
            plansza.wykonaj_ruch(p.first, p.second);
            cout<<"Ruch bota: "<<endl;
            rysuj_duza_plansze(plansza);
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
        cout<<"REMIS!";
    }
    string decyzja;
    cout<<"Czy chcesz zagrac jeszcze raz? [t/n] "; cin>>decyzja;
    if(decyzja == "t") graj();
}

void graj()
{
    int wybor = 0;
    while(wybor == 0)
    {
        cout<<"Wybierz czy grasz na malej(1) czy duzej(2) planszy: "; 
        cin>>wybor;
    }
    if(wybor == 1)
    {
        mala_gra();
    }
    else
    {
        duza_gra();
    }
}