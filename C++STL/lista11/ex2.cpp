#include <iostream>

template<int N, int K, int I>
struct binom_impl {
    static constexpr long long value =
        binom_impl<N, K, I - 1>::value * (N - K + I) / I;
};

template<int N, int K>
struct binom_impl<N, K, 0> {
    static constexpr long long value = 1;
};

template<int N, int K>
struct binomial {
    static constexpr long long value =
        binom_impl<N, K, K>::value;
};

int main() {
    std::cout << binomial<6, 3>::value << "\n"; // 20
}