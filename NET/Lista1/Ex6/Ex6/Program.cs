
class Person
{
    string name;
    int age;

    public Person()
    {
        name = "unknowm";
        age = -1;
    }

    public Person(string name, int age)
    {
        this.name = name;
        this.age = age;
    }

    public virtual void describe()
    {
        Console.WriteLine($"{name},{age}");
    }

    public void describe(bool showAge)
    {
        if(showAge) this.describe();
        else Console.WriteLine($"{name}");
    }

    //Wont work
    //public string describe()
    //{
    //    return ($"({name},{age})";
    //}

    public string describe(string message)
    {
        return $"{name},{age},{message}";
    }
}

class Actor : Person
{
    int noMovies;

    public Actor(string name, int age, int noMovies) : base(name,age)
    {
        this.noMovies = noMovies;
    }

    public override void describe()
    {
        Console.Write($"{noMovies}, ");
        base.describe();
    }
}

class Program
{
    static void Main()
    {
        Person p1 = new Person();
        Person tom = new Person("Tom", 33);
        Actor anthony = new Actor("Anthony", 87, 123);

        p1.describe();
        tom.describe(false);
        Console.WriteLine(tom.describe("Hi Im Tom"));
        anthony.describe();
    }
}
