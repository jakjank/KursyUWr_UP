#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <deque>
#include <algorithm>
#include <math.h>

using string = std::string;

struct Pearson
{
    Pearson(string name, string surname, int age, int weight, double height) :
        m_name(name), m_surname(surname), m_age(age), m_weight(weight), m_height(height) {}

    friend std::ostream& operator<<(std::ostream& os, Pearson& p)
    {
        os << "[" << p.m_name << ", " << p.m_surname << ", " << p.m_age << ", " << p.m_weight <<", " << p.m_height <<"]";
        return os;
    }

    string m_name;
    string m_surname;
    int m_age;
    int m_weight;
    double m_height;
};

std::deque<Pearson> ppl{
    {"Jan","Kowalski",44,88,1.81},
    {"Anna","Nowak",32,62,1.70},
    {"Piotr","Wiśniewski",51,92,1.79},
    {"Katarzyna","Wójcik",27,58,1.68},
    {"Michał","Krawczyk",35,123,1.83},
    {"Agnieszka","Dąbrowska",41,70,1.72},
    {"Tomasz","Mazur",29,85,1.90},
    {"Magdalena","Zielińska",24,155,1.66},
    {"Robert","Kaczmarek",47,95,1.68},
    {"Ewa","Szymańska",38,160,1.69},
    {"Paweł","Woźniak",33,78,1.82},
    {"Julia","Wróbel",22,52,1.64},
};

void print(string header)
{   
    std::cout << header << "\n";
    std::for_each(ppl.begin(), ppl.end(), [](Pearson& p){std::cout<<p<<"\n";});
    std::cout << "\n";
}

int main()
{
    print("We start with:");

    std::sort(ppl.begin(),
    ppl.end(),
    [](Pearson& p1, Pearson& p2)
        {
            double bmi1 = p1.m_weight / (p1.m_height * p1.m_height);
            double bmi2 = p2.m_weight / (p2.m_height * p2.m_height);
            return bmi1 > bmi2;
        });
    
    print("Sorted by BMI:");

    std::for_each(ppl.begin(),
        ppl.end(),
        [](Pearson& p){ p.m_weight -= 0.1 * p.m_weight; });
    
    print("After some sport:");

    auto it = std::partition(
        ppl.begin(),
        ppl.end(),
        [](const Pearson& p){ return p.m_weight > 100; }
    );

    auto heavy_begin = ppl.begin();
    auto heavy_end = it;

    auto light_begin = it;
    auto light_end = ppl.end();

    std::cout << "osoby ciezkie (>100kg):\n";
    for(auto it = heavy_begin; it != heavy_end; ++it)
        std::cout << *it << "\n";

    std::cout << "\nosoby lekkie (<=100kg):\n";
    for(auto it = light_begin; it != light_end; ++it)
        std::cout << *it << "\n";

    std::cout << "\nnajstarsza osoba:\n";
    std::cout << *std::max_element(ppl.begin(),
        ppl.end(),
        [](Pearson& p1, Pearson p2){ return p1.m_age < p2.m_age; });

    std::cout << "\nnajmlodsza osoba:\n";
    std::cout << *std::min_element(ppl.begin(),
        ppl.end(),
        [](Pearson& p1, Pearson p2){ return p1.m_age < p2.m_age; });
    std::cout << "\n";
}