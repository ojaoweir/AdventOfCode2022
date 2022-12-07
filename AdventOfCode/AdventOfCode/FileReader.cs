using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public class FileReader
    {
        private static string path = "C:\\projects\\AdventOfCode2022\\AdventOfCode\\";
        public static string[] ReadFile(string assignment)
        {
            return System.IO.File.ReadAllLines(path + assignment + ".txt");
        }
    }
}