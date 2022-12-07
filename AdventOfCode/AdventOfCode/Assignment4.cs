using AdventOfCode;
using System;

public class Assignment4
{
    public static void Run()
    {
        var lines = FileReader.ReadFile("ass4");
        var containEachOther = lines.Select(str => str.Split(",").Select(subStr => new ElfAssignment(subStr)).ToArray())
                     .Select(ass => ElfAssignment.ContainEachOther(ass[0], ass[1]))
                     .Where(b => b)
                     .Count();        
        var overLapEachOther = lines.Select(str => str.Split(",").Select(subStr => new ElfAssignment(subStr)).ToArray())
                     .Select(ass => ElfAssignment.OverlapEachOther(ass[0], ass[1]))
                     .Where(b => b)
                     .Count();
        Console.WriteLine("Step1: ");
        Console.WriteLine(containEachOther);
        Console.WriteLine("Step2: ");
        Console.WriteLine(overLapEachOther);
    }
}

public class ElfAssignment
{
    private int fromId;
    private int toId;

    public ElfAssignment(string order)
    {
        var t = order.Split("-").Select(str => int.Parse(str)).ToArray();
        fromId = t[0];
        toId = t[1];
    }

    public static bool ContainEachOther(ElfAssignment left, ElfAssignment right)
    {
        if(left.fromId <= right.fromId)
        {
            if(left.toId >= right.toId)
            {
                return true;
            }
        } 
        if(left.fromId >= right.fromId)
        {
            if(right.toId >= left.toId)
            {
                return true;
            }
        }
        return false;
    }

    public static bool OverlapEachOther(ElfAssignment left, ElfAssignment right)
    {
        var t = new List<int>();
        for(int i = left.fromId; i <= left.toId; i++)
        {
            t.Add(i);
        }        
        var t2 = new List<int>();
        for(int i = right.fromId; i <= right.toId; i++)
        {
            t2.Add(i);
        }

        foreach(int i in t)
        {
            if (t2.Contains(i)) return true;
        }
        return false;
    }
}
