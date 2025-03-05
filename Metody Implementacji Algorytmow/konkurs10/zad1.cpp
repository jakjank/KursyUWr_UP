#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;

int main(){
    int t, n, i;
    cin>>t;
    string s,res;
    bool same;

    for(int j=0;j<t;j++){
        same = false;
        cin>>n>>s;
        res = "";
        i=1;
        if(s.length()>1 and s[0]==s[1]){
            cout<<s[0]<<s[0]<<endl;
            same = true;
        }
        if(!same){
            while(s[i]-s[i-1]<=0 and i<s.length()){
                i++;
            }
            for(int k=0;k<i;k++){
                res += s[k];
            }
            for(int k=i-1;k>=0;k--){
                res += s[k];
            }
            cout<<res<<endl;
        }
    }
    return 0;
}