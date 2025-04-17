using System.Dynamic;

public class MyDanamic : DynamicObject
{
    private Dictionary<string, object?> members = new();
    private object[] values = new object[100];

    public override bool TryGetMember(GetMemberBinder binder, out object? result)
    {
        Console.WriteLine($"probuje pobrac {binder.Name}:");
        if (members.TryGetValue(binder.Name, out result))
        {
            return true;
        }
        result = null;
        return false;
    }

    public override bool TrySetMember(SetMemberBinder binder, object? value)
    {
        Console.WriteLine($"ustawiam {binder.Name} na {value}");
        members[binder.Name] = value;
        return true;
    }

    public override bool TrySetIndex(SetIndexBinder binder, object[] indexes, object value)
    {
        if (indexes.Length == 1 && indexes[0] is int index)
        {
            if (index >= 0 && index < values.Length)
            {
                values[index] = value;
                Console.WriteLine($"Ustawiono {index} na {value}");
                return true;
            }
        }
        Console.WriteLine("zły indeks");
        return false;
    }

    public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object? result)
    {
        if (indexes.Length == 1 && indexes[0] is int index && index >= 0 && index < values.Length)
        {
            Console.WriteLine($"probuje pobrac indeks {index}");
            result = values[index];
            return true;
        }

        Console.WriteLine($"zły indeks");
        result = null;
        return false;
    }

    public override bool TryInvoke(InvokeBinder binder, object?[]? args, out object? result)
    {
        Console.WriteLine($"MyDanamic jako funkcja");

        Console.WriteLine("Argumenty:");
        foreach (var arg in args)
        {
            Console.WriteLine(arg);
        }

        result = args.Length;

        return true;
    }

    public override bool TryInvokeMember(InvokeMemberBinder binder, object?[]? args, out object? result)
    {
        Console.WriteLine($"Nieistniejaca metoda: {binder.Name}");

        Console.WriteLine("Argumenty:");
        foreach (var arg in args)
        {
            Console.WriteLine(arg);
        }

        result = args.Length;

        return true;
    }

    public override bool TryUnaryOperation(UnaryOperationBinder binder, out object? result)
    {
        result = null;

        if(binder.Operation == System.Linq.Expressions.ExpressionType.Not)
        {
            result = !true;
            return true;
        }
        return false;
    }

    public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object? result)
    {
        if(binder.Operation == System.Linq.Expressions.ExpressionType.Add && arg is int val)
        {
            result = 1 + val;
            return true;
        }
        result = null;
        return false;
    }
}

public class Program
{
    public static void Main()
    {
        dynamic myDanamic = new MyDanamic();

        myDanamic.virtualField = 4;
        Console.WriteLine(myDanamic.virtualField);
        //object? smh = myDanamic.virtualField2;

        myDanamic[3] = 72;
        Console.WriteLine(myDanamic[3]);
        //Console.WriteLine(myDanamic[99]);

        Console.WriteLine(myDanamic(1, 2, 3));
        Console.WriteLine(myDanamic.SomeMethod(4,5,6,7));

        Console.WriteLine(!myDanamic);
        Console.WriteLine(myDanamic + 77);

    }
}