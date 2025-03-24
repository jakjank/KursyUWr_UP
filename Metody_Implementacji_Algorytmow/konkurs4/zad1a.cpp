#include <iostream>

using namespace std;

int main(){
    int q,n,tmp;
    int ile =1;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>n;
        int t[n];
        for(int j=0;j<n;j++){
            cin>>t[j];
        }

        for(int j=0;j<n;j++){
            tmp = t[j];
            //cout<<"tmp start: "<<tmp<<endl;
            while(tmp!=j+1){
                tmp=t[tmp-1];
                ile++;
                //cout<<tmp<<" ";
            }
            cout<<ile<<" ";
            ile=1;
        }
        cout<<endl;
    }
    return 0;
}