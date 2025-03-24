using System;
using System.Collections.Generic; //listy

class LazyIntList
{
    List<int> lista;
    int ile_el = 0;

    // Metoda definiowania LazyIntList
    public LazyIntList()
    {
        lista = new List<int>();
        ile_el = 0;
    }

    // prosta metoda dodawania/wypisywania
    // chcianych elementow ze wzgledu 
    // na to czy juz sa w liscie czy nie
    virtual public int element(int n)
    {
        if( n >= ile_el)
        {
            for(int i = ile_el; i <= n; i++)
            {
                lista.Add(i);
            }

            ile_el = n+1;
            return lista[n];
        }
        else
        {
            return lista[n];
        }
    }
    
    // size - nic skomplikowanego
    virtual public int size()
    {
        return ile_el;
    }
}

class LazyPrimeLista : LazyIntList
{
    List<int> lista;
    int ile_el = 0;

    // metoda definiowania LazyPrimeList
    public LazyPrimeLista()
    {
        lista = new List<int>();
        ile_el = 0;
    }
    // prosty algorytm do sprawdzania pierwszosci
    bool isprime(int n)
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
    //prosty algorytm wyznaczajacy kolejna l. pierwsza
    int KolejnaPierwsza(int n)
    {
        while(true)
        {
            n = n + 1;
            if(isprime(n))
            {
                return n;
            }
        }
    }

    override public int element(int n)
    {   
        // podzial na tworzenie/wypisywanie elementow
        // ze wzgledu na:
        // 1) lista calkowicie pusta
        // 2) chciany el. nie jest w liscie
        // 3) lista zawiera chciany element
        if(ile_el == 0)
        {
            // jako informatycy bedziemy mowic
            // ze zerowa l. pierwsza to 2
            // pierwsza l. pierwsza to 3 itd.
            lista.Add(2);
            for(int i = 1; i <= n; i++)
            {
                lista.Add(KolejnaPierwsza(lista[i - 1]));
            }
            ile_el = n + 1;
            return lista[n];
        }
        else
        {
            if(ile_el <= n)
            {
                for(int i = ile_el; i <= n ; i++)
                {
                    lista.Add(KolejnaPierwsza(lista[i - 1]));
                }
                ile_el = n + 1;
                return lista[n];
            }
            else
            {
                return lista[n];
            }
        }
    }
    // zwraca po prostu ilosc elementow
    override public int size()
    {
        return ile_el;
    }

}

class Degustacja
{
    static void Main()
    {
        LazyIntList x = new LazyIntList();
        Console.WriteLine("LazyIntList zaczyna z rozmiarem {0}" , x.size());
        Console.WriteLine("zerowy element to {0}" , x.element(0));
        Console.WriteLine("i teraz wielkosc listy to {0}" , x.size());
        Console.WriteLine("dziesiaty el. w liscie to {0}" , x.element(10));
        Console.WriteLine("i teraz wielkosc to {0}" , x.size());
        Console.WriteLine("a el. jedenasty to {0}" , x.element(11));
        Console.WriteLine("i teraz wielkosc: {0}" , x.size());
        Console.WriteLine("piaty z kolei to {0}" , x.element(5));
        Console.WriteLine("a wielkosc to dalej {0}" , x.size());
        Console.WriteLine("el. setny to {0}" , x.element(100));
        Console.WriteLine("to nowa wielkosc {0}" , x.size());
        Console.WriteLine("zerowy el. to dalej {0}" , x.element(0));

        Console.WriteLine();

        LazyIntList p = new LazyPrimeLista();
        Console.WriteLine("LazyPrimeList na start ma rozmiar {0}" , p.size());
        Console.WriteLine("zerowy el. to {0}" , p.element(0));
        Console.WriteLine("pierwszy to {0}" , p.element(1));
        Console.WriteLine("drugi to {0}" , p.element(2));
        Console.WriteLine("Wtedy ma rozmiar {0}" , p.size());
        Console.WriteLine("Trzeci el. to {0}" , p.element(3));
        Console.WriteLine("A rozmiar zmienia sie wtedy na {0}" , p.size());
        Console.WriteLine("El. 15 to {0}", p.element(15));
        Console.WriteLine("i wtedy rozmiar {0}", p.size());
        Console.WriteLine("A el. 3 to dalej {0}", p.element(3));
        Console.WriteLine("a rozmiar zostal {0}", p.size());
    }
}