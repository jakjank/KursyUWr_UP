#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,a,b,c;
    int d[3];
    cin>>n>>d[0]>>d[1]>>d[2];
    sort(d, d+sizeof(d)/sizeof(d[0]));
    a = d[0];
    b = d[1];
    c = d[2];
    int maxi=0;
    
    for(int B=0;B<=n/c;B++){ //BIG
        for(int M=0;M<=n/b;M++){ //MEDIUM
            if((n-(B*c)-(M*b))%a==0){
                if(B+M+((n-(B*c)-(M*b))/a)>maxi){
                    maxi= B+M+((n-(B*c)-(M*b))/a);
                }
            }
        }
    }
    cout<<maxi;

    return 0;
}