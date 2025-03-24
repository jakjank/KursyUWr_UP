#include <bits/stdc++.h>
using namespace std;


int main(){
    long long n,m,l;

    cin>>n>>m>>l;

    long long t[n];
    for(int i=0;i<n;i++){
        cin>>t[i];
    }
    
    if(n>=2){
        int k=0,czas=0;
        while(k<n){
            if(t[k]>l){
                czas++;
                k++;
                while(t[k]>l and k<n){
                    k++;
                }
            }
            else{
                k++;
            }
        }

        while(m--){
            int co;
            cin>>co;
            if(co == 1){
                long long a,b;
                cin>>a>>b;
                a= a-1;
                bool smaller = t[a]<=l;
                t[a] += b;
                bool bigger = t[a]>l;

                if(a != 0 and a != n-1 and smaller){
                    if(t[a-1]>l and t[a+1]>l and bigger){
                        czas--;
                    }
                    if(t[a-1]<=l and t[a+1]<=l and bigger){
                        czas++;
                    }
                }
                if(a==0){
                    if(t[1]<=l and smaller and bigger){
                        czas++;
                    }
                }
                if(a==n-1){
                    if(t[n-2]<=l and smaller and bigger){
                        czas++;
                    }
                }
                
            }
            else{
            cout<<czas<<endl;
            }

        }
    }
    else{
        while(m--){
            int co;
            cin>>co;
            if(co==0){
                if(t[0]>l){
                    cout<<1<<endl;
                }
                else{
                    cout<<0<<endl;
                }
            }
            else{
                int a,b;
                cin>>a>>b;
                t[a-1]+=b;
            }
        }
        
    }

    return 0;
}