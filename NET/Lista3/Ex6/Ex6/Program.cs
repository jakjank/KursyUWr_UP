public class Node<T> where T : IComparable<T>
{
    public T Value { get; set; }
    public Node<T>? Left { get; set; }
    public Node<T>? Right { get; set; }

    public Node(T value)
    {
        Value = value;
        Left = null;
        Right = null;
    }
}


public class BinaryTree<T> where T : IComparable<T>
{
    public BinaryTree(){}

    public Node<T>? root { get; set; }
    public BinaryTree<T>? left { get; set; }
    public BinaryTree<T>? right { get; set; }

    public void Add(T value)
    {
        root = AddRec(root, value);
    }

    private Node<T> AddRec(Node<T>? node, T value)
    {
        if (node == null)
            return new Node<T>(value);

        if (value.CompareTo(node.Value) < 0)
            node.Left = AddRec(node.Left, value);
        else if (value.CompareTo(node.Value) > 0)
            node.Right = AddRec(node.Right, value);

        return node;
    }

    public void InOrderTraversal()
    {
        InOrderRecursive(root);
        Console.WriteLine();
    }

    private void InOrderRecursive(Node<T>? node)
    {
        if (node != null)
        {
            InOrderRecursive(node.Left);
            Console.Write(node.Value + " ");
            InOrderRecursive(node.Right);
        }
    }

    public IEnumerable<T> DepthFirst()
    {
        if (root == null) yield break;

        Stack<Node<T>> stack = new();
        stack.Push(root);

        while (stack.Count > 0)
        {
            Node<T> node = stack.Pop();
            yield return node.Value;

            if (node.Right != null) stack.Push(node.Right);
            if (node.Left != null) stack.Push(node.Left);
        }
    }

    public IEnumerable<T> BreadthFirst()
    {
        if (root == null) yield break;

        Queue<Node<T>> queue = new();
        queue.Enqueue(root);

        while (queue.Count > 0)
        {
            Node<T> node = queue.Dequeue();
            yield return node.Value;

            if (node.Left != null) queue.Enqueue(node.Left);
            if (node.Right != null) queue.Enqueue(node.Right);
        }
    }
}

public class Program
{
    public static void Main()
    {
        BinaryTree<int> bt = new();
        bt.Add(7);
        bt.Add(1);
        bt.Add(2);
        bt.Add(33);
        bt.Add(8);
        bt.Add(7);
        bt.Add(5);
        bt.Add(-1);
        bt.Add(15);
        bt.Add(16);
        bt.InOrderTraversal();

        foreach(int val in bt.BreadthFirst())
        {
            Console.Write(val.ToString() + ", ");
        }
        Console.WriteLine("");

        foreach (int val in bt.DepthFirst())
        {
            Console.Write(val.ToString() + ", ");
        }
        Console.WriteLine("");
    }
}