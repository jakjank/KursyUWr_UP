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

    int godziny=0,pokonani=0,i=n-1,ja=0,jb=0,jc=0;
    while(t[ja]<=a){
        ja++;
    }
    ja--;
    while(t[jb]<=jb){
        jb++;
    }
    jb--;
    while(t[jc]<=jc){
        jc++;
    }
    jc--;


    if(t[i]> a+b+c){
        cout<<-1;
        return 0;
    }
    while(pokonani < n){
        if(t[i]>b+c){            //a+b+c
            godziny++;
            pokonani++;
            t[i]=-1;
            i--;
        }

        if(t[i]>c && t[i]<=b+c && t[i]>a+c){ //b+c
            while(t[ja]==-1 && ja>-1){
                ja--;
            }
            if(t[ja]>-1){
                pokonani++;
                t[ja]=-1;
                if(ja>0) ja--;
            }

            t[i]=-1;
            pokonani++;
            i--;
            godziny++;         
        } 
        
        if(t[i]>c && t[i]<=a+c && t[i]>a+b){ //a+c
            while(t[jb]==-1 && jb>-1){
                jb--;
            }
            if(t[jb]>-1){
                t[jb]=-1;
                pokonani++;
                if(jb>0) jb--;
            }

            t[i]=-1;
            pokonani++;
            i--;
            godziny++;
        }
        
        if(t[i]>c && t[i]<=a+b){  //a+b
            while(t[jc]==-1 && jc>-1){
                jc--;
            }
            if(t[jc]>-1){
                t[jc]=-1;
                pokonani++;
                if(jc>0) jc--;
            }
            t[i]=-1;
            i--;
            pokonani++;
            godziny++;
        }

        if(t[i]>a+b && t[i]<=c){             //c
            bool a_did=false, b_did=false;
            while(t[ja]==-1 && ja>-1){
                ja--;
            }
            if(t[ja]>-1){
                t[ja]=-1;
                pokonani++;
                a_did = true;
                if(ja>0) ja--;
            }

            while(t[jb]==-1 && jb>-1){
                jb--;
            }
            if(t[jb]>-1){
                t[jb]=-1;
                pokonani++;
                b_did = true;
                if(jb>0) jb--;
            }

            if(!a_did && !b_did){
                int tmp=0;
                while(t[tmp]<=a+b && tmp<n){
                    tmp++;
                }
                tmp--;
                if(t[tmp]>-1){
                    pokonani++;
                    t[tmp]=-1;
                }
            }
            t[i]=-1;
            pokonani++;
            i--;
            godziny++;      
        }
    }
    cout<<godziny;
    return 0;
}