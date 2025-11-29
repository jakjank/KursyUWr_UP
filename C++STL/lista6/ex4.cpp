#include <fstream>
#include <iterator>
#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    std::ifstream file(filename);
    
    std::istream_iterator<char> it_cin {file};
    std::istream_iterator<char> end_cin;
    
    std::map<char, int> occurrences;
    for (char c = 'a'; c <= 'z'; ++c)
        occurrences[c] = 0;

    while (it_cin != end_cin) {
        if(*it_cin >= 'a' && *it_cin <= 'z')
            occurrences[*it_cin]++;
        else if(*it_cin >= 'A' && *it_cin <= 'Z')
            occurrences[(*it_cin - 'A' + 'a')]++;
        it_cin++;
    }

    int sum = 0;
    for (const auto& [key, value] : occurrences)
        sum += value;

    // i suppose no letteroccures more than 20% so each row is 1%
    for(int row=20; row>0; row--) 
    {
        auto it = occurrences.begin();
        // *1000 and *10+5 is for rounding up
        while(it != occurrences.end())
            std::cout << ((it++->second*1000/sum >= row*10+5) ? 'X' : ' ');
        std::cout<<'\n';
    }

    auto it = occurrences.begin();
    while(it != occurrences.end())
        std::cout << it++->first;
    std::cout<<'\n';

    return 0;
}