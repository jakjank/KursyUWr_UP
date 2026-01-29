#include <iostream>

template<int N, long long A, long long B>
struct lucas_impl {
    static constexpr long long value =
        lucas_impl<N - 1, B, A + B>::value;
};

template<long long A, long long B>
struct lucas_impl<0, A, B> {
    static constexpr long long value = A;
};


template<int N>
struct lucas {
    static constexpr long long value =
        lucas_impl<N, 2, 1>::value;
};

int main() {
    std::cout << lucas<10>::value << "\n"; // 123
}