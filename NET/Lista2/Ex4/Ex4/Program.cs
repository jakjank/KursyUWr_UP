public delegate void EventHandler(object sender, string propertyName, object propertVal);

public class Person(string name, string surname)
{
    public event EventHandler propertyChanged;

    private string _name = name;
    private string _surname = surname;
    //public string Name
    //{
    //    get
    //    {
    //        return _name;
    //    }
    //    set 
    //    { 
    //        propertyChanged.Invoke(this, "Name", value);
    //        this._name = value;
    //    }
    //}
    //public string Surname 
    //{
    //    get
    //    {
    //        return _surname;
    //    }
    //    set
    //    {
    //        propertyChanged.Invoke(this, "Surname", value);
    //        this._surname = value;
    //    }
    //}
    public string Name
    {
        get
        {
            return _name;
        }
        set
        {
            if (value != _name)
            {
                propertyChanged.Invoke(this, "Name", value);
                this._name = value;
            }
        }
    }
    public string Surname
    {
        get
        {
            return _surname;
        }
        set
        {
            if (value != _surname)
            {
                propertyChanged.Invoke(this, "Surname", value);
                this._surname = value;
            }
        }
    }

}

public class Subscriber
{
    public Subscriber(Person person)
    {
        person.propertyChanged += Person_propertyChanged;
    }

    private void Person_propertyChanged(object sender, string propertyName, object propertVal)
    {
        Console.WriteLine($"{sender} changed {propertyName} to {propertVal}");
    }
}


class Program
{
    public static void Main()
    {
        Person person = new("Jan", "Kowalski");
        Console.WriteLine(person.Name);
        Console.WriteLine(person.Surname);

        Subscriber example_subs = new(person);

        person.Name = "Janusz";
        person.Name = "Janusz";
    }
}