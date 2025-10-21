#include <cstddef>
#include <cstdint>
#include <memory>
#include <iostream>
#include <random>
#include <set>


struct Counter
{
    Counter(uint64_t val = 1)
    {
        m_val = val;
    }

    virtual ~Counter()
    {
        std::cerr << " " << m_val;
    }

    void add(uint64_t x)
    {
        m_val += x;
    }

    uint64_t m_val;
};

void weird_fun(std::unique_ptr<Counter[]> counters, size_t n, int depth, int call=1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n-1);
    std::set<int> seen;

    if(depth > 0)
    {
        while(seen.size() < n / 10)
        {
            int random_index = distrib(gen);
            if(seen.find(random_index) == seen.end())
            {
                seen.insert(random_index);
                counters[random_index].add(call);
            }
        }
        weird_fun(std::move(counters), n, depth-1, call+1);
    }
}

int N = 10;
int M = 40;

int main()
{
    auto counters = std::make_unique<Counter[]>(N);

    weird_fun(std::move(counters), N, M);
    std::cout << "\n";

    return 0;
}