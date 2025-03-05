#include <bits/stdc++.h>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Node
{
    public:
        int czas_in;
        int czas_out;
        int rodzic_id;
        int brat_id;
        int dziecko_id;

        Node(){
            czas_in = -1;
            czas_out = -1;
            rodzic_id = -1;
            brat_id = -1;
            dziecko_id = -1;
        };
};

int main(){
    int n;
    int q;
    int a,b;
    cin>>n>>q;

    Node tab[n];

    for(int i=1; i<n; i++){
        cin>>a;
        tab[i].rodzic_id = a;
        tab[i].brat_id = tab[a-1].dziecko_id;
        tab[a-1].dziecko_id = i+1;
    }

    int czas = 0, akt = 1, tmp;

    while(akt != -1){
        if(tab[akt-1].czas_in < 0){
            tab[akt-1].czas_in = czas;
        }
        if(tab[akt-1].dziecko_id < 0){
            tab[akt-1].czas_out = czas;
            if(tab[akt-1].brat_id == -1){
                akt = tab[akt-1].rodzic_id;
            }
            else{
                akt = tab[akt-1].brat_id;
                czas++;
            }
        }
        else{
            tmp = tab[akt-1].dziecko_id;
            tab[akt-1].dziecko_id = -2;
            akt = tmp;
            czas++;
        }
    }

    while(q--){
        cin>>a>>b;
        if(tab[a-1].czas_in < tab[b-1].czas_in and
           tab[a-1].czas_out >= tab[b-1].czas_out){
            cout<<"TAK"<<endl;
        }
        else{
            cout<<"NIE"<<endl;
        }
    }

    return 0;
}