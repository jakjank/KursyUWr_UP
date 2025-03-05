#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    long long wart, poprz, nast;
    Node *lewy;
    Node *prawy;

    Node(){
        wart = LONG_LONG_MIN;
        lewy = NULL;
        prawy = NULL;
    }

    void insert(long long x){
        if(wart == LONG_LONG_MIN){
            wart = x;
            return;
        }
        if(x>wart){
            if(lewy != NULL){
                lewy->insert(x);
            }
            else{
                lewy = new Node();
                lewy->insert(x);
            }
        }
        if(x<wart){
            if(prawy != NULL){
                prawy->insert(x);
            }
            else{
                prawy = new Node();
                prawy->insert(x);
            }
        }
        return;
    }

    bool del(long long x){
        if(lewy == NULL and prawy == NULL){
            
        }

    }
    void wypisz(int x){
        if(this != NULL){
            cout<<wart<<"-"<<x<<" ";
            this->lewy->wypisz(x*3);;
            this->prawy->wypisz(x*2);
        }
    }
};

int main(){
    Node *root = new Node();

    int n;
    long long val;
    char type;
    cin>>n;
    while(n--){
        cin>>type;
        cin>>val;
        if(type == 'I'){
            root->insert(val);
        }
        if(type == 'D'){
            
        }
        if(type == 'U'){
            
        }
        if(type == 'L'){
            
        }
    }
    root->wypisz(1);
    return 0;
}