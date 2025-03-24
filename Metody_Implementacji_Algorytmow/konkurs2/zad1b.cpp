#include <iostream>

using namespace std;

int main(){
    int n,a,b;
    int w=0;
    cin>>n>>a>>b;

    string seats;
    cin>>seats;

    for(int i=0;i<n;i++){
        if(seats[i]=='.'){
            if(i==0){
                if(a>b && a>0){
                    seats[i] = 'a';
                    a--;
                    w++;
                }
                else{
                    if(b>0){
                        seats[i] = 'b';
                        b--;
                        w++;
                    }
                }
            }
            else{
                if(seats[i-1] == 'a' && b>0){
                    seats[i]='b';
                    b--;
                    w++;
                }
                if(seats[i-1] == 'b' && a>0){
                    seats[i]='a';
                    a--;
                    w++;
                }
                if(seats[i-1] == '*'){
                    if(a>b and a>0){
                        seats[i]='a';
                        a--;
                        w++;
                    }
                    else{
                        if(b>0){
                            seats[i]='b';
                            b--;
                            w++;
                        }
                    }
                }
                if(seats[i-1]=='.'){
                    if(a>0){
                        seats[i]='a';
                        a--;
                        w++;
                    }
                    if(b>0){
                        seats[i]='b';
                        b--;
                        w++;
                    }
                }
            }
        }
    }
    //cout<<seats<<endl;
    cout<<w;
    return 0;
}