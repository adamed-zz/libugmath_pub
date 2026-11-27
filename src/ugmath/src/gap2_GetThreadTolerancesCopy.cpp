#include <cstddef>
#include <memory>
#include <new>






























namespace UGS {
namespace Memory {

struct SharedPtrCountedBase;

template <class T>
class SharedPtr {
public:
    T* ptr;
    SharedPtrCountedBase* ctl;
};

}

namespace Math {

class ITolerances {
public:
    virtual ~ITolerances();
    virtual double GetA() const = 0;
    virtual double GetB() const = 0;
    virtual int GetC() const = 0;
};


class ThreadTolerances : public ITolerances {
public:
    double a;
    double b;
    int c;
    int pad_;
    unsigned char flag_;

    explicit ThreadTolerances(const ITolerances* src)
        : a(src->GetA()), b(src->GetB()), c(src->GetC()), pad_(0), flag_(1) {}

    double GetA() const override { return a; }
    double GetB() const override { return b; }
    int GetC() const override { return c; }
};

}
}



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
namespace Memory {



struct SharedPtrCountedBase {
    void* vt;
    unsigned int strong;
    unsigned int weak;
};

}

namespace Math {





extern std::unique_ptr<ITolerances> g_default_tolerances;
extern thread_local std::unique_ptr<ITolerances> s_thread_tolerances;

UGS::Memory::SharedPtr<ITolerances> GetThreadTolerancesCopy()
{
    ITolerances* src;
    if (UGS::System::Threading::Thread::IsLogicalMainThread()) {
        src = g_default_tolerances.get();
    } else {
        src = s_thread_tolerances.get();
        if (!src) {
            ERROR_raise(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Tolerances.cxx",
                89,
                4360002,
                "no tolerances set up for this thread - consider calling "
                "SetThreadTolerances during thread set up");
        }
    }
    UGS::Memory::SharedPtr<ITolerances> out;
    out.ptr = nullptr;
    out.ctl = nullptr;
    if (!src) return out;
    ThreadTolerances* obj = new (std::nothrow) ThreadTolerances(src);
    UGS::Memory::SharedPtrCountedBase* ctl =
        new (std::nothrow) UGS::Memory::SharedPtrCountedBase;
    if (!obj || !ctl) {
        delete obj;
        delete ctl;
        return out;
    }
    ctl->vt = nullptr;
    ctl->strong = 1;
    ctl->weak = 1;
    out.ptr = obj;
    out.ctl = ctl;
    return out;
}

}
}
