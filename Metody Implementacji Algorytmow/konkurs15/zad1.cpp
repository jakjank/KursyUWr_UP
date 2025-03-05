#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int a1,a2,b1,b2,c1,c2;
        cin>>a1>>a2>>b1>>b2>>c1>>c2;
        if(a2 == b2 and a2 > c2){
            cout<<max(b1,a1)-min(b1,a1)<<endl;
        }
        else{
            if(a2 == c2 and a2 > b2){
            cout<<max(c1,a1)-min(c1,a1)<<endl;
            }
            else{
                if(c2 == b2 and b2 > a2){
                    cout<<max(b1,c1)-min(b1,c1)<<endl;
                }
                else{
                    cout<<0<<endl;
                }
            }
        }
    }
    return 0;
}