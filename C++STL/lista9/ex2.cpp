#include <string>
#include <iostream>
#include <vector>
#include <iterator>
// #include <numeric>
#include <fstream>

bool rel_prime(int a, int b)
{
    // return std::gcd(a, b) == 1;
    if(a > b)
    {
        auto tmp = a;
        a = b;
        b = tmp;
    }
    for(int i=2; i<=a; i++)
    {
        if(a % i == 0)
        {
            if(b % i == 0)
                return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    if(argc==1){
        return 1;
    }

    int k = std::stoi(argv[1]);
    // std::cout << k;
    std::vector<int> phis;

    for(int i=1; i<=k; i++)
    {
        int phi=0;
        for(int j=1; j<=i;j++)
        {
            if(rel_prime(i,j))
                phi++;
        }
        phis.emplace_back(phi);
    }

    std::ofstream file("phi.txt");
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku phi.txt\n";
        return 1;
    }

    std::copy(phis.begin(), phis.end(),
              std::ostream_iterator<int>(file, "; "));

    return 0;
}