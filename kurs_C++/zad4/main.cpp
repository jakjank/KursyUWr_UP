//TEN PROJEKT NIE JEST SKONCZONY

#include <iostream>
#include "tabbit.hpp"

using namespace std;

int main()
{
    
    int *tablica;
    tablica = new int[10];
    for(int i = 0 ;i < 10; i++){
        cout<<(long long)tablica<<endl;
        tablica ++;
    }

    return 0;
}
