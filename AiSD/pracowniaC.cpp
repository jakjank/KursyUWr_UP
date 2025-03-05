#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // F - waga wszystkich
    // C - ilosc dost. monet
    int F,C,a,b;
    cin>>F>>C;
    int val[C];
    int weight[C];
    for(int i=0;i<C;i++){
        cin>>a>>b;
        val[i]=a;
        weight[i]=b;
    }
    int mini[F+1];
    int maxi[F+1];

    for(int i=0;i<=F;i++){
        mini[i] = INT32_MAX;
        maxi[i] = -1;
    }

    mini[0] = 0;
    maxi[0] = 0;
    //min max
    for(int i=1;i<=F;i++){
        for(int j=0; j<C; j++){
            // if(i == weight[j]){
            //     if(maxi[i] < val[j]){
            //         maxi[i] = val[j];
            //     }
            // }
            if(i >= weight[j] and maxi[i-weight[j]]!=-1){
                if(maxi[i] < val[j] + maxi[i-weight[j]]){
                    maxi[i] = val[j] + maxi[i-weight[j]];
                }
            }
        }
    }
    //jest rozw lub nie
    if(maxi[F] != -1){
        for(int i=1;i<=F;i++){
            for(int j=0; j<C; j++){
                // if(i == weight[j]){
                //     if(mini[i] > val[j]){
                //         mini[i] = val[j];
                //     }
                // }
                if(i >= weight[j] and mini[i-weight[j]] != INT32_MAX){
                    if(mini[i] > val[j] + mini[i-weight[j]]){
                        mini[i] = val[j] + mini[i-weight[j]];
                    }
                }
            }
        }

        // odzyskiwanie monet
        int monety_max[C] = {0};
        int monety_min[C] = {0};
        int akt = F;
        while(akt > 0){
            for(int i=0; i<C; i++){
                if(maxi[akt] == maxi[akt-weight[i]] + val[i]){
                    monety_max[i]++;
                    akt = akt - weight[i];
                    break;
                }
            }
        }
        akt = F;
        while(akt > 0){
            for(int i=0; i<C; i++){
                if(mini[akt] == mini[akt-weight[i]] + val[i]){
                    monety_min[i]++;
                    akt = akt - weight[i];
                    break;
                }
            }
        }
        
        cout<<"TAK"<<'\n';
        cout<<mini[F]<<'\n';
        for(int i=0; i<C;i++){
            cout<<monety_min[i]<<" ";
        }
        cout<<'\n';
        cout<<maxi[F]<<'\n';
        for(int i=0; i<C;i++){
            cout<<monety_max[i]<<" ";
        }
        return 0;
    }
    cout<<"NIE";
    return 0;
}