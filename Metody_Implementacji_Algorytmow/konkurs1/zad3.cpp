#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin>>s;
    long long a,b;
    cin>>a>>b;
    int rema[s.length()] = {0}, 
        remb[s.length()] = {0};

    rema[0] = (s[0]-'0') % a;
    for(int i=1; i<s.length();i++){
        rema[i] = (rema[i-1]*10 + (s[i]-'0'))%a;
    }

    int P = 1;
    remb[s.length()-1] = (s[s.length()-1]-'0') % b;
    for(int i=s.length()-2; i>=0;i--){
        P = (P*10)%b;
        remb[i] = (remb[i+1] + (s[i]-'0')*P)%b;
    }

    // for(int i=0;i<s.length();i++){
    //     cout<<i<<" "<<rema[i]<<" "<<remb[i]<<endl;
    // }
    
    for(int i=0; i<s.length()-1; i++){
        // cout<<rema[i]<<" "<<remb[i+1]<<" "<<s[i+1]<<" "<<i<<endl;
        if(rema[i] == 0 and remb[i+1] == 0 and s[i+1] != '0' and (s[i] != '0' or i != 0)){
            cout<<"YES"<<endl;
            for(int k=0;k<=i;k++){
                cout<<s[k];
            }
            cout<<endl;
            for(int k=i+1;k<s.length();k++){
                cout<<s[k];
            }
            cout<<endl;
            return 0;
        }
        // if(rema[i]==0){
        //     cout<<1<<endl;
        // }
        // if(remb[i+1]==0){
        //     cout<<2<<endl;
        // }
        // if(s[i+1] != '0'){
        //     cout<<3<<endl;
        // }
    }
    cout<<"NO";
    return 0;
}