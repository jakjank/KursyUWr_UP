#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

std::vector<int> v{1, 2, 3,
                   3, 4, 5,
                   5, 5, 6,       
                   7, 7, 7,
                   7, 8, 9};

auto bin_search(std::vector<int>& v, int val)
{
    auto i = v.begin();
    std::vector<int>::iterator l;
    std::vector<int>::iterator r;
    bool l_got = false;

    while(i != v.end())
    {
        auto o = val <=> *i;
        if(o < 0) // val smaller than ith  el
        {
            if(l_got) return std::make_pair(l,r);
            return std::make_pair(v.end(),v.end());
        }
        else if(o == 0) // val equal ith
        {
            if(l_got)
            {
                r = i;
                i++;
            }
            else
            {
                l = i;
                l_got = true;
            }
        }
        else // val bigger than ith el
        {
            i++;
        }
    } 
    
    if(l_got) return std::make_pair(l,i--);
    return std::make_pair(v.end(),v.end());
}

int main()
{
    auto [l,r] = bin_search(v, 5);

    std::cout << std::distance(v.begin(),l) << " - " << std::distance(v.begin(), r) << "\n";
    return 0;
}