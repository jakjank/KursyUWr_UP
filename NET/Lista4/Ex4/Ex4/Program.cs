using System;
using System.IO;
using System.Linq;

class Program
{
    static void Main()
    {
        string folderPath = @".\";

        long FilesSizeSum = Directory.GetFiles(folderPath)
            .Select(file => new FileInfo(file).Length)
            .Aggregate(0L, (sum, size) => sum + size);

        Console.WriteLine($"Suma długości plików: {FilesSizeSum} bajtów");
    }
}