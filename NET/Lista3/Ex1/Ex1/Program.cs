namespace Ex1
{

    public interface IClassInfo
    {
        string[] GetFieldNames();
        object GetFieldValue(string fieldName);
    }

    public class XMLGenerator
    {
        public string GenerateXML(IClassInfo dataObject)
        {
            string res = "";
            res += $"<{dataObject.GetType().Name}>\n";
            foreach (string field in dataObject.GetFieldNames())
            {
                res += $"   <{field}>{dataObject.GetFieldValue(field)}</{field}>\n";
            }
            res += $"</{dataObject.GetType().Name}>";

            return res;
        }
    }

    public class Person : IClassInfo
    {
        public string Name { get; set; }
        public string Surname { get; set; }
        public string[] GetFieldNames()
        {
            return new[] { "Name", "Surname" };
        }
        public object GetFieldValue(string fieldName)
        {
            switch (fieldName)
            {
                case "Name":
                    return this.Name;
                case "Surname":
                    return this.Surname;
                default:
                    return null;
            }
            throw new NotImplementedException();
        }
    }
}

public class Progam
{
    public static void Main()
    {
        Ex1.Person person = new()
            {
                Name = "Jan",
                Surname = "Kowalski"
            };
        Ex1.XMLGenerator generator = new();

        Console.WriteLine(generator.GenerateXML(person));
    }
}