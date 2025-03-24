#include "interface.hpp"

using namespace calc;
using namespace std;

string f_names[] = {"+", "-", "*", "/", "^", "%",
                    "min", "max", "log", "print",
                    "set", "to", "clear", "exit",
                    "abs", "sgn", "floor","ceil",
                    "frac","sin", "cos",  "atan",
                    "acot", "ln", "exp"};

void save_symbol(string s, queue<Symbol*>& symbols)
{
    for(string f_name : f_names)
    {
        if(f_name == s)
        {
            symbols.push(new Function(s));
            return;
        }
    }
    if(s == "pi" || s == "fi" || s == "e")
    {
        symbols.push(new Constant(s));
        return;
    }
    
    try
    {
        double x = stod(s);
        symbols.push(new Number(x));
        return;
    }
    catch(...)
    {
        try
        {
            symbols.push(new Variable(s));
        }
        catch(...)
        {
            clog << "unknown symbol: " << s;
        }
    }
    
}

double do_print(string s)
{   
    queue<Symbol*> symbols;
    istringstream ss(s);
    string sym;

    while(ss >> s)
    {
        save_symbol(s, symbols);
    }

    while(symbols.size() > 0)
    {
        Symbol* current;
        current = symbols.front();
        symbols.pop();
        try
        {
            current->evaluate();
        }
        catch(invalid_argument e)
        {
            throw e;
        }
    }
    
    if(Variable::stack.size() == 1)
    {   
        double result = Symbol::stack.top();
        Symbol::stack.pop();
        return result;
    }
    else
    {
        while(!Variable::stack.empty())
        {
            Variable::stack.pop();
        }
        throw invalid_argument("incorrect RPN");
    }
}

void do_set(string s)
{
    string val_s = "";
    double val;
    string name;
    istringstream ss(s);
    string bin;
    ss >> bin; // - set
    ss >> name;
    cout << name << endl;
    ss >> bin; // - to
    while(ss >> bin)
    {
        val_s = val_s + bin + " ";
    }
    try
    {
        val = do_print(val_s);
    }
    catch(...)
    {
        throw invalid_argument("couldn't set " + name + " to " + val_s);
    }
    set_var(name, val);
    cout << name << " is set to '" << val_s << "' (" << val << ")" << endl;
}

void do_clear()
{
    Variable x("x");
    x.clear_var();
    cout << "all variables have been deleted" << endl;
}

int recognize_command(string command)
{
    istringstream ss(command);
    string word, to;
    ss >> word;
    
    if(word == "print") return 1;
    if(word == "set")
    {
        ss >> to;
        ss >> to;
        if(to == "to")
        {
            return 2;
        }
    }
    if(word == "clear") return 3;
    if(word == "exit") return 4;
    throw invalid_argument("unknown command: '" + command + "'");
}

void start()
{
    string command;
    int which_command;
    cout<<"Hello, write a command"<<endl;
    getline(cin, command);

    while(command != "exit")
    {
        try
        {
            which_command = recognize_command(command);

            if(which_command == 1)
            {
                cout << do_print(command.substr(6, command.length() - 5)); 
                cout << endl;
            }
            if(which_command == 2)
            {
                do_set(command);
            }
            if(which_command == 3)
            {
                do_clear();
            }
        }
        catch(invalid_argument e)
        {
            clog << e.what() << endl;
        }
        getline(cin, command);
    }
    cout<<"Goodbye!" <<endl;
}