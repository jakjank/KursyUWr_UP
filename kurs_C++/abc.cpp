#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Car{
    string name;

    public:
    Car(string name){
        this->name = name;
    }
    string get_name(){
        return name;
    }
    void set_name(string name){
        *this = Car(name);
    }
};

void passArray(int* tab){
    cout<<tab<<"\n";
    for(int i=0;i<sizeof(int[3])/sizeof(tab[0]);i++){
        cout<<tab[i]<<" ";
        tab[i]++;
    }
}

int main(){
    /*cout << 2+2 << "\n" << "this is abc" << endl;
    cout << round(1.2) << " " << round(1.5) << " " << sqrt(123) << " " << log(M_E) << " " << pow(2,3) << endl;
    int a = 100;
    bool b = false;
    cout << a << " " << b << endl;
    string c = "to jest abc";
    cout << c << endl;
    for(char x : c){
        cout << x << " ";
        x = 'x';
    }
    cout << endl;

    Car cars[3] = {Car("BMW"), Car("audi"), Car("mercedes")};

    for(Car &car: cars){
        cout << car.get_name() << "->";
        car.set_name("x");
        cout << car.get_name() << " " << &car << " ";
    }
    cout << cars[0].get_name();
    cout << endl;

    vector<Car> cars2;
    cars2.push_back(Car("mazda"));
    cars2.push_back(Car("toyota"));
    cars2.push_back(Car("subaru"));
    for(Car &car : cars2){
        cout << car.get_name() << " ";
    }
    cout << endl;
    
    for(vector<Car>::iterator it=cars2.begin(); it != cars2.end(); it++){
        cout << it->get_name() << " ";
        // it->set_name("x");
    }
    cout << endl;
    // cars2.pop_back();
    // for(vector<Car>::iterator it=cars2.begin(); it != cars2.end(); it++){
    //     cout << it->get_name() << " ";
    // }

    reverse(cars2.begin(), cars2.end());

    // cout<<sizeof(cars2)<<"\\"<<sizeof(cars2[0])<<endl;
    for(int i=0; i<cars2.size(); i++){
        cout<<cars2.at(i).get_name()<<" ";
    }
    cout<<endl;
    
    swap(cars2[0],cars2[1]);
    for(int i=0; i<cars2.size(); i++){
        cout<<cars2.at(i).get_name()<<" ";
    }
    cout<<endl;

    cars2.push_back(Car("mercedes"));
    for(int i=0; i<cars2.size(); i++){
        cout<<cars2.at(i).get_name()<<" ";
    }
    cout<<endl;
    swap_ranges(cars2.begin(), cars2.begin()+1, cars2.begin()+2);
    for(int i=0; i<cars2.size(); i++){
        cout<<cars2.at(i).get_name()<<" ";
    }
    cout<<endl;

    int x = 7;
    int *y = &x;
    cout<<x<<" "<<y<<" "<<&x<<" "<<*y<<endl;
    *y = 3;
    cout<<x;
    x = 2;
    cout<<" "<<*y<<endl;
    */
    int a = 7;
    int* ptr = &a;
    cout<<&a<<" "<<ptr<<" "<<*ptr<<'\n';
    int& ref = a;
    cout<<&ref<<" "<<ref<<'\n';

    int arr[3] = {1,2,3};
    passArray(arr);
    for(int i=0;i<sizeof(int[3])/sizeof(arr[0]);i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}