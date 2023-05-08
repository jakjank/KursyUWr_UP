using zad2;

class Test
{
    static void Main()
    {
        //mogę sobie stworzyć słownik 
        //działający jako książka telefoniczna

        MyDictionary<string , int> numery = 
        new MyDictionary<string , int>();

        //i dodam tam numery rodziców kolegi
        //oraz mej lubej
        numery.dodaj("luba" , 666);
        numery.dodaj("tata", 123);
        numery.dodaj("mama" , 567);
        numery.dodaj("kolega", 421);

        //to jaki jest numer do mamy?
        Console.WriteLine(numery.wyszukaj("mama"));
        //a do kolegi?
        Console.WriteLine(numery.wyszukaj("kolega"));
        //z koleji nie mam numeru do prezydenta
        Console.WriteLine(numery.wyszukaj("prezydent"));

        //muszę porozmawiać z dziewczyną
        Console.WriteLine(numery.wyszukaj("luba"));
        //ale z dziewczyną sie rozstałem i teraz powinienem
        //usunąć jej numer żeby mi w głowie nie mieszał
        numery.usun("luba");
        //ale jednak chcę zadzwonić
        Console.WriteLine(numery.wyszukaj("luba"));
        //ale juz nie ma

        //a jaki jest numer do taty?
        Console.WriteLine(numery.wyszukaj("tata"));
        //ale nie działa! Przecież zmienił
        //muszę dodać nowy
        numery.dodaj("tata", 321);
        //to jaki jest jego numer?
        Console.WriteLine(numery.wyszukaj("tata"));

    }
}
