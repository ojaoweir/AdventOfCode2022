using AdventOfCode;
using System;
using System.Diagnostics;

public class Assignment5
{
    public static void Run()
    {
        Stack<char>[] stacks;
        string[] lines = FileReader.ReadFile("ass5");

        var startPositionLines = lines.TakeWhile(str => str != "").ToArray();
        var moveOrders = lines.Skip(startPositionLines.Count() + 1);

        foreach(string str in startPositionLines)
        {
            Console.WriteLine(str);
        }

        var numberOfStacks = startPositionLines.Last().Split(" ").Where(c => !c.Equals("")).Last().Select(c => int.Parse(c.ToString())).SingleOrDefault();
        stacks = new Stack<char>[numberOfStacks];
        for(int i = 0; i < stacks.Length; i++)
        {
            stacks[i] = new Stack<char>();
        }
        
        for(int i = startPositionLines.Length - 2; i >= 0; i--)
        {
            var boxes = startPositionLines[i].Replace("     ", " _ ").Split(" ").ToArray();
            for(int k = 0; k < stacks.Length; k++)
            {
                if(!boxes[k].Equals("_") && !boxes[k].Equals(""))
                {
                    stacks[k].Push(boxes[k][1]);
                } 
            }
        }

        PrintStacks(stacks);
        Instruction[] instructions = moveOrders.Select(str => new Instruction(str)).ToArray();
       // Part1(instructions, stacks);
        Part2(instructions, stacks);

        for(int i = 0; i < stacks.Length; i++)
        {
            Console.Write(stacks[i].Pop());
        }
        
    }

    public static void Part1(Instruction[] instructions, Stack<char>[] stacks)
    {
        foreach (Instruction i in instructions)
        {
            Console.WriteLine();
            Console.WriteLine();
            i.Print();
            i.Execute(stacks);
            PrintStacks(stacks);
        }
    }

    public static void Part2(Instruction[] instructions, Stack<char>[] stacks)
    {
        foreach (Instruction i in instructions)
        {
            Console.WriteLine();
            Console.WriteLine();
            i.Print();
            i.Execute90001(stacks);
            PrintStacks(stacks);
        }
    }

    public static void PrintStacks(Stack<char>[] stacks)
    {
        var newStacks = new Stack<char>[stacks.Length];
        var t = stacks.Select(s => s.Reverse().ToArray());
        foreach (char[] cArr in t)
        {
            foreach (char c in cArr)
            {
                Console.Write(c);
            }
            Console.WriteLine();
        }
    }
}

public class Instruction
{
    private int amount;
    private int fromColumn;
    private int toColumn;
    public Instruction(string line)
    {
        var t = line.Split(" ").Where(str => str != "").ToArray();
        amount = int.Parse(t[1]);
        fromColumn = int.Parse(t[3]) - 1;
        toColumn = int.Parse(t[5]) - 1;
    }

    public void Execute(Stack<char>[] stacks)
    {
        for(int i = 0; i < amount; i++)
        {
            stacks[toColumn].Push(stacks[fromColumn].Pop());
        }
    }
    public void Execute90001(Stack<char>[] stacks)
    {
        var temp = new char[amount];
        for(int i = 0; i < amount; i++)
        {
            temp[i] = stacks[fromColumn].Pop();
        }
        for(int i = temp.Length-1; i >= 0; i--)
        {
            stacks[toColumn].Push(temp[i]);
        }
    }

    public void Print()
    {
        Console.WriteLine("Move " + amount + " from " + (fromColumn) + " to " + (toColumn));
    }
}
