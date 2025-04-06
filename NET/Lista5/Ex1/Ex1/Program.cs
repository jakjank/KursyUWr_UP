using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;

public class MyBenchmarks
{
    const int iterations = 10000000;
    
    [Benchmark]
    public void Benchmark1()
    {
        int x = 3, y = 4;
        for(int i = 0; i < iterations; i++)
        {
            _ = DoWork1(x, y);
        }
    }

    [Benchmark]
    public void Benchmark2()
    {
        int x = 3, y = 4;
        for (int i = 0; i < iterations; i++)
        {
            _ = DoWork2(x, y);
        }
    }

    public int DoWork1(int x, int y)
    {
        return x + y;
    }

    public dynamic DoWork2(dynamic x, dynamic y)
    {
        return x + y;
    }
}


class Program
{
    public static void Main()
    {
        var summary = BenchmarkRunner.Run<MyBenchmarks>();
    }
}