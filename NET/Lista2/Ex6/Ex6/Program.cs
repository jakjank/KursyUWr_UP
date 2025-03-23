public class Vector2D
{
    double x;
    double y;

    public Vector2D(double X, double Y)
    {
        x = X;
        y = Y;
    }

    public Vector2D()
    {
        x = 0;
        y = 0;
    }

    public static Vector2D operator +(Vector2D v1, Vector2D v2)
    {
        return new Vector2D(v1.x + v2.x, v1.y + v2.y);
    }
    public static Vector2D operator +(Vector2D v1, double num)
    {
        return new Vector2D(v1.x + num, v1.y + num);
    }
    public static Vector2D operator +(double num, Vector2D v1)
    {
        return new Vector2D(v1.x + num, v1.y + num);
    }
    public static Vector2D operator *(Vector2D v1, double num)
    {
        return new Vector2D(v1.x * num, v1.y * num);
    }
    public static Vector2D operator *(double num, Vector2D v1)
    {
        return new Vector2D(v1.x * num, v1.y * num);
    }
    public static double operator *(Vector2D v1, Vector2D v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    public override string ToString()
    {
        return $"({x}, {y})";
    }
}

public class Program
{
    public static void Main()
    {
        Vector2D v1 = new(1, 2);
        Vector2D v2 = new(3, 4);

        Vector2D tmp = new();

        v1 = v1 * 2;
        Console.WriteLine(v1);
        v2 = v2 + 3.5;
        Console.WriteLine(v2);
        tmp = v1 + v2;
        Console.WriteLine(tmp);
        Console.WriteLine(v1 * v2);
    }
}