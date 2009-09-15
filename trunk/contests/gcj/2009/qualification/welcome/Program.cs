using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace welcome
{
    class Program
    {
        static void Main(string[] args)
        {
            const string needle = "welcome to code jam";
            const int P = 10000;

            StreamReader iFile = new StreamReader("e:\\data\\progr\\burdakovd\\contests\\gcj\\welcome\\in.txt");
            StreamWriter oFile = new StreamWriter("e:\\data\\progr\\burdakovd\\contests\\gcj\\welcome\\out.txt");

            int tc = Int32.Parse(iFile.ReadLine());

            for (int tn = 1; tn <= tc; ++tn)
            {
                string line = iFile.ReadLine();


                int[,] dp = new int[line.Length + 1, needle.Length + 1];

                for(int i=0; i<=line.Length; ++i)
                    dp[i, 0] = 1;

                for(int i=1; i<=needle.Length; ++i)
                    dp[0, i] = 0;

                for(int i=1; i<=line.Length; ++i)
                    for(int j=1; j<=needle.Length; ++j)
                    {
                        dp[i, j] = dp[i-1, j];
                        if(line[i-1] == needle[j-1])
                            dp[i, j] = (dp[i, j] + dp[i-1, j-1]) % P;
                    }

                Console.WriteLine("Case #{0}: {1:0000}", tn, dp[line.Length, needle.Length]);
                oFile.WriteLine("Case #{0}: {1:0000}", tn, dp[line.Length, needle.Length]);
            }

            iFile.Close();
            oFile.Close();
        }
    }
}
