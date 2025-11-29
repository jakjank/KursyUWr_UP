#include <list>
#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

template <typename container>
auto get_max_occurences(const container& c)
{
    using T = typename container::value_type;

    std::map<T, int> counter;

    for(auto& el : c)
    {
        if(counter.find(el) != counter.end())
        {
            counter[el]++;
        }
        else
        {
            counter[el] = 1;
        }
    }

    std::vector<std::pair<T, int>> result;

    auto max_it = std::max_element(counter.begin(), counter.end(),
        [](const auto& a, const auto& b){ return a.second < b.second; });

    if (max_it != counter.end()) {
        int max_value = max_it->second;

        for (const auto& [k, v] : counter) {
            if (v == max_value)
                result.push_back(std::make_pair(k, v));
        }
    }

    return result;
}

int main()
{
    std::vector<int> data{1, 1, 3, 5, 8, 9, 5, 8, 8, 5};
    auto r = get_max_occurences(data);
    for(auto& [k,v] : r)
    {
        std::cout<<k<<":"<<v<<'\n';
    }

    std::cout<<'\n';

    std::list<std::string> data2{ "b","c","d","b","e","f","e", "a","a"};
    auto r2 = get_max_occurences(data2);
    for(auto& [k,v] : r2)
    {
        std::cout<<k<<":"<<v<<'\n';
    }


    return 0;
}