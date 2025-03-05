#include <bits/stdc++.h>

using namespace std;

int wart(int l, int s, int f[]){
    int c = 1, res = 0;
    for(int i=l;i<s;i++){
        res += c*f[i];
        c++;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int K, L;
    cin>>K>>L;
    int f[L];

    for(int i=0; i<L; i++){
        cin>>f[i];
    }
    // t[i,j] = koszt fi, fi+1, ... , fL
    int t[L+1][K+1];

    for(int i=0; i<=L; i++){
        t[i][0] = INT16_MAX;
    }
    for(int i=0; i<=K; i++){
        t[L][i] = 0;
    }
    int koszty[L+1][K+1];
    
    for(int k=1;k<=K;k++){
        for(int l=L-1;l>=0;l--){
            //t[l][k] = min mniejszy sufiks o jeden mniejszy podzial
            int min = INT16_MAX, tmp;
            for(int s=l+1; s<=L; s++){
                tmp = t[s][k-1] + wart(l,s,f);
                if(tmp < min){
                    koszty[l][k] = wart(l,s,f);
                    min = tmp;
                }
            }
            t[l][k] = min;
        }   
    }
    // cout<<endl;
    // for(int i=-1; i<=L; i++){
    //     if(i==-1) cout<<"\\     ";
    //     for(int j=-1; j<=K; j++){
    //         if(i==-1 and j!=-1){
    //             cout<<j<<" ";
    //         }
    //         if(i!=-1 and j!=-1){
    //             cout<<t[i][j]<<"~"<<koszty[i][j]<<" ";
    //         }
    //         if(j==-1 and i!=-1){
    //             cout<<i<<" ";
    //         }
    //     }
    //     cout<<endl;
    // }

    cout<<t[0][K]<<'\n';

    // odzyskac sciezke
    int kolumna=K-1, indeks=0, poprz_indeks=0, poprz_koszt=koszty[0][K], poprz_t=t[0][K];
    int sciezka[K];
    while(indeks<=L){
        if(t[indeks][kolumna] == poprz_t-poprz_koszt){
            sciezka[kolumna] = indeks-poprz_indeks;
            poprz_koszt = koszty[indeks][kolumna];
            poprz_t = t[indeks][kolumna];
            kolumna--;
            poprz_indeks = indeks;
        }
        else{
            indeks++;
        }
    }

    for(int i=K-1;i>=0;i--){
        cout<<sciezka[i]<<" ";
    }

    


    return 0;
}