using EX1;

namespace EX1
{
    // static -> cant create instance and only contains static members
    public static class Helper
    {
        // static method -> method of class, not of instance
        // in -> passes ba reference but doesnt allow assigning the val
        public static int Add(in int a, in int b)
        {
            // a = a + 1;
            return a + b;
        }

        // ref -> passes by ref.
        public static void Double(ref int x)
        {
            x *= 2;
        }

        // out -> allows for 'returning' multiple values
        public static void InitializeTriple(out int a, out int b, out int c)
        {
            a = 0;
            b = 1;
            c = 2;
        }

        // params allow for passing multiple args,
        // they dont have to be in array and 0 args calls are suported
        public static void Print(params int[] nums)
        {
            foreach(int num in nums){
                Console.WriteLine(num);
            }
        }
    }

    // sealed -> cannot be a base class
    sealed class Baby { }
    // WONT WORK class WorkingBaby : Baby { } 

    // abstract -> no instances, can contain abstraact methods, meant to be inherited
    public abstract class Animal
    {
        // abstract method has no body and must be overrided
        public abstract void Sound();

        // virtual method has base implementation, but can be overrided
        public virtual void Run()
        {
            Console.WriteLine("going away");
        }
    }

    // partial -> allows a class to be splitted in mmultiple files
    public partial class Dog : Animal
    {
        public override void Sound()
        {
            Console.WriteLine("woof woof");
        }

        public override void Run()
        {
            Console.WriteLine("Running away");
        }
    }

}

public class Program
{
    public static void Main()
    {
        int a, b, c;
        Helper.InitializeTriple(out a, out b, out c);
        Helper.Print(a, b, c);
        Helper.Double(ref b);
        Helper.Print(a, b);


        Dog myDog = new("Rex");
        Console.WriteLine(myDog.GetName());
    }
}