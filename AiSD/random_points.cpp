#include <bits/stdc++.h>
#include <fstream>


using namespace std;

int main(){
    ofstream file;
    file.open("random_points.txt");
    int n = 5;
    for(int i=-n;i<n;i++){
        for(int j=-n;j<n;j++){
            file<<i<<" "<<j<<endl;
        }
    }
    file.close();

    return 0;
}