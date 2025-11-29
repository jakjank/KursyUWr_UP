#include <iostream>
#include <string>
#include <map>
#include <vector>

std::map<char,int> make_new_map(std::map<char,int>& new_m, std::map<char,int>& m, char c)
{   
    for(auto [k,v] : m)
    {
        new_m[k] = v;
        if(k == c)
            new_m[k]--;
    }
    return new_m;
}

void perm_helper(std::map<char,int> letters, std::vector<std::string> perms)
{
    int sum = 0;
    for (const auto& [key, value] : letters){
        // std::cout<<key<<":"<<value<<'\n';
        sum += value;
    }
    // std::cout<<sum<<'\n';

    if(sum > 0){
        std::vector<std::string> new_perms{};
        for (auto& [key, value] : letters){
            if(value > 0){
                for(auto x : perms){
                    new_perms.push_back(x + key);
                }
                std::map<char,int> new_letters{};
                new_letters = make_new_map(new_letters, letters, key);
                // std::cout << "taking off: " << key << "\n";
                perm_helper(new_letters, new_perms);
                new_perms = {};
            }
        }
    }
    else{
        for(auto& s : perms)
            std::cout << s << '\n';
    }
}

void permutations(std::string s)
{
    std::map<char,int> letters;

    for(auto& c : s)
    {
        if(letters.find(c) != letters.end())
            letters[c]++;
        else
            letters[c]=1;
    }
    std::vector<std::string> tmp{""};
    perm_helper(letters, tmp);
}

int main()
{
    std::string data{"aabb"};

    permutations(data);
}