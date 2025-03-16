using System.Xml.Serialization;

class Program
{
    class Example
    {
        private string? someString;
        
        public string SomeString
        {
            get { return someString; }
            set { someString = value; }
        }

        public int? SomeInt { set; get; }
    }

    public static void Main()
    {
        Example example = new Example();
        example.SomeString = "qwerty";
        Console.WriteLine(example.SomeString);

        example.SomeInt = 32;
        Console.WriteLine(example.SomeInt);
    }
}