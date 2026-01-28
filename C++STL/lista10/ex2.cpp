#include <iostream>
#include <iomanip>
#include <locale>
#include <ctime>
#include <vector>

void print_in_locale(const std::string& loc_name)
{
    try {
        std::locale loc(loc_name.c_str());
        std::wcout.imbue(loc);

        int i1 = 1234567;
        int i2 = -987654;
        double d1 = 12345.6789;
        double d2 = -0.00123;

        std::wcout << "Liczby:\n";
        std::wcout << "  int:    " << i1 << ", " << i2 << "\n";
        std::wcout << "  double: " << d1 << ", " << d2 << "\n";

        long double money1 = 1234.56;
        long double money2 = 9876543.21;

        std::wcout << "Pieniądze:\n";
        // Problem z 'zł'
        auto& x =std::use_facet<std::money_put<wchar_t>>(loc);
        x.put({std::wcout}, false, std::wcout, std::wcout.fill(), money1*100);
        
        // (money1 * 100) << "\n";
        std::wcout << "  " << std::showbase << std::put_money(money2 * 100) << "\n";

        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::wcout << "Data i godzina:\n";
        // std::wcout << "  " << std::put_time(&tm, "%c") << "\n";
        wchar_t buf[100];
        std::wcsftime(buf, sizeof(buf)/sizeof(wchar_t), L"%c", &tm);
        std::wcout << L"  " << buf << L"\n";

        std::wcout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Nie można ustawić lokalizacji: " << loc_name << "\n";
    }
}

int main()
{
    std::vector<std::string> locales = {
        "en_US.UTF-8",
        "de_DE.UTF-8",
        "fr_FR.UTF-8",
        "pl_PL.UTF-8"
    };

    for (const auto& loc : locales) {
        print_in_locale(loc);
    }

    return 0;
}
