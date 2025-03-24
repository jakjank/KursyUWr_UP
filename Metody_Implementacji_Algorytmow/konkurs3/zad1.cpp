#include <bits/stdc++.h>
using namespace std;

int main(){
    int t,n,m;
    cin>>t;

    for(int k=0;k<t;k++){
        cin>>n>>m;
        string c[n];
        for(int i=0;i<n;i++){
            cin>>c[i];
        }
        string v="vika";
        int cur=0;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(c[j][i] == v[cur]){
                    cur++;
                    break;
                }
            }
            if(cur==4){
                cout<<"YES"<<endl;
                i=m;
            }
        }
        if(cur<4){
            cout<<"NO"<<endl;
        }
    }

    return 0;
}