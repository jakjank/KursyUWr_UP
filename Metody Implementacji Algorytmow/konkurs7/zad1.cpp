#include <bits/stdc++.h>
#include <math.h>

using namespace std;

bool a_in_q(string q){
    for(int i=0;i<q.length();i++){
        if(q[i]=='a'){
            return true;
        }
    }
    return false;
}

int main(){
    cout<<setprecision(30);
    int testcases;
    cin>>testcases;
    string s, q;
    int k = 0;

    for(int i=0;i<testcases;i++){
        cin>>s>>q;

        if(q=="a"){
            cout<<1<<endl;
            k=1;
        }

        if(a_in_q(q) and k !=1){
            cout<<-1<<endl;
            k=1;
        }

        if(k==0){
            cout<<pow(2,s.length())<<endl;
        }
        k=0;
    }
    return 0;
}