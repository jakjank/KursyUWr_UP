#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin>>n;
    int t[n], sorted[n];
    
    for(int i=0;i<n;i++){
        cin>>t[i];
        sorted[i] = t[i];
    }
    sort(sorted, sorted + n);

    int m,l,r,type;
    long long sum_t[n+1], sum_s[n+1];
    sum_s[0] = 0;
    sum_t[0] = 0;
    for(int i=1;i<=n;i++){
        sum_s[i] = sum_s[i-1] + sorted[i-1];
        sum_t[i] = sum_t[i-1] + t[i-1];
    }
    cin>>m;
    while(m--){
        cin>>type>>l>>r;
        if(type==1){
            cout<<sum_t[r] - sum_t[l-1]<<endl;
        }
        else{
            cout<<sum_s[r] - sum_s[l-1]<<endl;
        }
    }

    return 0;
}