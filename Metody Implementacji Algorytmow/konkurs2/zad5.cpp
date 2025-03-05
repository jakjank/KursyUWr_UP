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

    int godziny=0,pokonani=0,i=n-1,j=0;

    if(t[i]> a+b+c){
        cout<<-1;
        return 0;
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<t[i]<<" ";
    }
    cout<<"#"<<godziny<<endl;

    while(pokonani < n){
        if(t[i]>b+c){            //a+b+c
            godziny++;
            pokonani++;
            t[i]=-1;
            i--;
                        
            for(int i=0;i<n;i++){
                cout<<t[i]<<" ";
                }
            cout<<"#"<<godziny<<" abc"<<endl;
            
        }
        if(t[i]>c && t[i]<=b+c && t[i]>a+c){ //b+c
            if(t[j]<=a){
                t[j]=-1;
                pokonani++;
                j++;
            }
            t[i]=-1;
            pokonani++;
            i--;
            godziny++;
                        
            for(int i=0;i<n;i++){
                cout<<t[i]<<" ";
                }
            cout<<"#"<<godziny<<" a bc"<<endl;
            
        } 
        if(t[i]>c && t[i]<=a+c){ //a+c
            if(t[j]<=b){
                pokonani++;
                t[j]=-1;
                j++;
            }
            t[i]=-1;
            pokonani++;
            i--;
            godziny++;
                        
            for(int i=0;i<n;i++){
                cout<<t[i]<<" ";
                }
            cout<<"#"<<godziny<<" b ac"<<endl;
            
        }
        if(t[i]<=c){             //c
            if(t[j]<=a){
                t[j]=-1;
                pokonani++;
                j++;
                if(t[j]<=b){
                    t[j]=-1;
                    pokonani++;
                    j++;
                }
            }
            else{
                if(t[j]<=a+b){
                    t[j]=-1;
                    pokonani++;
                    j++;
                }
            }
            t[i]=-1;
            pokonani++;
            i--;
            godziny++;
                        
            for(int i=0;i<n;i++){
                cout<<t[i]<<" ";
                }
            cout<<"#"<<godziny<<" c a b or c ab"<<endl;
            
        }
        if(t[i]<=a+b && t[i]>c){ //a+b
            if(t[j]<=c){
                t[j]=-1;
                pokonani++;
                j++;
            }
            t[i]=-1;
            i--;
            pokonani++;
            godziny++;

            for(int i=0;i<n;i++){
                cout<<t[i]<<" ";
                }
            cout<<"#"<<godziny<<" ab c"<<endl;    
        }
    }
    cout<<godziny;
    return 0;
}