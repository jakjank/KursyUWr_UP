public static class StringExt
{
    public static bool IsPalindrome(this string str)
    {
        string cleaned = str.ToLower().Replace(" ", "");
        return cleaned == new string(cleaned.Reverse().ToArray());
    }
}

class Program
{
    static void Main()
    {
        string word = "kobyła ma mały bok";
        Console.WriteLine(word.IsPalindrome());

        string word2 = "kobyła nie ma małego boku";
        Console.WriteLine(word2.IsPalindrome());
    }
}