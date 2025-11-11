#include <functional>
#include <iostream>

// czemu globalnie jest zle?
// const std::function<int(int, int)> binomial = 
// [&binomial](int n, int k)
// {
//     return binomial(n-1, k) + binomial(n-1,k-1);
// };


int main()
{
    const std::function<int(int, int)> binomial = [&binomial](int n, int k)
    {
        if( n == 0 || k == 0 || k == n) return 1;
        // if( n < 0 || k < 0) return 0;
        return binomial(n-1, k) + binomial(n-1,k-1);
    };

    std::vector<std::pair<int,int>> examples{{3,3}, {4,2}, {5,5}, {7,3}, {-1,-5}};

    for(auto& el : examples)
    {
        std::cout << el.first << " po " << el.second << " = " 
                  << binomial(el.first, el.second) << "\n";
    }

    return 0;
}