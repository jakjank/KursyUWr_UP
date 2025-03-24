#pragma once
#include <stack>
#include <queue>
#include <map>
#include <iostream>


using namespace std;

namespace calc
{
    class Symbol
    {
    public:
        Symbol();
        ~Symbol();
        virtual void push(queue<Symbol*>& symbols) = 0;
        virtual void evaluate() = 0;
        static stack<double> stack;
    };
}