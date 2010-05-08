using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace problemB
{
    class Program
    {
        static void Main(string[] args)
        {
            //using(var reader = new StreamReader(System.Console.OpenStandardInput()))
            using (var reader = new StreamReader(File.OpenRead("f:\\var\\tmp\\input.txt")))
            using (var fwriter = File.CreateText("f:\\var\\tmp\\output.txt"))
            using (var stdout = new StreamWriter(System.Console.OpenStandardOutput()))
            {
                List<StreamWriter> writers = new List<StreamWriter> { fwriter,  stdout };
                Int64 tc = Int64.Parse(reader.ReadLine());

                for (Int64 i = 1; i <= tc; ++i)
                {
                    Int64[] rkn = reader.ReadLine().Split().Select(s => Int64.Parse(s)).ToArray();
                    Int64 r = rkn[0], k = rkn[1], n = rkn[2];

                    Int64[] g = reader.ReadLine().Split().Select(s => Int64.Parse(s)).ToArray();

                    writers.ForEach(writer => writer.WriteLine(String.Format("Case #{0}: {1}", i, solve(r, k, g))));
                }
            }
        }

        private static Int64 solve(Int64 r, Int64 k, Int64[] g)
        {
            if (r <= 3 * g.Length)
            {
                Int64 ans = 0;
                for (Int64 first = 0, i = 0; i < r; ++i)
                {
                    Int64 used, now;
                    for (used = g[first], now = 0; used <= k && now < g.Length; first = (first + 1) % g.Length, used += g[first], ++now) ;
                    used -= g[first];
                    Debug.Assert(used <= k);
                    ans += used;
                }
                return ans;
            }
            else
            {
                var offset_and_period = Period(r, k, g);
                Int64 offset = offset_and_period.Key, period = offset_and_period.Value;

                Debug.Assert(offset <= g.Length);
                Debug.Assert(period <= g.Length);

                Int64 periods = (r - offset) / period;
                Int64 nonPeriodical = r - periods * period;

                return solve(nonPeriodical, k, g) + periods * (solve(offset + period, k, g) - solve(offset, k, g));
            }
        }

        private static KeyValuePair<Int64, Int64> Period(Int64 r, Int64 k, Int64[] g)
        {
            Dictionary<Int64, Int64> d = new Dictionary<Int64, Int64>();
            Int64 first = 0, time = 0;

            do
            {
                d[first] = time;
                ++time;
                for (Int64 used = g[first], now = 0; used <= k && now < g.Length; first = (first + 1) % g.Length, used += g[first], ++now) ;
            }
            while (!d.ContainsKey(first));

            return new KeyValuePair<Int64, Int64>(d[first], time - d[first]);
        }
    }
}
