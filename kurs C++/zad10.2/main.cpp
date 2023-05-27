#include <cstdlib>
#include <ctime>
#include "opakowania.hpp"

int main()
{
    // ofstream plik("data.txt");
    // int n = 7;
    // plik.write(reinterpret_cast<char*>(&n), sizeof(n));
    // plik.close();

    // ifstream plik2("data.txt");
    // plik2.read(reinterpret_cast<char*>(&n), sizeof(n));
    // cout << n;
    

    srand(time(NULL));
    cout << "zapisywanie losowych liczb (double)"<<endl;
    safe_output file_o("data.txt");
    for(int i=0; i<10; i++)
    {
        double n = (double)rand()/100;
        cout<<n<<endl;
        file_o.write<double>(n);
    }

    cout << endl;
    cout<<"odczytywanie liczb"<<endl;
    safe_input file_i("data.txt");
    for(int i=0; i<10; i++)
    {
        double x = file_i.read<double>();
        cout << x << endl;
    }

    cout << endl;
    // cout << "zapisywanie losowych liczb (int)"<<endl;
    // safe_output file_o2("data.txt");
    // for(int i=0; i<5; i++)
    // {
    //     int n = (int)rand();
    //     cout<<n<<endl;
    //     file_o2.write<int>(n);
    // }
    // cout << endl;

    // odczytywanie bajt po bajcie
    safe_input file_i2("data.txt");
    for(int i=0; i<40; i++)
    {
        char c = file_i2.read<char>();
        cout << hex << (int)c << endl;
    }
    return 0;
}