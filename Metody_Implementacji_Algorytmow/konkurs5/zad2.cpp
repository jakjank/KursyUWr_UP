#include <bits/stdc++.h>
using namespace std;

long long koszt_k_pamiatek(long long a[],long long b[],long long k,long long n){
    long long w=0;
    for(int i=0;i<n;i++){
        b[i] = a[i] + k*(i+1);
    }
    sort(b,b+n);
    // cout<<endl<<"dla k="<<k<<": ";
    // for(int i=0;i<n;i++){
    //     cout<<b[i]<<" ";
    // }
    // cout<<endl;
    for(int i=0;i<k;i++){
        w+=b[i];
    }
    
    return w;
}

int main(){
    long long n,S;
    cin>>n>>S;
    long long a[n];
    long long b[n];

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    long long koszt=0, srodek=0, prawa = n-1, lewa = 0;
    while(lewa<=prawa){
        // cout<<"prawa ="<<prawa<<" lewa ="<<lewa<<" ->";
        srodek = (prawa+lewa)/2;
        // cout<<"srodek ="<<srodek<<endl;
        koszt = koszt_k_pamiatek(a,b,srodek,n);
        if(koszt > S){
            prawa=srodek-1;
        }
        else{
            lewa=srodek+1;
        }
    }
    // cout<<"prawa ="<<prawa<<" lewa ="<<lewa<<" ->";

    srodek = (prawa+lewa)/2;
    // cout<<"srodek ="<<srodek<<endl;
    // cout<<"koszt dla 3: "<<koszt_k_pamiatek(a,b,1,n)<<" "<<koszt_k_pamiatek(a,b,2,n)<<" "<<koszt_k_pamiatek(a,b,3,n);
    while(koszt_k_pamiatek(a,b,srodek,n)<=S and srodek<=n){
        srodek++;
    }
    srodek--;
    cout<<srodek<<" "<<koszt_k_pamiatek(a,b,srodek,n);

    return 0;
}