using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;
using System.Text.RegularExpressions;

namespace gcj
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader iFile = new StreamReader("e:\\data\\progr\\burdakovd\\contests\\gcj\\gcj\\in.txt");
            StreamWriter oFile = new StreamWriter("e:\\data\\progr\\burdakovd\\contests\\gcj\\gcj\\out.txt");

            string line = iFile.ReadLine();

            int[] _line = line.Split(' ').Select(x => Int32.Parse(x)).ToArray();

            int l = _line[0], d = _line[1], n = _line[2];


            Console.WriteLine("l={0} d={1} n={2}", l, d, n);

            List<string> words = new List<string>();

            for (int i = 0; i < d; ++i)
            {
                string word = iFile.ReadLine();
                words.Add(word);
            }

            Regex pr = new System.Text.RegularExpressions.Regex("\\([a-z]+\\)|[a-z]");

            for (int i = 0; i < n; ++i)
            {
                BitArray[] pattern = new BitArray[26];
                string sPattern = iFile.ReadLine();
                
                int cnt = 0;
                foreach(Match match in pr.Matches(sPattern))
                {
                    BitArray b = new BitArray(26, false);
                    foreach (char c in match.Value)
                        if (c != '(' && c != ')')
                            b[c - 'a'] = true;

                    pattern[cnt] = b;
                    ++cnt;
                }

                int ans = 0;
                foreach (string word in words)
                {
                    bool ok = true;
                    
                    for(int j=0; j<l; ++j)
                        if (!pattern[j][word[j] - 'a'])
                        {
                            ok = false;
                            break;
                        }

                    if (ok)
                    {
                        ++ans;
                        //Console.WriteLine("Case #{0}: {1} matches {2}", i, word, sPattern);
                    }
                    else
                    {
                        //Console.WriteLine("Case #{0}: {1} doesn't match {2}", i, word, sPattern);
                    }
                }

                Console.WriteLine("Case #{0}: {1}", i + 1, ans);
                oFile.WriteLine("Case #{0}: {1}", i + 1, ans);

            }
            iFile.Close();
            oFile.Close();
        }
    }
}
