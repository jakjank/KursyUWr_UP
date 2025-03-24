/*
Program implementuje klasę Gramatyka, która ma reprezentować 
klasyczne gramatyki bezkontekstowe (niestey dość ubogo z 
racji możliwości tworzenia praktycznie wyłącznie losowych słów w danej
gramatyce). 
Niestety implementacja wymusza, aby to użytkownik zadeklarował daną
gramatykę. Zatem nierealne na tym poziomie mojego opanowania języka C#
było stworzenie jakichkolwiek testów w Main.

tworzenie gramatyki powinno wyglądać mniej więcej tak:

Podaj nieterminale (aby zakończyć wpisz STOP):
A
B
S
STOP
Podaj zbior produkcji do każdego nieterminala
(aby zakończyć dodawanie wpisz STOP):
Podaj produkcje do A:
Bab
Aab
STOP
Podaj produkcje do B:
bbb
STOP
Podaj produkcje do S:
Ss
A
STOP
Okresl ktory nieterminal ma byc symbolem startowym:
S
*/

// będziemy trzymać się notacji, że terminale są  pisane małymi literami,
// a nieterminale wielkimi literami
class Gramatyka
{
    string? symbol_startowy;
    List<string> nieterminale = new List<string>();
    // string[] terimnale;   terminale będziemy definiowć pośrednio poprzez produkcję
    // do każedgo nieteminala będziemy mieli jego zbiór produkcji
    Dictionary<string,List<string>> produkcje = new Dictionary<string, List<string>>();

    public Gramatyka(){
        string? s;

        Console.WriteLine("TWORZENIE GRAMATYKI");
        // wpisujemy terminale i od razu dodajemy je jako klucze do produkcji
        Console.WriteLine("Podaj nieterminale (aby zakończyć wpisz STOP):");
        do
        {
            s = Console.ReadLine();
            if(s != "STOP" && s is not null)
            {
                nieterminale.Add(s);
                produkcje.Add(s, new List<string>());
            }
        }while(s != "STOP");
        
        // do każdeg nieterminala definiujemy jego zbiór produkcji
        Console.WriteLine("Podaj zbior produkcji do każdego nieterminala");
        Console.WriteLine("(aby zakończyć dodawanie wpisz STOP):");
        foreach(string nieterm in nieterminale)
        {
            Console.WriteLine("Podaj produkcje do {0}: ", nieterm);
            do
            {
                s = Console.ReadLine();
                if(s != "STOP" && s is not null)
                {
                    produkcje[nieterm].Add(s);
                }
            }while(s != "STOP");
        }

        // określamy od którego nieterminala będziemy zaczynać tworzenie zdań/słów
        Console.WriteLine("Okresl ktory nieterminal ma byc symbolem startowym: ");
        symbol_startowy = Console.ReadLine();
    }

    // funkcja biorąca napis, nieterminal i produkcę którą chcemy do 
    // niego zastosować. Zwraca napisa po wykonaniu danej produkcji
    // na pierwszym napotkanym terminalu danego typu
    public string rozwin(string s, string nieterminal, string produkcja)
    {
        // sprawdzamy czy dany terminal i produkcja występują w danym języku
        // jeśli nie - zwracamy dany napis bez zmian
        if(nieterminale.Contains(nieterminal))
        {
            if(produkcje[nieterminal].Contains(produkcja)){}
            else
            {
                return s;
            }
        }
        else
        {
            return s;
        }

        string nowy_s = "";
        bool byla_zamiana = false;
        // sprawdzamy znaki w wejściowym napisie, jeśli to nie szukany nieterminal,
        // to dodajemy go do nowy_s wpp. stosujemy produkcję i dodajemy do nowy_s
        foreach(char znak in s)
        {
            if(znak.ToString() != nieterminal )
            {
                nowy_s = nowy_s + znak;
            }
            else
            {
                if(!byla_zamiana)
                {
                    nowy_s = nowy_s + produkcja;
                    byla_zamiana = true;
                    // była zamiana, aby tylko raz zastosować produkcję
                }
                else
                {
                    nowy_s = nowy_s + znak;
                }
            }
        }
        return nowy_s;
    }

    public string losowe_slowo()
    {   
        if(symbol_startowy is null)
        {
            return "brak symbolu startowego";
        }
        string losowe_s = symbol_startowy;

        for(int i = 0; i < losowe_s.Length; i++)
        {
            if(nieterminale.Contains(losowe_s[i].ToString()))
            {   
                // losujemy produkcję do danego nieterminala i wywołujemy rozwin() 
                var random = new Random();
                int indeks = random.Next(produkcje[losowe_s[i].ToString()].Count);
                string losowa_produkcja = produkcje[losowe_s[i].ToString()][indeks];
                losowe_s = this.rozwin(losowe_s, losowe_s[i].ToString(), losowa_produkcja);
                i = -1;
            }
        }
        return losowe_s;
    }
}


class Test
{
    static void Main()
    {
        Gramatyka gm = new Gramatyka();
        Console.WriteLine(gm.losowe_slowo());
    }
}