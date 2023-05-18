#include "list.cpp"

using namespace std;
using namespace calc;

int main()
{
    cout << "worzenie obiektu klasy list za pomoca initializer_list: " << endl;
    list<int> przyklad({1,2,3,4,99});
    cout << "utworzona lista: " << przyklad << endl << endl;

    cout << "wypisanie i sprawdzenie czy nowa lisat int-ow jest pusta: " << endl;
    list<int> a;
    cout << "a: "<< a << endl;
    cout << "czy a pusta? " << a.empty() << endl;
    cout << "liczba elementow w a: " << a.number_of_elements() << endl << endl;

    cout << "po dodaniu kilku elementow: " << endl;
    a.push_front(1);
    a.push_front(0);
    a.push_back(5);
    a.insert(2,0);
    a.insert(3,1);
    a.insert(5,2);
    a.push_back(3);
    a.push_back(7);
    cout << "a: "<< a << endl;
    cout << "czy a pusta? " << a.empty() << endl;
    cout << "liczba elementow w a: " << a.number_of_elements() << endl << endl;
    
    cout << "szukanie i licznie elementow: " << endl;
    cout << "pozycja elementu o wartosci 3: " << a.position_of_value(3) << endl;
    cout << "ilosc elementow o wartosci 5: " << a.count_values(5) << endl;
    cout << "ilosc elementow o wartosci 9: " << a.count_values(9) << endl << endl;
    
    cout << "testownie usuwania: " << endl;
    a.remove(3);
    cout << "usuniecie pozycji 3: " << a << endl;
    a.pop_front();
    cout << "usuniecie poczatku: " << a << endl;
    a.pop_back();
    cout << "usuniecie konca: " << a << endl;
    a.remove_value(3);
    cout << "usuniecie elementu o wartosci 3: " << a << endl;
    a.remove_all_values(5);
    cout << "usuniecie wszystkich el. o wart. 5: " << a << endl << endl;

    cout << "kolejka: " << endl;
    queue<string> b;
    b.push("a");
    b.push("b");
    b.push("c");
    cout << b.pop() << endl;
    cout << b.pop() << endl;
    cout << b.pop() << endl;
    
    cout << "stos: " << endl;
    stack<char> c;
    c.push('x');
    c.push('y');
    c.push('z');
    cout << c.pop() << endl;
    cout << c.pop() << endl;
    cout << c.pop() << endl;
}