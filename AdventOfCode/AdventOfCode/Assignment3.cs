using AdventOfCode;
using System;
using System.Linq;

public class Assignment3
{
    public static void Run()
	{
		string[] lines = FileReader.ReadFile("ass3");
		var compartmentDuplicates = lines.Select(str => FindDuplicateInCompartments(str)).Select(c => ScoreOfChar(c));

		List<char> badges = new List<char>();
		for(int i = 0; i < lines.Length; i += 3)
		{
			var strArr = new string[] { lines[i], lines[i + 1], lines[i + 2] };
			foreach(char c in strArr[0])
			{
				if (strArr[1].Contains(c) && strArr[2].Contains(c))
				{
					badges.Add(c);
					break;
				}
			}
		}

        Console.WriteLine("Part1:");
        Console.WriteLine(compartmentDuplicates.Sum());
        Console.WriteLine("Part2:");
        Console.WriteLine(badges.Select(c => ScoreOfChar(c)).Sum());
    }

	private static int ScoreOfChar(char c)
    {
        int lowerCaseA = 96;
        int upperCaseA = 64;
        int i = (int)c;
		return i > lowerCaseA ? i - lowerCaseA : i - upperCaseA + 26;

    }

	private static char FindDuplicateInCompartments(string str)
	{
		var str1 = str.Substring(0, str.Length/2);
		var str2 = str.Substring(str.Length/2);
		
		foreach(char c in str1)
		{
			if(str2.Contains(c))
			{
				return c;
			}
		}
		return '0';
	}
}
