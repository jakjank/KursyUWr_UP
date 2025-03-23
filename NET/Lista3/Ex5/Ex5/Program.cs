using System;
using System.Collections.Generic;
using System.Linq.Expressions;

public class ListHelper
{
    public static List<TOutput> ConvertAll<T, TOutput>(
    List<T> list,
    Converter<T, TOutput> converter)
    {
        List<TOutput> res = [];
        foreach(T elem in list)
        {
            res.Add(converter(elem));
        }
        return res;
    }
    public static List<T> FindAll<T>(
    List<T> list,
    Predicate<T> match)
    {
        List<T> res = [];
        foreach (T elem in list)
        {
            if (match(elem))
            {
                res.Add(elem);
            }
        }
        return res;
    }
    public static void ForEach<T>(List<T> list, Action<T> action)
    {
        foreach (T elem in list)
        {
            action(elem);
        }
    }
    public static int RemoveAll<T>(
    List<T> list,
    Predicate<T> match)
    {
        int count = 0;
        for(int i = 0; i < list.Count; i++)
        {
            if (match(list[i]))
            {
                count += 1;
                list.RemoveAt(i);
            }
        }
        return count;
    }
    public static void Sort<T>(
    List<T> list,
    Comparison<T> comparison)
    {
        for (int i = 0; i < list.Count - 1; i++)
        {
            for (int j = 0; j < list.Count - 1; j++)
            {
                if (comparison(list[j], list[j+1]) > 0)
                {
                    T tmp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = tmp;
                }
            }
        }
    }
}

class Program
{
    static void Main()
    {
        List<int> list = new List<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        Console.WriteLine("list:");
        ListHelper.ForEach(list, delegate (int x) {
            Console.Write($"{x}, ");
        });

        List<int> plusTen = ListHelper.ConvertAll(list, delegate (int x) { return x + 10; });

        Console.WriteLine("\nConvertAll (+10):");
        ListHelper.ForEach(plusTen, delegate (int x) {
            Console.Write($"{x}, ");
        });

        List<int> divisible3 = ListHelper.FindAll(list, delegate (int x) { return x % 3 == 0; });

        Console.WriteLine("\nFindAll (%3==0):");
        ListHelper.ForEach(divisible3, delegate (int x) {
            Console.Write($"{x}, ");
        });


        ListHelper.RemoveAll(plusTen, delegate(int x) { return x % 4 == 0; });

        Console.WriteLine("\nRemoveAll (plusTen no 4 div):");
        ListHelper.ForEach(plusTen, delegate (int x) {
            Console.Write($"{x}, ");
        });

        ListHelper.Sort(list, delegate (int a, int b) { return a > b ? -1 : a == b ? 0 : 1; });

        Console.WriteLine("\nSort desc:");
        ListHelper.ForEach(list, delegate (int x) {
            Console.Write($"{x}, ");
        });
    }
}