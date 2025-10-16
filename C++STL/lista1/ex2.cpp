#include <iostream>
#include <set>


using MySet = std::set<std::string>;

int main()
{
    MySet set{"a", "ab", "ala ma kota"};

    for(auto& s : set)
    {
        std::cout << s << "\n";
    }
    
    return 0;
}