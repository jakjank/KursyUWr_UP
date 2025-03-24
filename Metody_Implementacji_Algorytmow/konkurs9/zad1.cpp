#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int t[n];

    for(int i=0;i<n;i++){
        cin>>t[i];
    }
    
    for(int i=0; i<n; i++){
        if(t[t[t[i]-1]-1] == i+1){
            cout<<"YES";
            return 0;
        }
    }

    cout<<"NO";
    return 0;
}
