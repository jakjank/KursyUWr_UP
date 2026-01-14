#include <iostream>
#include <fstream>
#include <string>
#include <utility>


template<typename T>
void serialize(std::ostream& os, const T& value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
void deserialize(std::istream& is, T& value)
{
    is.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void serialize(std::ostream& os, const std::string& str)
{
    std::size_t size = str.size();
    serialize(os, size);
    os.write(str.data(), size);
}

void deserialize(std::istream& is, std::string& str)
{
    std::size_t size;
    deserialize(is, size);

    str.resize(size);
    is.read(str.data(), size);
}

template<typename T>
void serialize_array(std::ostream& os, const T* data, std::size_t size)
{
    serialize(os, size);
    for (std::size_t i = 0; i < size; ++i)
        serialize(os, data[i]);
}

template<typename T>
std::pair<T*, std::size_t> deserialize_array(std::istream& is)
{
    std::size_t size;
    deserialize(is, size);

    T* data = new T[size];
    for (std::size_t i = 0; i < size; ++i)
        deserialize(is, data[i]);

    return { data, size };
}

int main()
{
    {
        std::ofstream ofs("data.bin", std::ios::binary);

        int a = 42;
        double b = 3.14;
        std::string s = "Hello world";

        double arr[] = {1.1, 2.1, 3.1, 4.1, 5.1};

        serialize(ofs, a);
        serialize(ofs, b);
        serialize(ofs, s);
        serialize_array(ofs, arr, 5);
    }

    {
        std::ifstream ifs("data.bin", std::ios::binary);

        int a;
        double b;
        std::string s;

        deserialize(ifs, a);
        deserialize(ifs, b);
        deserialize(ifs, s);

        auto tmp = deserialize_array<double>(ifs);
        double* arr = tmp.first;
        std::size_t size = tmp.second;

        std::cout << a << "\n";
        std::cout << b << "\n";
        std::cout << s << "\n";

        for (std::size_t i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }
}