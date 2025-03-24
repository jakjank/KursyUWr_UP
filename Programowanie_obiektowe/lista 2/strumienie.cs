using System;

class IntStream
{
    //aktualna to zmienna pamietajaca ostatnie co wypisalismy
    int aktualna = -1;
    virtual public int next()
    {   
        // nie zwracamy nic nowego jesli koniec strumienia
        if(eos())
        {
            return aktualna;
        }
        aktualna += 1;
        return aktualna;
    }
    virtual public void reset()
    {
        aktualna = -1;
    }
    // koniec gdy aktualna jest najw. mozliwa
    virtual public bool eos()
    {
        if(aktualna == int.MaxValue)
        { 
            return true;
        }
        return false;
    }
}

class PrimeStream : IntStream
{
    int aktualna = 1;

    // algorytm sprawdzajacy czy dana liczba jest pierwsza
    bool CzyPierwsza(int n)
    {
        if(n != 2 && n % 2 == 0)
        {
            return false;
        }

        for(int i = 3; i*i <= n; i += 2)
        {
            if(n % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    
    // algorytm zwraccajacy kolejna liczbe pierwsza 
    // po danej liczbie n
    int KolejnaPierwsza(int n)
    {
        while(true)
        {
            n = n + 1;
            if(CzyPierwsza(n))
            {
                return n;
            }
        }
    }
    override public int next()
    {
        // jesli nie mozemy zwrocic kolejnej to 
        // next nie daje nowych wartosci
        if(eos())
        {
            return aktualna;
        }
        aktualna = KolejnaPierwsza(aktualna);
        return aktualna;
    }
    override public void reset()
    {
        aktualna = 1;
    }   
    // w eos() sprawdzamy po prostu czy aktualna
    // jest rowna najwiekszej mozliwej do zapisania 
    // na int licznie pierwszej czyli int max val (2^31-1)
    override public bool eos()
    {
        if(aktualna ==  int.MaxValue)
        {
            return true;
        }
        return false;
    }
}

class RandomStream : IntStream
{

    // korzystam z klasy Random
    Random rnd = new Random();

    override public int next()
    {
        return rnd.Next();
    }
    public override bool eos()
    {
        return false;
    }
}

class RandomWordStream
{
    // dlugosc to kolejne liczby pierwsze dane
    // z wczesniejszej klasy PrimeStream
    PrimeStream dlugosc = new PrimeStream();


    // dane to losowe liczby uzyskane za pomoca
    // wczesniejszej klasy RandomStream
    RandomStream dane = new RandomStream();


    // next bierze pusty string i dokleja do niego
    // dlugosc razy (wiem ze okropnie to brzmi)
    // znaki uzyskane z losowej liczby z danych
    // po dostosowaniu jej tak aby byla jakims
    // znakiem z ASCII
    public string next()
    {
        string tmp = "";

        for(int i = dlugosc.next() ; i>0 ; i--)
        {
            tmp += (char)(dane.next() % 94 + 32);
        }

        return tmp;
    }
}

class MalutkiTescik
{
    static void Main()
    {
        // wypisywanie kolejnych l. naturalnych 
        // i sprawdzanie czy reset dziala
        IntStream tmp = new IntStream();
        Console.WriteLine("utworzenie strumienia i wypisanie next 2 razy:");
        Console.WriteLine(tmp.next());
        Console.WriteLine(tmp.next());
        tmp.reset();
        Console.WriteLine("reset strumienia i wypisanie next 3 razy:");
        Console.WriteLine(tmp.next());
        Console.WriteLine(tmp.next());
        Console.WriteLine(tmp.next());

        // wypisywanie trzech kolejnych liczb pierwszych
        PrimeStream ps = new PrimeStream();
        Console.WriteLine("utworzenie PrimeStream i wypisanie next 3 razy:");
        Console.WriteLine(ps.next());
        Console.WriteLine(ps.next());
        Console.WriteLine(ps.next());

        // wypisywanie losowych liczb 
        Console.WriteLine("utworzenie RandomStream i wypisanie dwukrotnie next");
        RandomStream rd = new RandomStream();
        Console.WriteLine(rd.next());
        Console.WriteLine(rd.next());

        // wypisywanie losowych stringow o dlugosciach
        // czterech kolejnych liczb pierwszych 
        Console.WriteLine("utworzenie RandomStreamWord i wypisanie 4 razy next");
        Console.WriteLine("powinny miec dlugosci odpowiadajace kolejnym czterem l. pierw.");
        Console.WriteLine("to jest: 2, 3, 5, 7");
        RandomWordStream rws = new RandomWordStream();
        Console.WriteLine(rws.next());
        Console.WriteLine(rws.next());
        Console.WriteLine(rws.next());
        Console.WriteLine(rws.next());
    }
}

