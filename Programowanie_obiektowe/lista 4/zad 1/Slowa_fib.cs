/*
Program implementuje klasę słowa fibonacciego,
która generuje ilość podach w konstruktorze słów fibonacciego.
Przede wszystkim po elementach tej klasy można iterować za pomocą
pętli foreach.
*/

using System.Collections;

class SlowaFibonacciego : IEnumerable, IEnumerator
{
    // przypisanie wartości początkowych
    string s1 = "b", s2 = "a";
    int ile;
    int pozycja = -1;

    public SlowaFibonacciego(int n)
    {   
        this.ile = n;
    }

    public object Current
    {
        get{
            return s1;
        }
    }

    // tworzenie kolejnych słów Fibonaccciego
    public void dalej()
    {
        string tmp = s2 + s1;
        this.s1 = this.s2;
        this.s2 = tmp;
    }

    public IEnumerator GetEnumerator()
    {
        return (IEnumerator)this;
    }

    public bool MoveNext()
    {   
        // za pierwszym razem nie wykonujemy dalej(), aby
        // nie zgubić pierwszego słowa "b", bo zawsze zwracamy s1
        if(pozycja != -1) this.dalej();
        pozycja++;
        if(pozycja == ile){
            this.Reset();
            return false;
        }
        return true;
    }

    public void Reset()
    {
        s1 = "b";
        s2 = "a";
        pozycja = -1;
    }
}

class KrotkiTest
{
    static void Main()
    {
        SlowaFibonacciego sf = new SlowaFibonacciego(6);
        // działa jak w poleceniu
        foreach(string s in sf)
        {
            Console.WriteLine(s);
        }

        Console.WriteLine("");

        SlowaFibonacciego sf2 = new SlowaFibonacciego(1);
        // wypisuje wg definicji "b"
        foreach(string s in sf2)
        {
            Console.WriteLine(s);
        }

        Console.WriteLine("");

        SlowaFibonacciego sf3 = new SlowaFibonacciego(0);
        // nic nie wypisuje
        foreach(string s in sf3)
        {
            Console.WriteLine(s);
        }

        Console.WriteLine("");

        // i możemy wywołac jeszcze raz cosś
        // co już było wywołane
        foreach(string s in sf)
        {
            Console.WriteLine(s);
        }
    }
}