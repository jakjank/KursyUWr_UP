using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        List<int> list = new List<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        Console.WriteLine("list:");
        list.ForEach(delegate (int x) {
            Console.Write($"{x}, ");
        });

        List<int> plusTen = list.ConvertAll(delegate (int x) { return x + 10; });

        Console.WriteLine("\nConvertAll (+10):");
        plusTen.ForEach(delegate (int x) {
            Console.Write($"{x}, ");
        });

        List<int> divisible3 = list.FindAll(delegate (int x) { return x % 3 == 0; });

        Console.WriteLine("\nFindAll (%3==0):");
        divisible3.ForEach(delegate (int x) {
            Console.Write($"{x}, ");
        });


        plusTen.RemoveAll(delegate (int x) { return x % 4 == 0; });

        Console.WriteLine("\nRemoveAll (plusTen no 4 div):");
        plusTen.ForEach(delegate (int x) {
            Console.Write($"{x}, ");
        });

        list.Sort(delegate (int a, int b) { return a > b ? -1 : a == b ? 0 : 1; });

        Console.WriteLine("\nSort desc:");
        list.ForEach(delegate (int x) {
            Console.Write($"{x}, ");
        });
    }
}
