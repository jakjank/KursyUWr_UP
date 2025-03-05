#include <iostream>

using namespace std;

int main(){
    int q,n;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>n;
        int t[n];
        for(int j=0;j<n;j++){
            cin>>t[i];
        }

        int ile=1;
        int tmp;
        for(int j=0;j<n;j++){
            tmp = t[j];
            while(tmp!=j){
                tmp=t[tmp];
                ile++;
            }
            cout<<ile<<" ";
            ile=1;
        }
        cout<<endl;
    }
    return 0;
}