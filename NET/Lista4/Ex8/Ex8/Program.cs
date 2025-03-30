class Program
{
    static void Main()
    {
        Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y = null;
        Y = f => x => f(Y(f))(x);

        List<int> list = new List<int>() { 1, 2, 3, 4, 5, 6 };

        foreach (var item in list.Select( Y(f => i => (i <= 2) ? 1 : f(i - 1) + f(i - 2))) )
        {
            Console.WriteLine(item);
        }
    }
}
