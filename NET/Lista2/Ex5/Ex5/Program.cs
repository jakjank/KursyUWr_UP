class Grid
{
    int[,] grid;
    public Grid(int no_rows, int no_cols)
    {
        grid = new int[no_rows, no_cols];
    }

    public int this[int row, int col]
    {
        get
        {
            return grid[row, col];
        }
        set
        {
            grid[row, col] = value;
        }
    }

    public int[] this[int row]
    {
        get
        {
            int length = grid.GetLength(1);
            int[] rowVals = new int[length];
            for (int i = 0; i < length; i++)
            {
                rowVals[i] = grid[row, i];
            }
            return rowVals;
        }
    }
}

class Program
{
    public static void Main()
    {
        Grid grid = new(3, 4);
        grid[0, 0] = 33;
        grid[0, 3] = 44;
        grid[2, 2] = 11;
        Console.WriteLine(grid[2, 2]);
        int[] vals = grid[0];
        foreach (int val in vals)
        {
            Console.Write($"{val} ");
        }
    }
}