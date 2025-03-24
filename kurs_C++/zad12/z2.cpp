#include <iostream>
#include <algorithm>
#include <functional>
#include <complex>

using namespace std;

template<typename T>
struct z2
{
    T a, b;

    z2(T a, T b) : a(a), b(b) {}

    T operator()(const T& x) const
    {
        std::function<T(const T&, const T&)> multiply = std::multiplies<T>();
        std::function<T(const T&, const T&)> add = std::plus<T>();

        return add(multiply(a, x), b);
    }
};

int main()
{
    cout << "przyklady zad2" << endl;
    z2<int> f_int(3, 4);
    z2<double> f_double(2, 1.5);
    z2<float> f_float(0.5, 1);
    z2<complex<double>> f_complex({1, 2}, {3, 4});
    cout << "f_int od 3: " << f_int(3) << endl;
    cout << "f_doube od 1: " << f_double(1) << endl;
    cout << "f_float od 6: " << f_float(6) << endl;
    cout << "f_complex od {1,2}: " << f_complex({1, 2}) << endl;

    return 0;
}