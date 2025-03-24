#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    string mins;
    bool przez10;
    bool przez3;
    int suma;

    for(int i=0;i<n;i++){
        cin>>mins;
        przez10=false;
        przez3=false;
        suma=0;
        for(int j=0; j<mins.length();j++){
            if(mins[j]-'0' == 0) przez10 = true;
            suma = suma+mins[j]-'0';
        }
        if(suma%3 == 0) przez3 = true;

        if(przez10 and przez3){
            cout<<"red"<<endl;
        }
        else{
            cout<<"cyan"<<endl;
        }
    }


}