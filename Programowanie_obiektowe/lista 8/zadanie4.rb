class Jawna
    def initialize(nowy_tekst)
        @tekst = nowy_tekst
    end

    def zaszyfruj(klucz)
        zaszyfrowany_tekst = ""
        i = 0
        while i < @tekst.length
            if @tekst[i] == " "
                zaszyfrowany_tekst += " "
            else
                zaszyfrowany_tekst += klucz[@tekst[i]]
            end
            i += 1
        end
        return Zaszyfrowana.new(zaszyfrowany_tekst)
    end

    def wypisz
        puts @tekst
    end
end

class Zaszyfrowana
    def initialize(zaszyfrowany_tekst)
        @tekst = zaszyfrowany_tekst
    end

    def odszyfruj(klucz)
        odszyfrowany_tekst = ""
        i = 0
        while i < @tekst.length
            if @tekst[i] == " "
                odszyfrowany_tekst += " "
            else
                odszyfrowany_tekst += klucz[@tekst[i]]
            end
            i += 1
        end
        return Jawna.new(odszyfrowany_tekst)
    end

    def wypisz
        puts @tekst
    end
end

print "Tekst wejsciowy jawny: "
jawny = Jawna.new("send jest super")
jawny.wypisz()

print "Tekst zaszyfrowany: "
szyfr = jawny.zaszyfruj({"s" => "a",
                        "e" => "b",
                        "n" => "c",
                        "d" => "d",
                        "j" => "e",
                        "t" => "f",
                        "u" => "g",
                        "p" => "h",
                        "r" => "i"})
szyfr.wypisz()

print "Tekst odszyfrowany: "
jawny = szyfr.odszyfruj({"a" => "s",
                        "b" => "e",
                        "c" => "n",
                        "d" => "d",
                        "e" => "j",
                        "f" => "t",
                        "g" => "u",
                        "h" => "p",
                        "i" => "r"})
jawny.wypisz()
