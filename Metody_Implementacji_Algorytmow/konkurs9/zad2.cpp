#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    int x;
    cin>>n>>m;
    int t[n] = {0};

    for(int i=0; i<2*m;i++){
        cin>>x;
        t[x-1]++;
    }

    int twos=0, ones=0, more=0;
    for(int i=0;i<n;i++){
        if(t[i]==1){
            ones++;
        }
        if(t[i]==2){
            twos++;
        }
        if(t[i]>2){
            more++;
        }
    }

    if(twos == n){
        cout<<"ring topology";
        return 0;
    }
    if(twos == n-2 && ones == 2){
        cout<<"bus topology";
        return 0;
    }
    if(ones == n-1){
        cout<<"star topology";
        return 0;
    }
    cout<<"unknown topology";
    return 0;
}
