#include <bits/stdc++.h>

using namespace std;

int main(){
    long long n;
    cin>>n;                  // n!/(n-5)!5!
    long long w=1;

    w = (n*(n-1)*(n-2)*(n-3)*(n-4));
    w = w/(long long)(5*4*3*2*1);
    w = w * (n*(n-1)*(n-2)*(n-3)*(n-4));

    cout<<w;
    return 0;
}