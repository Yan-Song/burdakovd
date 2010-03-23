using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using Util;

namespace Nakamar
{
    public class LoaderManager
    {
        private List<Loader> loaders = new List<Loader>();

        public LoaderManager(string assemblyPath)
        {
            // Make sure we actually have a path to work with.
            if (string.IsNullOrEmpty(assemblyPath))
            {
                throw new ArgumentNullException("assemblyPath");
            }

            try
            {
                // Load the assembly, and get the types contained
                // within it.
                Assembly asm = Assembly.LoadFrom(assemblyPath);
                Type[] types = asm.GetTypes();

                foreach (Type type in types)
                {
                    try
                    {
                        // Here's some fairly simple stuff.
                        if (type.IsClass && type.IsSubclassOf(typeof(Loader)))
                        {
                            // Create the State using the Activator class.
                            var tempLoader = (Loader)Activator.CreateInstance(type, new object[] {});
                            // Make sure we're not using two of the same state.
                            // (That would be bad!)
                            if (!loaders.Contains(tempLoader))
                            {
                                loaders.Add(tempLoader);
                            }
                        }
                    }
                    catch (TargetInvocationException t)
                    {
                        Logger.LogError("LoaderManager: " + type.Name, t.InnerException.Message);
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError("LoaderManager: " + type.Name, ex.Message);
                    }
                }
            }
            catch (Exception ex)
            {
                Logger.LogError("LoaderManager", ex.Message);
            }
        }

        public string WhyShouldntStartWow()
        {
            foreach(var loader in loaders)
            {
                var result = loader.WhyShouldNotStartWoW();

                if (result != null)
                    return result;
            }

            return null;
        }

        public void Prepare()
        {
            loaders.ForEach(loader => loader.PrepareForStartWoW());
        }
    }
}
