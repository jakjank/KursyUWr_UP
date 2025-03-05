#include <iostream>
#include <functional>

using namespace std;

int main() {
    // [&] znaczy że przechowujemy wszystkie rzeczy w lambdzie przez referencje
    function<void(int)> collatz = [&](int n) {
        cout << n << " ";

        if (n == 1) {
            return;
        }

        if (n % 2 == 0) {
            collatz(n / 2);
        } else {
            collatz(3 * n + 1);
        }
    };

    int n = 10;
    collatz(n);

    return 0;
}