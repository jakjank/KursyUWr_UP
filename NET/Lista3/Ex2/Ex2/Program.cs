namespace Ex2
{
    public class XMLGenerator
    {
        public string GenerateXML(Object obj)
        {
            Type type = obj.GetType();

            string res = "";
            res += $"<{type.Name}>\n";
            foreach (var property in type.GetProperties())
            {
                res += $"   <{property.Name}>{property.GetValue(obj)}</{property.Name}>\n";
            }
            res += $"</{type.Name}>";

            return res;
        }
    }

    public class Person
    {
        public string Name { get; set; }
        public string Surname { get; set; }
    }
}

public class Progam
{
    public static void Main()
    {
        Ex2.Person person = new()
        {
            Name = "Jan",
            Surname = "Kowalski"
        };
        Ex2.XMLGenerator generator = new();

        Console.WriteLine(generator.GenerateXML(person));
    }
}