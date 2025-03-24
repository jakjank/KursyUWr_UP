#include "wektor.hpp"
using namespace std;

wektor::wektor(double a, double b){
    wx = a;
    wy = b;
}

double wektor::wsp_x(){
    return wx;
}

double wektor::wsp_y(){
    return wy;
}