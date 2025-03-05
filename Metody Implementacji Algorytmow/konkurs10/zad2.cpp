#include <bits/stdc++.h>
using namespace std;


int main(){
    string s, t;
    bool tmp;
    cin>>s>>t;
    int t1[26] = {0},t2[26] = {0};
    for(int i=0;i<s.length();i++){
        t1[s[i]-'a']++;
    }
    for(int i=0;i<t.length();i++){
        t2[t[i]-'a']++;
    }

    // cout<<s<<endl;
    // for(int i=0;i<26;i++){
    //     cout<<t1[i]<<" ";
    // }
    // cout<<endl;
    // cout<<t<<endl;
    // for(int i=0;i<26;i++){
    //     cout<<t2[i]<<" ";
    // }
    // cout<<endl;

    //array
    if(s.length() == t.length()){
        tmp = true;
        for(int i=0;i<26;i++){
            if(t1[i]!=t2[i]){
                tmp = false;
                break;
            }
        }
        if(tmp){
            cout<<"array";
            return 0;
        }
    }
    //automaton
    if(s.length()>t.length()){
        int k = 0, i = 0;
        while(i<s.length() and k<t.length()){
            if(s[i]==t[k]){
                i++;
                k++;
            }
            else{
                i++;
            }
        }
        if(k==t.length()){
            cout<<"automaton";
            return 0;
        }
    }

    //both
    if(s.length()>t.length()){
        tmp = true;
        for(int i=0;i<26;i++){
            if(t2[i]>t1[i]){
                tmp = false;
                break;
            }
        }
        if(tmp){
            cout<<"both";
            return 0;
        }
    }

    cout<<"need tree";
    return 0;
}