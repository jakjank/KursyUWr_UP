using System.Configuration;

namespace Ex5
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            bool runThis = bool.Parse(ConfigurationManager.AppSettings["doRun"]);
            
            if(runThis){
                Application.Run(new Form1());
            }
        }
    }
}