// zwiekszamy od konca
// sprawdzamy czy i-1 lub i-2 nie sa takie same jak i-ta sprawdzana
// jak zmeinimy jakas to musimy uzupelnic tyl do najmniejszego mozliwego 

#include <iostream>
using namespace std;

int main(){
    string s;
    int n,p;
    int where=-1;

    cin>>n>>p>>s;

    for(int i=n-1; i>=0; i--){
        while(s[i]-'a'+1 < p){
            s[i]=s[i]+1;
            //cout<<s<<endl;
            if(s[i]!=s[i-1] && s[i]!=s[i-2]){
                where = i;
                i=-1;
                break;
            }
        }
    }
    
    if(where == -1){
        cout<<"NO";
    }
    else{
        for(int i=where+1;i<n;i++){
            char x='a';
            while(x==s[i-1] or x==s[i-2]){
                x++;
            }
            s[i] = x;
        }
        cout<<s;
    }
    return 0;
}