// pomysł jest taki, że BigNumy będą przechowywać stringi 
// i stworzymy do tego odpowiednie metody odpowiadającą 
// zwykłemu dodawaniu i odejmowaniu 

class BigNum
{
    string wartosc = "";

    // Wymagany jest argument (int) przy deklaracji 
    public BigNum(int dana)
    {
        if(dana < 0)
        {
            dana = dana * (-1);
            wartosc = "-" + wartosc;
        }
        if(dana == 0)
        {
            wartosc = "0";
        }
        while(dana > 0)
        {
            wartosc = dana % 10 + wartosc;
            dana = dana / 10;
        }
    }

    // wypisz po prostu wypisuje na konsoli wartość (string)
    public void wypisz()
    {
        Console.WriteLine(wartosc);
    }

    // metody daj uzywamy tylko do otrzymania wartosci other w dodaj
    public string daj()
    {
        return wartosc;
    }

    string suma(string dluzszy , string krotszy)
    {
        string wynik = "";
        int reszta = 0;
        int suma = 0;
        int cyfra = 0;
        for(int i = 1; i <= krotszy.Length; i++)
        {
            suma = (dluzszy[dluzszy.Length - i] - '0') +
                   (krotszy[krotszy.Length - i] - '0') +
                   reszta;
            cyfra = suma % 10;

            if(suma > 9)
            {
                reszta = 1;
            }
            else
            {
                reszta = 0;
            }
            wynik = (char)(cyfra + '0') + wynik;
        }
        for(int i = krotszy.Length + 1; i <= dluzszy.Length; i++)
        {
            suma = (dluzszy[dluzszy.Length - i] - '0') +
                   reszta;
            cyfra = suma % 10;

            if(suma > 9)
            {
                reszta = 1;
            }
            else
            {
                reszta = 0;
            }
            wynik = (char)(cyfra + '0') + wynik;
        }
        if(reszta == 1)
        {
            wynik = reszta + wynik;
        }
        return wynik;
    }

    bool czy_wieksze(string x , string y)
    {
        int i = 0;
        if(y.Length > x.Length)
        {
            return false;
        }
        if(y.Length == x.Length)
        {
            while(true)
            {
                if(x[i] > y[i])
                {
                    return true;
                }
                if(x[i] < y[i])
                {
                    return false;
                }
                i ++;
                if( i == x.Length)
                {
                    return false;
                }
            }
        return true;
        }
    }

    string 

    string roznica(string od , string co)
    {
        string wynik = "";
        bool czy_minus = false;

        if(czy_wieksze(co , od))
        {
            czy_minus = true;
        }

        for(int i = 0; i < co.Length; i++)
        {
            if(od[od.Length - i- 1] >= co[co.Length - i -1])
            {
                wynik = (char)(od[od.Length - i- 1] - 
                               co[co.Length - i -1] + '0') + 
                        wynik;
            }
            else
            {
                od[]
            }
        }
    }
    
    public string dodaj(BigNum other)
    {
        if(wartosc.Length > other.daj().Length)
        {
            return suma(wartosc , other.daj());
        }
        else
        {
            return suma(other.daj() , wartosc);
        }
    }

    public string odejmij(BigNum other)
    {
        return roznica(wartosc , other.daj());
    }
}

class Tescik
{
    static void Main2()
    {
        BigNum tmp1 = new BigNum(333333333);
        BigNum tmp2 = new BigNum(5555559);
        Console.WriteLine(tmp1.dodaj(tmp2));
        

    }
}
*/