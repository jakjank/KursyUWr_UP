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

    int godziny=0,pokonani=0,i=n-1,j=0,tmp=0;

    if(t[i]> a+b+c){
        cout<<-1;
        return 0;
    }
    while(pokonani < n){
        tmp=0;
        if(a+b>c){
            if(t[i]>b+c){  //abc
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
            }
            tmp=0;

            if(t[i]<=b+c && t[i]>a+b){  //a bc
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
                while(t[tmp]==-1 && tmp<n){
                    tmp++;
                }
                if(t[tmp]<=a){
                    t[tmp]=-1;
                    pokonani++;
                }
            }
            tmp=0;

            if(t[i]<=a+b && t[i]>c){    //ab c
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
                while(t[tmp]==-1 && tmp<n){
                    tmp++;
                }
                if(t[tmp]<=c){
                    t[tmp]=-1;
                    pokonani++;
                }
            }
            tmp=0;

            if(t[i]<=c){
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
                while(t[tmp]==-1 && tmp<n){
                    tmp++;
                }
                if(t[tmp]<=a){
                    t[tmp]=-1;
                    pokonani++;
                }
                while(t[tmp]<b && tmp<n){
                    tmp++;
                }
                while(t[tmp]==-1 || t[tmp]>b && tmp>=0){
                    tmp--;
                }
                if(t[tmp]!=-1){
                    pokonani++;
                    t[tmp]=-1;
                }
            }
            tmp=0;
        }
        else{
            if(t[i]>b+c){  //abc
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
            }
            tmp=0;

            if(t[i]<=b+c && t[i]>a+b){  //a bc
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;
                while(t[tmp]==-1 && tmp<n){
                    tmp++;
                }
                if(t[tmp]<=a){
                    t[tmp]=-1;
                    pokonani++;
                }
            }
            tmp=0;

            if(t[i]<=c && t[i]>a+b){    //c ab
                t[i]=-1;
                pokonani++;
                godziny++;
                i--;

                bool a_did=false, b_did=false;
                while(t[tmp]==-1 && tmp<n){
                    tmp++;
                }
                if(t[tmp]<=a && t[tmp]!=-1){
                    t[tmp]=-1;
                    pokonani++;
                    a_did=true;
                }
                while(t[tmp]<=b && tmp<n){
                    tmp++;
                }
                while(t[tmp]>b && tmp>0){
                    tmp--;
                }
                if(t[tmp]!=-1){
                    t[tmp]=-1;
                    pokonani++;
                }
                tmp=0;
                if(!a_did && !b_did){
                    while(t[tmp]<=a+b && tmp<n){
                        tmp++;
                    }
                    while(t[tmp]>a+b || t[tmp]==-1 && tmp>=0){
                        tmp--;
                    }
                    if(t[tmp]!=-1){
                        t[tmp]=-1;
                        pokonani++;
                    }
                }
                
            }
            tmp=0;
        }
    }

    cout<<godziny;
    return 0;
}