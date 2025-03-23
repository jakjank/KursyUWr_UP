using System.Reflection;

namespace Ex3
{
    [AttributeUsage(AttributeTargets.Property)]
    public class IgnoreInXML : Attribute {}
    public class XMLGenerator
    {
        public string GenerateXML(Object obj)
        {
            Type type = obj.GetType();

            string res = "";
            res += $"<{type.Name}>\n";
            foreach (var property in type.GetProperties())
            {
                if (property.GetCustomAttribute(typeof(IgnoreInXML)) != null)
                {
                    continue;
                }
                res += $"   <{property.Name}>{property.GetValue(obj)}</{property.Name}>\n";
            }
            res += $"</{type.Name}>";

            return res;
        }
    }

    public class Person
    {
        public string Name { get; set; }

        [IgnoreInXML]
        public string Surname { get; set; }
    }
}

public class Progam
{
    public static void Main()
    {
        Ex3.Person person = new()
        {
            Name = "Jan",
            Surname = "Kowalski"
        };
        Ex3.XMLGenerator generator = new();

        Console.WriteLine(generator.GenerateXML(person));
    }
}