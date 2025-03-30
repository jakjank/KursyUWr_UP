using ClassLibrary1;

class App1
{
    static void Main()
    {
        Console.WriteLine("we are in app1");
        App1.libraryTest();
    }

    static void libraryTest()
    {
        ClassLibrary1.Class1 library1 = new Class1();
        ClassLibrary2.Class2 library2 = new ClassLibrary2.Class2();

        library1.smallLibrary();
        library2.bigLibrary();
    }
}