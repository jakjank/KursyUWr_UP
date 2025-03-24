#include <bits/stdc++.h>
#include <vector>
#include <stdexcept>
using namespace std;

string transform(int number){
    const vector<pair<int, string>> rome = {
        {1000 , "M"} , {900 , "CM"} , {500 , "D"} , {400 , "CD"} , {100 , "C"} , {90 , "XC"} ,
        {50 , "L"} , {40 , "XL"} , {10 , "X"} , {9 , "IX"} , {5 , "V"} , {4 , "IV"} , {1 , "I"}
    };
    string roman = "";

    while(number > 0){
        int i = 0;
        while(number < rome[i].first){
            i++;
        }
        number = number - rome[i].first;
        roman = roman +rome[i].second;
    }
    return roman;
}

string ArabicToRoman(string arabic){
    size_t pos{};
    int number;

    try {
        number = stoi(arabic , &pos);

        if(arabic.length() != pos){
            throw invalid_argument("");
        }  

        if(number <= 0 || number >= 4000){
            throw out_of_range("");
        }
    }
    catch(invalid_argument){
        clog << "Zly argument: " << arabic << endl;
        return "";
    }
    catch(out_of_range){
        clog << "Argument spoza zakresu: " << arabic << endl;
        return "";
    }
    catch(...){
        clog << "Nieznany blad" << endl;
        return "";
    }

    return transform(number);
}

int main(int argc , const char* argv[]){
    for(int i = 1; i < argc; i++){
        string wynik = ArabicToRoman( argv[i] );
        if(wynik != "")
            cout << wynik << endl;
    }
    return 0;
}