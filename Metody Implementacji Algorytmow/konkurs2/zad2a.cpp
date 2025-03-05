#include <iostream>
using namespace std;

int main(){
    long long n,x,y,tmp=0; //y przeciwne
    string a;
    cin>>n>>x>>y;
    cin>>a;
    
    for(int i=0;i<n;i++){
        if(a[i]=='0' && (a[i-1] == '1' || i==0)){
            tmp++;
        }
    }

    long long w1 = tmp*y;
    long long w2 = abs((tmp-1)*x + y);
    
    if(w1<=w2){
        cout<<w1;
    }
    else{
        cout<<w2;
    }


    return 0;
}