#include <iostream>
#include <ratio>


using h1  = std::ratio<1,1>;
using h2  = std::ratio_add<h1,  std::ratio<1,2>>;
using h3  = std::ratio_add<h2,  std::ratio<1,3>>;
using h4  = std::ratio_add<h3,  std::ratio<1,4>>;
using h5  = std::ratio_add<h4,  std::ratio<1,5>>;
using h6  = std::ratio_add<h5,  std::ratio<1,6>>;
using h7  = std::ratio_add<h6,  std::ratio<1,7>>;
using h8  = std::ratio_add<h7,  std::ratio<1,8>>;
using h9  = std::ratio_add<h8,  std::ratio<1,9>>;
using h10 = std::ratio_add<h9,  std::ratio<1,10>>;
using h11 = std::ratio_add<h10, std::ratio<1,11>>;
using h12 = std::ratio_add<h11, std::ratio<1,12>>;
using h13 = std::ratio_add<h12, std::ratio<1,13>>;
using h14 = std::ratio_add<h13, std::ratio<1,14>>;
using h15 = std::ratio_add<h14, std::ratio<1,15>>;
using h16 = std::ratio_add<h15, std::ratio<1,16>>;
using h17 = std::ratio_add<h16, std::ratio<1,17>>;
using h18 = std::ratio_add<h17, std::ratio<1,18>>;
using h19 = std::ratio_add<h18, std::ratio<1,19>>;
using h20 = std::ratio_add<h19, std::ratio<1,20>>;
using h21 = std::ratio_add<h20, std::ratio<1,21>>;
using h22 = std::ratio_add<h21, std::ratio<1,22>>;
using h23 = std::ratio_add<h22, std::ratio<1,23>>;
using h24 = std::ratio_add<h23, std::ratio<1,24>>;
using h25 = std::ratio_add<h24, std::ratio<1,25>>;
using h26 = std::ratio_add<h25, std::ratio<1,26>>;
using h27 = std::ratio_add<h26, std::ratio<1,27>>;
using h28 = std::ratio_add<h27, std::ratio<1,28>>;
using h29 = std::ratio_add<h28, std::ratio<1,29>>;
using h30 = std::ratio_add<h29, std::ratio<1,30>>;
using h31 = std::ratio_add<h30, std::ratio<1,31>>;
using h32 = std::ratio_add<h31, std::ratio<1,32>>;
using h33 = std::ratio_add<h32, std::ratio<1,33>>;
using h34 = std::ratio_add<h33, std::ratio<1,34>>;
using h35 = std::ratio_add<h34, std::ratio<1,35>>;
using h36 = std::ratio_add<h35, std::ratio<1,36>>;
using h37 = std::ratio_add<h36, std::ratio<1,37>>;
using h38 = std::ratio_add<h37, std::ratio<1,38>>;
using h39 = std::ratio_add<h38, std::ratio<1,39>>;
using h40 = std::ratio_add<h39, std::ratio<1,40>>;
using h41 = std::ratio_add<h40, std::ratio<1,41>>;
using h42 = std::ratio_add<h41, std::ratio<1,42>>;
using h43 = std::ratio_add<h42, std::ratio<1,43>>;
using h44 = std::ratio_add<h43, std::ratio<1,44>>;
using h45 = std::ratio_add<h44, std::ratio<1,45>>;
using h46 = std::ratio_add<h45, std::ratio<1,46>>;
// using h47 = std::ratio_add<h46, std::ratio<1,47>>;


int main()
{
    std::cout << h1::num  << " / " << h1::den  << "\n";
    std::cout << h2::num  << " / " << h2::den  << "\n";
    std::cout << h3::num  << " / " << h3::den  << "\n";
    std::cout << h4::num  << " / " << h4::den  << "\n";
    std::cout << h5::num  << " / " << h5::den  << "\n";
    std::cout << h6::num  << " / " << h6::den  << "\n";
    std::cout << h7::num  << " / " << h7::den  << "\n";
    std::cout << h8::num  << " / " << h8::den  << "\n";
    std::cout << h9::num  << " / " << h9::den  << "\n";
    std::cout << h10::num << " / " << h10::den << "\n";
    std::cout << h11::num << " / " << h11::den << "\n";
    std::cout << h12::num << " / " << h12::den << "\n";
    std::cout << h13::num << " / " << h13::den << "\n";
    std::cout << h14::num << " / " << h14::den << "\n";
    std::cout << h15::num << " / " << h15::den << "\n";

    std::cout << h25::num << " / " << h25::den << "\n";

    std::cout << h35::num << " / " << h35::den << "\n";

    std::cout << h45::num << " / " << h45::den << "\n";

    return 0;
}
