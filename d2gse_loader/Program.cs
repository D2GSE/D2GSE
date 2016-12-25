using System;
using System.IO;

namespace d2gse_loader
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var injector = new Injector())
            {
                try
                {
                    var basePath = AppDomain.CurrentDomain.BaseDirectory;
                    injector.StartProcess(Path.Combine(basePath, "D2GS.exe"));
                    injector.Inject(Path.Combine(basePath, "d2gse.dll"));
                    injector.WaitForRemoteThread();
                    injector.ResumeProcess();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Exception:\n\t{0}", ex.Message);
                }
            }
        }
    }
}
