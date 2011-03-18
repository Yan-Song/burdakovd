using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace Util
{
    public class ConfigWTF : Dictionary<string, string>
    {
        readonly Regex lineEx = new Regex("^SET (?<key>[^ ]+) \\\"(?<value>.*)\\\"");
        string filename;

        public ConfigWTF()
        {
        }

        public ConfigWTF(string filename)
        {
            Load(filename);
        }

        /// <summary>
        /// читает настройки из файла
        /// </summary>
        /// <param name="filename"></param>
        public void Load(string filename)
        {
            this.Clear();
            this.filename = filename;
            foreach (string line in File.ReadAllLines(filename).Where(line => !string.IsNullOrEmpty(line)))
            {
                var match = lineEx.Match(line);
                Debug.Assert(match.Success);
                this[match.Groups["key"].ToString()] = match.Groups["value"].ToString();
            }
        }

        public void Save()
        {
            string[] lines = this.Select(kvp => string.Format("SET {0} \"{1}\"", kvp.Key, kvp.Value)).ToArray();

            File.WriteAllLines(filename, lines);
        }
    }
}
