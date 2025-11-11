#include <iostream>

template<typename T>
using func_ptr = void(*)(T&);

//przykład

// void example(int x) { std::cout << x << "\n"; }
// func_ptr<int> example_ptr = &example;
// exampe_ptr(7);

template<typename T>
void transform(T tab[], int n, func_ptr<T> f)
{
    for(int i=0; i<n; i++)
    {
        f(tab[i]);
    }
}

void increment_by_one(int& x)
{
    x++;
}

void append_a(std::string& s)
{
    s=s+"a";
}

int main()
{
    int tab1[] = {1,2,3};

    transform(tab1, 3, increment_by_one);

    for(int i=0; i<3; i++)
    {
        std::cout << tab1[i] << " ";
    }
    std::cout << "\n";

    std::string tab2[] = {"a", "b", "c"};

    transform(tab2, 3, append_a);

    for(int i=0; i<3; i++)
    {
        std::cout << tab2[i] << " ";
    }
    std::cout << "\n";

    return 0;
}