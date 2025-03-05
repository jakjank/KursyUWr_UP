#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main(){
    int n,tmp;
    cin>>n;
    int t[n+1] = {0};
    int z = n;

    for(int i=0;i<n;i++){

        cin>>tmp;
        t[tmp] = 1;
        while(t[z] == 1){
            cout<<z<<" ";
            z--;
        }
        cout<<'\n';
    } 
    

    return 0;
}