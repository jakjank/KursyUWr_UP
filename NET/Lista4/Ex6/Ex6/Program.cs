public class Program
{
    public static void Main()
    {
        var requests = File.ReadLines("requests.txt")
            .Select(line =>
            {
                var parts = line.Split(' ');
                if (parts.Length < 5)
                {
                    return null;
                }
                else
                {
                    return new
                    {
                        Time = parts[0],
                        IP = parts[1],
                        RequestType = parts[2],
                        ResName = parts[3],
                        Status = parts[4]
                    };
                }
            })
            .Where(r => r != null);

        var top3 = requests.GroupBy(r => r.IP)
            .Select(g => new
            {
                IP = g.Key,
                Count = g.Count()
            })
            .OrderByDescending(g => g.Count)
            .Take(3);

        foreach (var rekord in top3)
        {
            Console.WriteLine($"{rekord.IP} {rekord.Count}");
        }
    }
}