using System.Security.Cryptography;

public class Program
{
    public static void Main()
    {
        var liczby = File.ReadAllLines("liczby.txt").Select(int.Parse);

        var filteredAndSorted =
            from liczba in liczby
            where liczba > 100
            orderby liczba descending
            select liczba;

        foreach (var liczba in filteredAndSorted)
        {
            Console.WriteLine(liczba);
        }

        var filteredAndSorted2 = liczby.Where(liczby => liczby > 100).OrderByDescending(liczby => liczby);

        Console.WriteLine("------------");

        foreach (var liczba in filteredAndSorted2)
        {
            Console.WriteLine(liczba);
        }
    }
}
