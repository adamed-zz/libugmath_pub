


































#include "ugmath/tolerance.h"

#include <memory>




namespace UGS { namespace System { namespace Threading {
class Thread
{
public:
    static __declspec(dllimport) bool IsLogicalMainThread(void);
};
}}}




__declspec(dllimport) __declspec(noreturn)
void ERROR_raise(char const* file, int line, int code, char const* message, ...);

namespace UGS {
namespace Math {


ITolerances::~ITolerances() = default;


std::unique_ptr<ITolerances> g_default_tolerances;



thread_local std::unique_ptr<ITolerances> s_thread_tolerances;

ITolerances* GetThreadTolerances(void)
{
    if (UGS::System::Threading::Thread::IsLogicalMainThread())
        return g_default_tolerances.get();

    if (!s_thread_tolerances)
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Tolerances.cxx",
                    78,
                    4360002,
                    "no tolerances set up for this thread - consider calling SetThreadTolerances during thread set up");

    return s_thread_tolerances.get();
}

}
}
