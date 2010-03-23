using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Serialization;

namespace Util
{
    public class Serialization<TValue>
    {
        /// <summary>
        /// для тестирования
        /// </summary>
        /// <param name="o"></param>
        /// <returns></returns>
        public static string Serialize(TValue o)
        {
            StringWriter outStream = new StringWriter();
            XmlSerializer s = new XmlSerializer(typeof(TValue));

            s.Serialize(outStream, o);

            return outStream.ToString();
        }
    }
}
