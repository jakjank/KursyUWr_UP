#ifndef KOLOR_HPP
#define KOLOR_HPP
#include <iostream>
#include <stdexcept>

class kolor
{
protected:
    unsigned char R, G, B;
public:
    kolor();

    kolor(int r, int g, int b);

    void set_R(int r);
    void set_G(int g);
    void set_B(int b);
    int get_R();
    int get_G();
    int get_B();

    void rozjasnij();
    void pociemnij();
    static kolor srednia(kolor a, kolor b);

    friend std::ostream& operator<<(std::ostream& out, kolor& A);
};

#endif