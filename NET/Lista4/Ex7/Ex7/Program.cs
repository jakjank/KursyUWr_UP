using System.Collections.Generic;

public class Program
{
    public static void Main()
    {
        var item = new { Field1 = "The value", Field2 = 5 };

        // nie mozemy jawnie okreslic czegos w stylu: List <{ string, int }>
        var theList = new [] {item}.ToList();
        // theList.Add(new { el1 = "value:", el2 = 10 });

        theList.Add(new { Field1 = "value:", Field2 = 10 });

        theList.ForEach(x => Console.WriteLine($"{x.Field1} {x.Field2}"));
    }
}