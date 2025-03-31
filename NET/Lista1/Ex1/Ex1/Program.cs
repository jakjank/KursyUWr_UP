using System;
using System.Collections.Generic;
using System.IO;

class Program
{
    static void Main()
    {
        List<int> res = new List<int>();
        for(int i=1; i<100000; i++)
        {
            if(dividesByDigitsSum(i) && dividesByDigits(i))
            {
                res.Add(i);
            }
        }

        foreach(int el in res)
        {
            Console.Write(el + " ");
        }
    }
    static bool dividesByDigitsSum(int a)
    {
        int tmp = a;
        int digitSum = 0;
        while(a > 0)
        {
            digitSum += a % 10;
            a /= 10;
        }
        return (tmp % digitSum) == 0;
    }

    static bool dividesByDigits(int a)
    {
        int tmp = a;
        int digit;
        while (a > 0)
        {
            digit = a % 10;
            if(digit == 0) { return false; }
            if (tmp % digit != 0) { return false; }
            a /= 10;
        }
        return true;
    }
}