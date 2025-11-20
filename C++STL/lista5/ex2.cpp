#include <deque>
#include <forward_list>
#include <map>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include "lexer.cpp"

using namespace lex;

enum class symbol_type {
    val,
    oper,
    constant,
    var,
    lparen,
    rparen
};


std::map<std::string, double> constants{
    {"e", 2.71},
    {"pi", 3.41}
};

std::unordered_map<std::string, double> variables{
    {"x", 5.0},
    {"y", 7.99}
};

std::deque<std::string> operators{"+", "-", "*", "/", "^"};

std::map<std::string, int> priority{{"+",1}, {"-",1}, {"*",2}, {"/",2}, {"^",3}};

struct Symbol{

    Symbol(const std::string s)
    {   
        if(s[0] == '('){
            m_type = symbol_type::lparen;
            m_prior = 5;
        }

        if(s[0] == ')'){
            m_type = symbol_type::rparen;
            m_prior = 5;
        }

        if (s[0] >= '0' && s[0] <= '9'){
            m_type = symbol_type::val;
            m_val = std::stod(s);
            m_prior = 0;
        }

        auto o = std::find(operators.begin(),operators.end(), s);
        if(o != operators.end()){
            m_type = symbol_type::oper;
            m_val = std::nullopt;
            m_name = *o;
            m_prior = priority.at(*o);
            return;
        }

        auto c = constants.find(s);
        if(c != constants.end()){
            m_type = symbol_type::constant;
            m_val = c->second;
            m_name = c->first;
            m_prior = 0;
            return;
        }

        auto v = variables.find(s);
        if(v != variables.end()){
            m_type = symbol_type::var;
            m_val = v->second;
            m_name = v->first;
            m_prior = 0;
        }
    }

    symbol_type m_type;
    std::optional<double> m_val;
    std::optional<std::string> m_name;
    int m_prior;
};

std::forward_list<Symbol> get_symbols(std::forward_list<std::span<const char>> raw)
{
    std::forward_list<Symbol> symbols;
    auto it = symbols.before_begin();
    for(auto el : raw)
    {
        std::string token(el.data(), el.size());
        it = symbols.insert_after(it, Symbol(token));
    }
    return symbols;
}

void print_symbols(const std::forward_list<Symbol>& lst)
{
    for (const auto& s : lst) {
        if (s.m_type == symbol_type::val)
            std::cout << s.m_val.value() << " ";
        else if (s.m_name.has_value())
            std::cout << s.m_name.value() << " ";
    }
    std::cout << "\n";
}

std::forward_list<Symbol> shunting_yard(std::forward_list<Symbol> infi)
{
    std::forward_list<Symbol> output;
    auto out_it = output.before_begin();

    std::stack<Symbol> S;

    for(auto& sym : infi)
    {
        switch (sym.m_type) {
            case symbol_type::val : 
                out_it = output.insert_after(out_it, sym);
                break;
            case symbol_type::constant : 
                out_it = output.insert_after(out_it, sym);
                break;
            case symbol_type::var : 
                out_it = output.insert_after(out_it, sym);
                break;

            case symbol_type::oper:
                while (!S.empty() &&
                       (S.top().m_type == symbol_type::oper &&
                        S.top().m_prior >= sym.m_prior))
                {
                    out_it = output.insert_after(out_it, S.top());
                    S.pop();
                }
                S.push(sym);
                break;
            
            case symbol_type::lparen:
                S.push(sym);
                break;

            case symbol_type::rparen:
                while (!S.empty() && S.top().m_type != symbol_type::lparen) {
                    out_it = output.insert_after(out_it, S.top());
                    S.pop();
                }
                if (!S.empty() && S.top().m_type == symbol_type::lparen)
                    S.pop();
                break;
        }
    }
    
    while (!S.empty()) {
        out_it = output.insert_after(out_it, S.top());
        S.pop();
    }

    return output;
}

int main()
{
    // std::string infiks = "((2+7)/3+(14-3)*4)/2";
    std::string infiks = "2 + 3 / 4";

    Lexer lexer(infiks);
    auto raw = lexer.tokenize();
    std::cout << "INFIX TOKENS:\n";
    print(raw);

    std::cout << "POSTFIX SYMBOLS:\n";
    print_symbols(shunting_yard(get_symbols(raw)));
    return 0;
}