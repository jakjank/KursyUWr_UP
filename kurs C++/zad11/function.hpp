#pragma once
#include "symbol.hpp"

namespace calc
{
    class Function : public Symbol
    {
        enum kind_of_f
        {
            f_add = 0,
            f_sub = 1,
            f_mul = 2,
            f_div = 3,
            f_modulo = 4,
            f_min = 5,
            f_max = 6,
            f_log = 7,
            f_pow = 8,
            f_abs = 9,
            f_sgn = 10,
            f_floor = 11,
            f_ceil = 12,
            f_frac = 13,
            f_sin = 14,
            f_cos = 15,
            f_atan = 16,
            f_acot = 17,
            f_ln = 18,
            f_exp = 19
        };
        static map<string,kind_of_f> map_of_f;
        kind_of_f name;
    public:
        Function(string s);
        ~Function();
        void push(queue<Symbol*>& symbols);
        void evaluate() override;

    };
}