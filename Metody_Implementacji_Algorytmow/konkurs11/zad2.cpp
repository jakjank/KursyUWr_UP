#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main(){
    int n,q,l,r;
    cin>>n>>q;
    int t[n]={0}, h[n]={0};
    for(int i=0;i<n;i++){
        cin>>t[i];
    }

    for(int i=0;i<q;i++){
        cin>>l>>r;
        for(int j=l-1;j<r;j++){
            h[j]++;
        }
    }

    long long sum=0;
    sort(h,h+n);
    sort(t,t+n);
    for(int i=0;i<n;i++){
        sum += h[i] * t[i];
    }
    cout<<sum;


    return 0;
}