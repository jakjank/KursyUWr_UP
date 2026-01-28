#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>

int main()
{
    std::locale loc("pl_PL.UTF-8");
    // why both?
    std::locale::global(loc);
    std::wcout.imbue(loc);

    std::vector<std::wstring> names = {
        L"żubr",
        L"zając",
        L"źrebak",
        L"ąkacja",
        L"ananas",
        L"ćma",
        L"cyprys",
        L"łabędź",
        L"lew",
        L"świerk",
        L"szczur",
        L"żmija",
        L"żółw"
    };

    const std::collate<wchar_t>& coll =
        std::use_facet<std::collate<wchar_t>>(loc);

    std::sort(names.begin(), names.end(),
        [&](const std::wstring& a, const std::wstring& b) {
            return coll.compare(
                a.data(), a.data() + a.size(),
                b.data(), b.data() + b.size()
            ) < 0;
        });

    for (const auto& s : names) {
        std::wcout << s << '\n';

        // auto old_flags = std::wcout.flags();

        // std::wcout.imbue(std::locale::classic());
        // std::wcout << " " << coll.hash(s.data(), s.data() + s.size()) << "\n";

        // std::wcout.flags(old_flags);
        // std::wcout.imbue(loc);
    }

    return 0;
}
