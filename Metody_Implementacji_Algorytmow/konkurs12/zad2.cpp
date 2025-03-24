#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    int tmp;
    cin>>t;

    while(t--){
        int n;
        cin>>n;
        int ones = 0;
        bool cos_innego = false;
        for(int i=0;i<n;i++){
            cin>>tmp;
            if(tmp==1 and !cos_innego){
                ones++;
            }
            else{
                cos_innego=true;
            }
        }
        
        if(ones==n){
            if(ones%2==0){
                cout<<"Second"<<endl;
            }
            else{
                cout<<"First"<<endl;
            }
        }
        else{
            if(ones%2==1){
                cout<<"Second"<<endl;
            }
            else{
                cout<<"First"<<endl;
            }
        }

    }

    return 0;
}