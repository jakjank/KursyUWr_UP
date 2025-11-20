#include "lexer.cpp"

using namespace lex;

int main()
{
    std::string source = 
    R"(
    using string = std::string;

    template <typename T>
    using vector = std::vector<T>;

    enum TokenType
    {
        (NUMBER),
        IDENTIFIER,
        INTERPUNCT,
        BRACKET,
        OPERATOR,
        RELATION
    };
    
    double a <= 7.1;
    )";

    Lexer lxr(source);

    auto result = lxr.tokenize();
    print(result);

    return 0;
}