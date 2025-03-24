#include <iostream>
using namespace std;

int main(){
    int t,n,m;
    cin>>t;

    int dd[4][2] = {{1,1},{-1,1},{1,-1},{-1,-1}};
    int akt=0;
    int maxi=0;

    for(int i=0;i<t;i++)
    {
        cin>>n>>m;
        int a[n][m];
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                cin>>a[j][k];
            }
        }

        
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++){
                akt = a[j][k];
                for(int d=0;d<4;d++){
                    int j2 = j + dd[d][0];
                    int k2 = k + dd[d][1];
                    while(j2>=0 && j2<n && k2>=0 && k2<m){
                        // cout <<"j2: "<<j2<<" k2: "<<k2<<"   "<<dd[d][0]<<" "<<dd[d][0]<<endl;
                        akt += a[j2][k2];
                        j2 += dd[d][0];
                        k2 += dd[d][1];
                    }
                }
                if(akt > maxi){
                    maxi = akt;
                }
            }
        }
        cout<<maxi<<endl;
        maxi = 0;
    }
    return 0;
}