#include <cstdint>
#include <iostream>
#include <string>

enum class Name : uint16_t {
    Kuba,
    Kasia,
    Krzys
};

void fun(std::string s, Name name)
{
    switch(name)
    {
        case Name::Kuba:
            std::cout << "Kuba: " << s << "\n";
            break;
        case Name::Kasia:
            std::cout << "Kasia: " << s << "\n";
            break;
        case Name::Krzys:
            std::cout << "Krzyś: " << s << "\n";
            break;
    }
}


int main() {
    fun("z podlasia", Name::Kasia);

    return 0;
}