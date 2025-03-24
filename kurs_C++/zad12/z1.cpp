#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <vector>
#include <functional>

using namespace std;

// zad1
class z1
{
private:
    int num;
    double sum;
    double avg;
public:
    z1() : num(0), sum(0), avg(0) {};
    void operator() (double elem)
    {
        num++;
        sum += elem;
        avg = sum / num;
        cout << "sum: " << sum << ", avarage: " << avg <<", num of elem: " << num << endl;
    }
};

int main()
{
    cout << "przyklady zad1" << endl;
    set<int> e1 = {1, 2, 3, 4, 5};
    z1 a = for_each(e1.begin(), e1.end(), z1());
    cout << endl;
    list<float> e2 = {1.01, 2.02, 3.03};
    a = for_each(e2.begin(), e2.end(), z1());
    cout << endl;
    vector<double> e3 = {1.1, 0, 1.1};
    a = for_each(e3.begin(), e3.end(), z1());
    cout << endl;
    
    return 0;
}