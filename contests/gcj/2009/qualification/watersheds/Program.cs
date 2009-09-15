using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace watersheds
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader iFile = new StreamReader("e:\\data\\progr\\burdakovd\\contests\\gcj\\watersheds\\in.txt");
            StreamWriter oFile = new StreamWriter("e:\\data\\progr\\burdakovd\\contests\\gcj\\watersheds\\out.txt");

            int tc = Int32.Parse(iFile.ReadLine());

            for (int tn = 1; tn <= tc; ++tn)
            {
                string line = iFile.ReadLine();

                int[] _line = line.Split(' ').Select(x => Int32.Parse(x)).ToArray();

                int H = _line[0], W = _line[1];

                int[][] altitudes = new int[H][];

                for (int i = 0; i < H; ++i)
                    altitudes[i] = iFile.ReadLine().Split(' ').Select(x => Int32.Parse(x)).ToArray();

                char name = 'a';

                char[,] map = new char[H,W];
                for (int i = 0; i < H; ++i)
                    for (int j = 0; j < W; ++j)
                        map[i,j] = '?';

                for(int ch=0; ch<H; ++ch)
                    for (int cw = 0; cw < W; ++cw)
                    {
                        Stack<KeyValuePair<int, int>> stack = new Stack<KeyValuePair<int, int>>();

                        int h = ch, w = cw;

                        while (map[h,w] == '?') // неизвестный бассейн, ищем куда стекает вода
                        {
                            // North, West, East, South, exactly in this order
                            int min = altitudes[h][w];
                            KeyValuePair<int, int>? minc = null;
                            for(int dh=-1; dh<=1; ++dh)
                                for(int dw=-1; dw<=1; ++dw)
                                    if(Math.Abs(dh) != Math.Abs(dw))  // North, West, East or South
                                        if(h+dh>=0 && h+dh<H && w+dw>=0 && w+dw<W) // in bounds
                                            if (altitudes[h + dh][w + dw] < min)
                                            {
                                                min = altitudes[h + dh][w + dw];
                                                minc = new KeyValuePair<int, int>(h + dh, w + dw);
                                            }

                            if (min == altitudes[h][w]) // никуда не стекает, это новый бассейн, именуем
                            {
                                map[h, w] = name;
                                ++name;
                            }
                            else // ищем дальше
                            {
                                stack.Push(new KeyValuePair<int, int>(h, w));
                                h = ((KeyValuePair<int, int>)minc).Key;
                                w = ((KeyValuePair<int, int>)minc).Value;
                            }

                        }

                        // бассейн найден, запоминаем его для всего пути
                        foreach (KeyValuePair<int, int> kvp in stack)
                            map[kvp.Key, kvp.Value] = map[h, w];


                    }

                Console.WriteLine("Case #{0}:", tn);

                oFile.WriteLine("Case #{0}:", tn);

                for (int h = 0; h < H; ++h)
                {
                    for (int w = 0; w < W; ++w)
                    {
                        if (w != 0)
                            oFile.Write(' ');

                        oFile.Write(map[h, w]);
                    }
                    oFile.WriteLine();
                }
            }

            iFile.Close();
            oFile.Close();
        }
    }
}
