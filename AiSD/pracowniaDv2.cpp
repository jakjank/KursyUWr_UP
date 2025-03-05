#include <bits/stdc++.h>

using namespace std;
// ZMIENIONE INT NA LONG LONG I SIE POPSULO
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
    long long t[L+1][K+1];

    for(int i=0; i<=L; i++){
        t[i][0] = INT16_MAX;
    }
    for(int i=0; i<=K; i++){
        t[L][i] = 0;
    }
    long long koszty[L+1][K+1];
    long long A[L+1], B[L+1];
    //A[i] = fi+fi+1+ ... + fL
    //B[i] = fi+2fi+1+ .. (n-i+1)fL
    A[L] = 0;
    B[L] = 0;
    for(int i=L-1; i>=0; i--){
        A[i] = f[i] + A[i+1];
        B[i] = A[i] + B[i+1];
    }

    // for(int i=0; i<=L;i++){
    //     cout<<A[i]<<" ";
    // }
    // cout<<endl;
    //  for(int i=0; i<=L;i++){
    //     cout<<B[i]<<" ";
    // }
    // cout<<endl;

    for(int k=1;k<=K;k++){
        for(int l=L-1;l>=0;l--){
            long long min = INT16_MAX, tmp;
            for(int s=l+1; s<=L; s++){
                // t[i,j] = min (i<s) T[s,j-1] + S[i,s-1]
                // t[l,k] = min (l<s) T[s,k-1] + S[l,s-1]
                // S[l,s-1] = B[l]-B[s] - (s-l)*A[s]
                tmp = t[s][k-1] + (B[l] - B[s] - (s-l)*A[s]);
                if(tmp < min){
                    koszty[l][k] = B[l] - B[s] - (s-l)*A[s];
                    min = tmp;
                }
            }
            t[l][k] = min;
        }   
    }

    cout<<t[0][K]<<'\n';

    // int kolumna=K-1, indeks=0, poprz_indeks=0;
    // long long poprz_koszt=koszty[0][K], poprz_t=t[0][K];
    int sciezka[K];
    // while(indeks<=L){
    //     if(t[indeks][kolumna] == poprz_t-poprz_koszt){
    //         sciezka[kolumna] = indeks-poprz_indeks;
    //         poprz_koszt = koszty[indeks][kolumna];
    //         poprz_t = t[indeks][kolumna];
    //         kolumna--;
    //         poprz_indeks = indeks;
    //     }
    //     else{
    //         indeks++;
    //     }
    // }

    // for(int i=K-1;i>=0;i--){
    //     cout<<sciezka[i]<<" ";
    // }

    // cout<<"\n druga siciezka"<<endl;

    int i=0;
    int poprz_koszt=koszty[0][K], poprz_t=t[0][K], poprz_indeks=0;
    for(int kolumna2=K-1;kolumna2>=0;kolumna2--){
        i = L;
        while(t[i][kolumna2] != poprz_t-poprz_koszt){
            i--;
        }
        sciezka[kolumna2] = i-poprz_indeks;
        poprz_koszt = koszty[i][kolumna2];
        poprz_t = t[i][kolumna2];
        poprz_indeks = i;
    }

    for(int j=K-1;j>=0;j--){
        cout<<sciezka[j]<<" ";
    }

    return 0;
}