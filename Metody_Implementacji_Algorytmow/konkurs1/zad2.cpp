#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int n;
    cin>>n;
    set<int> x;

    if(n==1){
        int a[6];
        for(int i=0;i<6;i++){
            cin>>a[i];
        }
        for(int i=0;i<6;i++){
            x.insert(a[i]);
        }

    }
    if(n==2){
        int a[6];
        int b[6];
        for(int i=0;i<6;i++){
            cin>>a[i];
        }
        for(int i=0;i<6;i++){
            cin>>b[i];
        }
        for(int i=0;i<6;i++){
            x.insert(a[i]);
            x.insert(b[i]);
            for(int j=0;j<6;j++){
                x.insert(a[i]*10 + b[j]);
                x.insert(b[i]*10 + a[j]);
            }
        }
    }
    if(n==3){
        int a[6];
        int b[6];
        int c[6];
        for(int i=0;i<6;i++){
            cin>>a[i];
        }
        for(int i=0;i<6;i++){
            cin>>b[i];
        }
        for(int i=0;i<6;i++){
            cin>>c[i];
        }
        for(int i=0;i<6;i++){
            x.insert(a[i]);
            x.insert(b[i]);
            x.insert(c[i]);
            for(int j=0;j<6;j++){
                x.insert(a[i]*10 + b[j]);
                x.insert(b[i]*10 + a[j]);
                x.insert(a[i]*10 + c[j]);
                x.insert(c[i]*10 + a[j]);
                x.insert(c[i]*10 + b[j]);
                x.insert(b[i]*10 + c[j]);
            }
        }
    }

    for(int k=0;k<101;k++){
        if(x.count(k+1)==0){
            cout<<k;
            return 0;
        }
    }
    return 0;
}