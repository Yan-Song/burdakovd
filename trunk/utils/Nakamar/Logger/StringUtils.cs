using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Util
{
    public sealed class StringUtils
    {
        public static String join<T>(T[] array, char separator)
        {
            StringBuilder builder = new StringBuilder();

            for (int i = 0; i < array.Length; ++i)
            {
                if (i != 0)
                {
                    builder.Append(separator);
                }

                builder.Append(array[i]);
            }

            return builder.ToString();
        }
    }
}
