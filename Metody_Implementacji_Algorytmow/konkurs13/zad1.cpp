#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int cur, maxi = -1000001;
    bool is_sqr;
    for(int i=0;i<n;i++){
        cin>>cur;
        is_sqr = false;
        if(cur < 0){
            if(cur > maxi){
                maxi = cur;
            }
        }
        else{
            for(int j=0; j*j<=cur; j++){
                if(j*j == cur){
                    is_sqr = true;
                }
            }
            if(!is_sqr and cur > maxi){
                maxi = cur;
            }
        }
    }
    cout<<maxi;

    return 0;
}