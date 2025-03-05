#include <iostream>

using namespace std;

int main(){
    int n,a,b;
    int w=0;
    cin>>n>>a>>b;

    string seats;
    cin>>seats;

    for(int i=0;i<seats.length();i++){
        
        if(a>b && a>0){
            while(seats[i]!='*'){
                w++;
                a--;
                i++;
                if(seats[i]=='.' && b>0){
                    w++;
                    b--;
                    i++;
                }
            }
        }
        else{
            while(seats[i]!='*' && b>0){
                w++;
                b--;
                i++;
                if(seats[i]=='.' && a>0){
                    w++;
                    a--;
                    i++;
                }
            }
        }
        
    }
    cout<<w;
    return 0;
}