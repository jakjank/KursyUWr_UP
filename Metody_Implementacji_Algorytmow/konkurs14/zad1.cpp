#include <bits/stdc++.h>
using namespace std;

int silnia(int n){
    if(n==0 or n==1){
        return 1;
    }
    else return silnia(n-1) * n;
}

int main(){
    cout.precision(20);
    string send,got;
    cin>>send>>got;
    int wart1=0, wart2=0, niewiadome=0;
    for(int i=0; i<send.length(); i++){
        if(send[i] == '+') wart1++;
        else wart1--;
        
        if(got[i] == '?') niewiadome++;
        else{
            if(got[i] == '+') wart2++;
            else wart2--;
        }
    }
    int odl = abs(wart1 - wart2);
    if(odl == 0 and niewiadome == 0){
        cout<<double(1);
        return 0;
    }

    if(odl > niewiadome){
        cout<<double(0);
        return 0;
    }
    if((niewiadome - odl) % 2 == 1){
        cout<<double(0);
        return 0;
    }
    double szansa;
    int mozliwosci = pow(2, niewiadome);
    int ile = odl + ((niewiadome-odl)/2);
    int wybieramy = silnia(niewiadome)/(silnia(ile) * silnia(niewiadome-ile));
    szansa = double(wybieramy)/double(mozliwosci);
    szansa = min(double(1) - szansa,szansa);
    //cout<<wybieramy<<endl<<mozliwosci<<endl;
    cout<<szansa;
    return 0;
}