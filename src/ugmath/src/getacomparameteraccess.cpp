










#include "iacomparameteraccess_shared.h"
#include <intrin.h>




__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* message, ...);
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line, const char* format, ...);

namespace UGS {
namespace System {
namespace Threading {

class Thread
{
public:
    __declspec(dllimport) static bool IsLogicalMainThread();
};

}
}
}

namespace UGS {
namespace Part {




}
}



unsigned long long libugmath_dev_acom_instance = 0;

UGS::Part::IAcomParameterAccess* UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()
{
    if (!libugmath_dev_acom_instance)
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Part_IAcomParameterAccess.cxx",
            46,
            "Could not find the GetAcomParameterAccess class instance - not registered yet");
        __debugbreak();
        __assume(0);
    }
    if (MACH__checking_level && !UGS::System::Threading::Thread::IsLogicalMainThread())
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Part_IAcomParameterAccess.cxx",
            49, "%s", "System::Threading::Thread::IsLogicalMainThread()");
    return (UGS::Part::IAcomParameterAccess*)libugmath_dev_acom_instance;
}
