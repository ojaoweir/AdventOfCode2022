using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    internal class Assignment1
    {
        public static void Run()
        {
            var t = FileReader.ReadFile("ass1");
            List<int> workshopers = new List<int>();
            workshopers.Add(0);
            foreach (string a in t)
            {
                try
                {
                    var calories = int.Parse(a);
                    workshopers[workshopers.Count - 1] += calories;

                }
                catch (Exception e)
                {
                    workshopers.Add(0);
                }
            }
            workshopers.Sort();
            workshopers.Reverse();

            //Question1
            Console.WriteLine(workshopers.Max());
            //Question2
            Console.WriteLine(workshopers.Take(3).Sum());
        }
    }
}
