class BaseClass
{
    public void ImPublic()
    {
        Console.WriteLine("Im Public");
    }
    protected void ImProtected()
    {
        Console.WriteLine("Im Protected");
    }
    private void ImPrivate()
    {
        Console.WriteLine("Im Private");
    }
    internal void ImInternal()
    {
        Console.WriteLine("Im Internal");
    }

    public virtual void accessibleMethods()
    {
        ImPublic();
        ImProtected();
        ImPrivate();
        ImInternal();
    }
}

class DerivedClass : BaseClass 
{
    public override void accessibleMethods()
    {
        ImPublic();
        ImProtected();
        // ImPrivate();
        ImInternal();
    }
}

class Program
{
    static void Main()
    {
        BaseClass obj = new BaseClass();
        Console.WriteLine("methods in BaseClass:");
        obj.accessibleMethods();

        DerivedClass derivedObj = new DerivedClass();
        Console.WriteLine("\nmethods in DerivedClass:");
        derivedObj.accessibleMethods();

        Console.WriteLine("\nBaseClass methods in Main:");
        obj.ImPublic();
        obj.ImInternal();
        //obj.ImProtected();
        //obj.ImPrivate()

        Console.WriteLine("\nOtherClass in the same project:");
        OtherClass.checkInternal();
    }
}