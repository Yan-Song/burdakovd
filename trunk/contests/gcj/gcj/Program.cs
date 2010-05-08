using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace gcj
{
    class Program
    {
        static void Main(string[] args)
        {
            //using(var reader = new StreamReader(System.Console.OpenStandardInput()))
            using(var reader = new StreamReader(File.OpenRead("f:\\var\\tmp\\input.txt")))            
            using (var fwriter = File.CreateText("f:\\var\\tmp\\output.txt"))
            {
                List<StreamWriter> writers = new List<StreamWriter> { fwriter, new StreamWriter(System.Console.OpenStandardOutput()) };
                int tc = int.Parse(reader.ReadLine());

                for (int i = 1; i <= tc; ++i)
                {
                    int[] nk = reader.ReadLine().Split().Select(s => int.Parse(s)).ToArray();
                    int n = nk[0], k = nk[1];

                    writers.ForEach(writer => writer.WriteLine(String.Format("Case #{0}: {1}", i, k % (1 << n) == (1 << n) - 1 ? "ON" : "OFF")));
                }
            }
        }
    }
}
