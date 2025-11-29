#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include <algorithm>

using string = std::string;

struct Point
{
    Point(double x, double y, int R, int G, int B, string name)
        : m_x(x), m_y(y), m_r(R), m_g(G), m_b(B), m_name(name) {}

    friend std::ostream& operator<<(std::ostream& os, Point p)
    {
        os << "[" << p.m_name << ", (" << p.m_x << ", " << p.m_y << "), {" << p.m_r << ", " << p.m_g <<", " << p.m_b << "}]";
        return os;  
    }
    
    double m_x, m_y;
    unsigned int m_r, m_g, m_b;
    string m_name;
};

template<typename  T>
void print(string header, T& container)
{   
    std::cout << header << "\n";
    using elemType = typename T::value_type;
    std::for_each(container.begin(), container.end(), [](elemType& p){std::cout<<p<<"\n";});
    std::cout << "\n";
}

double lum(Point& a)
{
    return a.m_r*0.3 + a.m_g*0.59 + a.m_b*0.11;
}

int main()
{
    std::list<Point> points =
    {
        {  5.3,   7.8, 210,  40,  90, "Aquila" },
        { 12.1,  14.6,  80, 200,  10, "Orion" },
        {  3.2,   9.4, 120,  80, 255, "Lyra" },
        { 18.7,   6.3, 255, 160,  30, "Vega" },
        {  9.9,   2.1, 200,  90, 150, "Nova" },
        { 22.0,  11.2, 180,  60, 220, "Atlas" },
        { -4.8,   8.7, 240, 200,  60, "Hera" },
        { -9.1,  16.3, 130,  0,  40, "Echo" },
        { -2.4,  13.1,  60, 210, 170, "Draco" },
        { -7.6,   4.5, 0,  70, 80, "Raven" },
        { -1.2,  19.8,  50, 180,  60, "Mira" },
        { -3.9,  -2.4, 200, 220,  30, "Aster" },
        { -10.7, -7.3, 150,  80,  70, "Zephyr" },
        { -6.5, -14.9,  80,  65, 220, "Nimbus" },
        { -14.0, -9.1, 230, 120,  20, "Solara" },
        { -2.3, -20.4,  40, 180, 180, "Quartz" },
        { -11.8, -3.6, 255,  40,  40, "Crimson" },
        {  7.4,  -5.2, 100, 130,  20, "Borealis" },
        { 15.3, -11.6,  90,  10, 200, "Cassia" },
        {  4.2, -18.1, 210,  60,  40, "Tempest" },
        { 21.8,  -9.9,  50, 240, 100, "EchoX" },
        {  2.0,  -3.3, 140,  50, 200, "OrionX" },
        { 13.6,   4.9,  90,  90, 255, "Zenith" }
    };

    print("At the begining:", points);

    auto toRemove = std::remove_if(points.begin(),
        points.end(),
        [](Point& p){return p.m_name.length() > 5; });
    points.erase(toRemove, points.end());
    print("after deleting long names:" ,points);

    auto q1 = std::count_if(points.begin(), points.end(),
                        [](const Point& p){ return p.m_x > 0 && p.m_y > 0; });

    auto q2 = std::count_if(points.begin(), points.end(),
                            [](const Point& p){ return p.m_x < 0 && p.m_y > 0; });

    auto q3 = std::count_if(points.begin(), points.end(),
                            [](const Point& p){ return p.m_x < 0 && p.m_y < 0; });

    auto q4 = std::count_if(points.begin(), points.end(),
                            [](const Point& p){ return p.m_x > 0 && p.m_y < 0; });

    std::cout << "There are this many poitns in q1, q2, q3, q4 accordingly " << q1 <<", "<<q2<<", "<<q3<<", "<<q4<<"\n";

    points.sort([](Point& a, Point& b){return lum(a) > lum(b);});
    print("\nSoreted by brightness:" ,points);

    auto it = std::partition(points.begin(),
        points.end(),
        [](Point& a){return lum(a) < 64;});

    std::list<Point> dark(points.begin(), it);

    std::cout << "There are " << dark.size() << " dark points:";
    print("", dark);


    return 0;
}
