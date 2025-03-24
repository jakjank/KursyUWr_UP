#include "opakowania.hpp"

using namespace std;

safe_input::safe_input(const string& file_name)
{
    file.exceptions(ifstream::badbit | ifstream::failbit);

    file.open(file_name , ios::binary);
    
    if(!file.good())
    {
        throw invalid_argument("file failed to open: " + file_name);
    }
}

safe_input::~safe_input()
{
    if (file.is_open())
    {
        file.close();
    }
}

bool safe_input::eof()
{
    return file.eof();
}

safe_output::safe_output(const string& file_name)
{
    file.exceptions(ofstream::badbit | ofstream::failbit);

    file.open(file_name , ios::binary);
    
    if(!file.good())
    {
        throw invalid_argument("file failed to open: " + file_name);
    }
}

safe_output::~safe_output()
{
    if (file.is_open())
    {
        file.close();
    }
}

