#include <iostream>
#include <list>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using string = std::string;

template <typename T> 
class values_in_range
{   
public:
    values_in_range(T left, T right) : m_left(left), m_right(right) {}

    template<typename container>
    void operator() (container c)
    {
        for(auto& el : c)
        {
            if (el > m_left && el < m_right)
                std::cout << el << " ";
        }
        std::cout << "\n";
    }

private:
    T m_left;
    T m_right;
};

// cool stuff
template<typename T>
values_in_range(T, T) -> values_in_range<T>;


class pth_since_kth
{   
public:
    pth_since_kth(int p, int k) : m_p(p), m_k(k) {}

    template<typename container>
    void operator() (container& c)
    {   
        int counter = 0;
        for(auto& el : c)
        {
            counter++;
            if (counter >= m_p && (counter-m_p) % m_k == 0)
                std::cout << el << " ";
        }
        std::cout << "\n";
    }

private:
    int m_p;
    int m_k;
};

// template <typename T>  deduce element types in () instead
struct min_and_max
{
    template<typename container>
    auto operator() (container& c)
    {
        using T = typename container::value_type;
        return std::pair<T,T>(*std::min_element(c.begin(), c.end()),
                              *std::max_element(c.begin(), c.end()));
    }
};

// template <typename T> 
struct my_sum
{
    template<typename container>
    auto operator() (container& c)
    {
        using T = typename container::value_type;
        T sum;
        for(auto el : c)
        {
            sum = sum + el;
        }
        return sum;
    }
};

int main()
{
    std::vector<double> doubles{1.1,2.1,3.1,4.1,5.99};
    std::list<int> ints{5,3,6,8,9,3,4,5};
    std::set<string> strings{"aa", "bb", "cc", "dd", "ad"};

    std::cout << "print values in range\n";
    values_in_range vird(2.3,4.2);
    values_in_range viri(4,8);
    values_in_range virs("bc", "de");
    vird(doubles);
    viri(ints);
    virs(strings);

    std::cout << "\nprint every kth since pth\n";
    pth_since_kth(3,2)(doubles);
    pth_since_kth(3,2)(doubles);
    pth_since_kth(2,2)(doubles);

    std::cout << "\nmin and max vals\n";
    auto mmd = min_and_max()(doubles);
    auto mmi = min_and_max()(ints);
    auto mms = min_and_max()(strings);
    std::cout << mmd.first << " " << mmd.second << "\n";
    std::cout << mmi.first << " " << mmi.second << "\n";
    std::cout << mms.first << " " << mms.second << "\n";

    std::cout << "\nsums\n";
    std::cout << my_sum()(doubles) << "\n";
    std::cout << my_sum()(ints) << "\n";
    std::cout << my_sum()(strings) << "\n";

    return 0;
}