// ~destructor is called by garbage collector (we ddont know when)
// Dispose is calledby programmer
// Dispose DOESNT free the memory. It closes files etc. (manual cleanup)
// but the object is still usable after calling dispose

using Ex2;

namespace Ex2
{
    public class Class1
    {
        public void Print()
        {
            Console.WriteLine("Hello");
        }
        ~Class1()
        {
            Console.WriteLine("Destructor called");
        }
    }

    public class Class2 : IDisposable
    {
        readonly int count;
        static int MAX_COUNT=0;

        public Class2()
        {
            MAX_COUNT += 1;
            count = MAX_COUNT;
        }
        public void Print()
        {
            Console.WriteLine($"Hello {count}");
        }
        public void Dispose()
        {
            Console.WriteLine($"Dispose called on {count}");
        }
    }
}

public class MyProgram
{
    public static void Main()
    {
        Class1 c1 = new Class1();
        c1 = null;
        GC.Collect();
        GC.WaitForPendingFinalizers();

        Class2 c2 = new Class2();
        c2.Dispose();
        //c2.Print();
        //Console.WriteLine("Forcing delay...");
        //Thread.Sleep(1000000000);

        using(Class2 c3 = new())
        {
            c3.Print();
        }
    }
}