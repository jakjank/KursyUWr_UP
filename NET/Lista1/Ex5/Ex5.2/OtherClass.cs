using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class OtherClass
{
    public static void checkInternal()
    {
        BaseClass obj = new BaseClass();
        obj.ImInternal();
        obj.ImPublic();
    }
}

