public class Program
{
    public static void Main()
    {
        var surnames = File.ReadAllLines("nazwiska.txt");

        var orderedFirstLetters = surnames
            .OrderBy(s => s)
            .GroupBy(s => s[0]);

        foreach (var letter in orderedFirstLetters)
        {
            Console.WriteLine(letter.Key);
        }
    }
}