#include <bits/stdc++.h>
#include <math.h>
using namespace std;

long long odl_kw(long long a, long long b, long long c, long long d){
    long long x = abs(a-c);
    long long y = abs(b-d);
    return x*x+y*y;
}

bool czyWspolliniowe(long long a1, long long a2, long long b1, long long b2, long long c1, long long c2){
    if (a1 == b1) {
        return (c1 == a1);
    }

    if((b2 - a2)*(c1 - b1) == (b1 - a1)*(c2 - b2)){
        return true;
    }
    return false;
}

int main(){
    long long a1,a2,b1,b2,c1,c2;
    cin>>a1>>a2>>b1>>b2>>c1>>c2;

    if(czyWspolliniowe(a1,a2,b1,b2,c1,c2)){
        cout<<"no";
        return 0;
    }

    if(odl_kw(a1,a2,b1,b2) == odl_kw(b1,b2,c1,c2)){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    
    return 0;
}