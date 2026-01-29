#include <iostream>

template<int A, int B>
struct NWD {
    enum{
        val = NWD<B, A%B>::val
    };
};

template<int A>
struct NWD<A, 0> {
    enum {
        val = A
    };
};

int main() {
    std::cout << NWD<48, 18>::val << "\n"; // 6
    std::cout << NWD<7, 3>::val << "\n"; // 1
    std::cout << NWD<18, 48>::val << "\n"; // 6
}