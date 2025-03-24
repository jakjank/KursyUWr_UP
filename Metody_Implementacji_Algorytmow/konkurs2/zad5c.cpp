#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n, s[3],a,b,c;
    cin>>n>>s[0]>>s[1]>>s[2];
    sort(s, s+sizeof(s)/sizeof(s[0]));
    a=s[0];
    b=s[1];
    c=s[2];

    int t[n];
    for(int i=0;i<n;i++){
        cin>>t[i];
    }
    sort(t,t + sizeof(t)/sizeof(t[0]));

    int godziny=0;
    map<string,int> mymap;
    mymap.insert(pair<string,int>("a",0));
    mymap.insert(pair<string,int>("a",0));
    mymap.insert(pair<string,int>("a",0));
    mymap.insert(pair<string,int>("ab",0));
    mymap.insert(pair<string,int>("ac",0));
    mymap.insert(pair<string,int>("bc",0));
    mymap.insert(pair<string,int>("abc",0));


    if(a+b>c){

    }
    else{

    }

    cout<<godziny;
    return 0;
}