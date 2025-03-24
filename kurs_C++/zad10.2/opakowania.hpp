#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class safe_input
{
    ifstream file;
public:
    safe_input(const string& file_name);
    ~safe_input();

    template<typename T>
    T read()
    {
        T data;
        if (!file.read(reinterpret_cast<char*>(&data), sizeof(data)))
        {
           throw runtime_error("Failed to read data from file.");
        }
        return data;
    }

    bool eof();
};

class safe_output
{
    ofstream file;
public:
    safe_output(const string& file_name);
    ~safe_output();

    template<typename T>
    void write(T data)
    {
        file.write(reinterpret_cast<char*>(&data), sizeof(data));
        file.flush();
    }
};