#include <type_traits>
#include <utility>
#include <iostream>

template<typename A, typename B>
void my_move(A from_, B& to_)
{
    if constexpr (std::is_pointer_v<A>)
    {
        using T = std::remove_pointer_t<A>;
        if constexpr (std::is_convertible_v<T, B>)
            to_ = std::move(*from_);
    }
    else
    {
        if constexpr (std::is_convertible_v<A, B>)
            to_ = std::move(from_);
    }
}

int main()
{
    int from1 = 7;
    double to1 = 0; 
    std::cout << "int to double: ";
    my_move(from1,to1);
    std::cout << to1 << std::endl;

    int* from2 = new int;
    *from2 = 7;
    double to2 = 0;
    std::cout << "int* to double: ";
    my_move(from2, to2);
    std::cout << to2 << std::endl;

    std::string from3 = "a";
    int to3 = 0;
    std::cout << "double to int: ";
    my_move(from3, to3);
    std::cout << to3 << std::endl;

    return 0;
}