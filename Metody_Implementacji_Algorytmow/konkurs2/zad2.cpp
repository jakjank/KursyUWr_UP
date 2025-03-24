#include <iostream>
using namespace std;

int main(){
    int n,x,y,tmp=0; //y przeciwne
    string a,b="";
    cin>>n>>x>>y;
    cin>>a;
    int w =0;
    b+=a[0];

    for(int i=1;i<n;i++){
        while(a[i]==a[i-1]){
            i++;
        }
        if(i<n){
            b+=a[i];
        }
    }
    
    cout<<b<<endl;
    for(int i=0;i<b.length();i++){
        if(b[i]=='0'){
            tmp++;
        }
    }
    
    if(y<=x){
        cout<<tmp*y;
        return 0;
    }
    if(tmp==0){
        cout<<0;
        return 0;
    }
    cout<<(tmp-1)*x + y;

    return 0;
}