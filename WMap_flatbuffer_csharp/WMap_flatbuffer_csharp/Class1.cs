using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Ini.Net;


namespace WMap_flatbuffer_csharp
{
    class CTestIni
    {
        public void fn()
        {
            var iniFile = new IniFile(@"D:\machine\ini\ult.ini");

            string companyName = iniFile.ReadString("App 1 Reject Code", "BadPkgLocate");
            int code = iniFile.ReadInteger("App 1 Reject Code", "BadPkgLocate");
            //string companyType = iniFile.ReadString("Company", "Type");
            //int companyEmployees = iniFile.ReadInteger("Company", "Employees");

        }
    }
}
