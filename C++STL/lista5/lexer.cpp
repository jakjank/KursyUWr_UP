#include <forward_list>
#include <set>
#include <string>
#include <iostream>
#include <span>

namespace lex {

class Lexer
{
    std::string m_source;

    inline static const std::set<char> interpunctionSymbols { ',', ';', ':' };
    inline static const std::set<char> brackets { '[', ']', '{', '}', '(', ')' };
    inline static const std::set<char> operators { '+', '-', '*', '/' };
    inline static const std::set<char> realations { '>', '<', '=', '!' };

    bool isWhitespace(const char c) { return c == ' '; }
    bool isDigit(const char c) { return c >= '0' && c <= '9'; }
    bool isLetter(const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    bool isInterpunction(const char c) { return interpunctionSymbols.count(c) > 0; }
    bool isBracket(const char c) { return brackets.count(c) > 0; }
    bool isOperator(const char c) { return operators.count(c) > 0; }
    bool isRelation(const char c) { return realations.count(c) > 0; }

public:
    Lexer(std::string source) : m_source(source) {}

    std::forward_list<std::span<const char>> tokenize()
    {
        std::forward_list<std::span<const char>>  spans;
        auto insertPos = spans.before_begin();

        size_t pos = 0;
        const char* base = m_source.data();

        while (pos < m_source.size())
        {
            char c = m_source[pos];

            if (isWhitespace(c)) {
                ++pos;
                continue;
            }

            const char* start = base + pos;
            size_t length = 0;

            if (isDigit(c))
            {
                bool hasDot = false;
                while (pos < m_source.size()) {
                    char cur = m_source[pos];
                    if (isDigit(cur)) { ++pos; }
                    else if (cur == '.' && !hasDot) { hasDot = true; ++pos; }
                    else break;
                }
                length = (base + pos) - start;
            }
            else if (isLetter(c))
            {
                while (pos < m_source.size() && (isLetter(m_source[pos]) || isDigit(m_source[pos])))
                    ++pos;
                length = (base + pos) - start;
            }
            else if (isRelation(c))
            {
                ++pos;
                if (pos < m_source.size() && (c == '!' || c == '=' || c == '<' || c == '>') && m_source[pos] == '=')
                    ++pos;
                length = (base + pos) - start;
            }
            else if (isOperator(c) || isBracket(c) || isInterpunction(c))
            {
                ++pos;
                length = 1;
            }
            else
            {
                ++pos;
                continue;
            }

            insertPos = spans.insert_after(insertPos, std::span<const char>(start, length));
        }

        return spans;
    }
};

void print(const std::forward_list<std::span<const char>>& v)
{
    for (const auto& sp : v)
    {
        std::cout << "[" << std::string_view(sp.data(), sp.size()) << "] ";
    }
    std::cout << std::endl;
}

} //end namespace lex