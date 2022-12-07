using AdventOfCode;
using System;
using System.Linq;

public class Assignment6
{
    public static void Run()
    {
        var lines = FileReader.ReadFile("ass6");
        // Part 1
        var markers = lines.Select(str => FindMarkerInString(str,4)).ToArray();
        Console.WriteLine("Part1");
        Console.WriteLine(markers.FirstOrDefault());
        // Part 2
        var markers2 = lines.Select(str => FindMarkerInString(str,14)).ToArray();
        Console.WriteLine("Part2");
        Console.WriteLine(markers2.FirstOrDefault());
        
    }

    public static int FindMarkerInString(string str, int length)
    {
        char[] chars = new char[length];
        for(int i = 0; i < length-1; i++)
        {
            chars[i+1] = str[i];
        }

        for(int i = 3; i < str.Length; i++)
        {
            for(int j = 0; j < chars.Length-1; j++)
            {
                chars[j] = chars[j+1];
            }
            chars[length-1] = str[i];
            if(!HasDuplicate(chars))
            {
                foreach(char c in chars)
                {
                    Console.Write(c);
                }
                Console.WriteLine();
                return i + 1;
            }
        }
        return -1;
    }

    private static bool HasDuplicate(char[] chars)
    {
        return chars.Distinct().Count() != chars.Length;
    }


    //public static int FindMarkerInString(string str)
    //{
    //    for(int i = 0; i < str.Length; i++)
    //    {
    //        Console.WriteLine(i);
    //        bool match = false;
    //        for(int j = 1; j < 4; j++)
    //        {
    //            if (i - j == -1)
    //            {
    //                match = true;
    //                break;
    //            }
    //            if (str[i] == str[i-j])
    //            {
    //                match = true;
    //                i += j-1;
    //                break;
    //            }
    //        }
    //        if (!match)
    //        {
    //            return i;
    //        }
    //    }
    //    return -1;
    //}
}
