#include <iostream>
template<typename T>
using func_ptr = void(*)(T&);



template<typename T, typename F>
class po_kolei
{
    T f1;
    F f2;

public:
    po_kolei(T f1, F f2) : f1(f1), f2(f2) {} 

    //wykonywanie 2 funkcji a nie ich zlozenie!
    template<typename X>
    void operator()(X x)
    {
        f1(x);
        f2(x);
    }
};

int main()
{
    auto print = [](int x){ std::cout << "x: " << x << "\n"; };
    auto plus1 = [](int x){ std::cout << "x+1: " << x+1 << "\n"; };
    auto plus2 = [](int x){ std::cout << "x+2: " << x+2 << "\n"; };

    auto f12 = po_kolei(print, plus1);
    auto f123 = po_kolei(f12, plus2);

    f123(7);
}