#include <complex>
#include <math.h>
#include <numbers>
#include <iostream>

using namespace std;

const double E_M =  0.5772156649;

complex<double> gamma(complex<double> z, uint iterations)
{   
    using c = complex<double>;
    c res = 1;
    for (int i = 1; i <= iterations; i++)
    {
        res *= pow(numbers::e, z/c(i,0)) / (c(1,0) + z/c(i,0));
    }
    return (pow(numbers::e, -z*E_M) / z) * res;
}

complex<double> inv_gamma(complex<double> z, uint iterations)
{   
    using c = complex<double>;
    c res = 1;
    for (int i = 1; i <= iterations; i++)
    {
        res *= (c(1,0) + z/c(i,0)) / pow(numbers::e, z/c(i,0));
    }
    return z * pow(numbers::e, z*E_M) * res;
}

int main()
{
    int iter = 1;

    while( iter < 11)
    {
        cout << iter << " : " << gamma(complex<double>(2,3), iter) << "\n";
        iter++;
    }

    iter = 1;
    cout << '\n';
    while( iter < 11)
    {
        cout << iter << " : " << inv_gamma(complex<double>(2,3), iter) << "\n";
        iter++;
    }

    return 0;
}