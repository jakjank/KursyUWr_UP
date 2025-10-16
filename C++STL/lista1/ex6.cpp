#include <iostream>
#include <string>

int main() {
    int d, m, y;

    std::cout << "DD:MM:RRRR: ";
    std::cin >> d >> m >> y;

    std::string monthName;
    switch (int x = m; x) {
        case 1:
            monthName = "stycznia";
            break;
        case 2:
            monthName = "lutego";
            break;
        case 3:
            monthName = "marca";
            break;
        case 4:
            monthName = "kwietnia";
            break;
        case 5:
            monthName = "maja";
            break;
        case 6:
            monthName = "czerwca";
            break;
        case 7:
            monthName = "lipca";
            break;
        case 8:
            monthName = "sierpnia";
            break;
        case 9:
            monthName = "września";
            break;
        case 10:
            monthName = "października";
            break;
        case 11:
            monthName = "listopada";
            break;
        case 12:
            monthName = "grudnia";
            break;
        default:
            monthName = "...";
            break;
    }

    std::cout << d << " " << monthName << " " << y << std::endl;

    return 0;
}
