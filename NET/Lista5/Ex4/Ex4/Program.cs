using System;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;

public static class StringAwaiterExtensions
{
    private static readonly HttpClient client = new();
    public static TaskAwaiter<string> GetAwaiter(this string url)
    {
        return client.GetStringAsync(url).GetAwaiter();
    }
}

class Program
{
    public static async Task Main()
    {
        //Console.WriteLine("1");
        Console.WriteLine(await "https://www.google.com");
        //Console.WriteLine("2");
    }
}