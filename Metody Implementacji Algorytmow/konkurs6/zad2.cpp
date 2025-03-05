#include <bits/stdc++.h>
using namespace std;

int main(){
    set<long long> tprimes;
    long long limit = 1000000000000;
    long long x = 3;
    for(long long i=1; i<limit; i=i+x){
        if(has_3_dividers(i)){
            tprimes.insert(i);
        }
    }
}