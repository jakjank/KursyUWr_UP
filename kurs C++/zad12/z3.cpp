#include <random>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

template <int mini, int maxi>
auto generuj = []() {
    return ((rand() % (maxi - mini)) + mini);
};

auto czy_pierwsza = [](int number) {
    if (number < 2)
        return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
};

int main()
{
    srand(time(NULL));

    int t[10];
    array<int, 10> a;
    vector<int> v(10);

    generate(begin(t), end(t), generuj<1,10>);
    generate(a.begin(), a.end(), generuj<50, 100>);
    generate(v.begin(), v.end(), generuj<1,100>);

    for_each(begin(t), end(t), [](int x){cout << x << " ";});
    cout << endl;
    for_each(a.begin(), a.end(), [](int x){cout << x << " ";});
    cout << endl;
    for_each(v.begin(), v.end(), [](int x){cout << x << " ";});
    cout << endl;
    
    // cos w tym stylu?
    // vector<int> t_p(0);
    // vector<int> a_p(0);
    // vector<int> v_p(0);

    // copy_if(begin(t), end(t), t_p, czy_pierwsza);
    // copy_if(a.begin(), a.end(), a_p, czy_pierwsza);
    // copy_if(v.begin(), v.end(), v_p, czy_pierwsza);

    // for_each(begin(t_p), end(t_p), [](int x){cout << x << " ";});
    // cout << endl;
    // for_each(a_p.begin(), a_p.end(), [](int x){cout << x << " ";});
    // cout << endl;
    // for_each(v_p.begin(), v_p.end(), [](int x){cout << x << " ";});
    // cout << endl;

    return 0;
}