#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;

    int a[n], b[m];
    for(int j=0;j<n;j++){
        cin>>a[j];
    }
    for(int j=0;j<m;j++){
        cin>>b[j];
    }
    sort(a,a+sizeof(a)/sizeof(a[0]));
    int lewy,prawy,wynik,srodek;

    for(int j=0;j<m;j++){
        lewy = 0;
        prawy = n-1;
        while(lewy<=prawy){
            srodek = (lewy+prawy)/2;
            if(a[srodek]>b[j]){
                prawy = srodek-1;
            }
            else{
                lewy = srodek+1;
            }
        }
        wynik = prawy;
        if(wynik < 0){
            wynik = 0;
        }
        while(a[wynik]<=b[j] and wynik<n){
            wynik++;
        }
        cout<<wynik<<" ";
    }
    
    return 0;
}