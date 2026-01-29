#include <iostream>

template<int N, typename T>
struct inner_impl {
    static T eval(const T* x, const T* y) {
        return inner_impl<N - 1, T>::eval(x, y)
             + x[N - 1] * y[N - 1];
    }
};

template<typename T>
struct inner_impl<0, T> {
    static T eval(const T*, const T*) {
        return T{}; // el neutr
    }
};

template<std::size_t N, typename T = double>
T inner(T* x, T* y) {
    return inner_impl<N, T>::eval(x, y);
}

int main() {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    std::cout << inner<3>(a, b) << "\n";
}
