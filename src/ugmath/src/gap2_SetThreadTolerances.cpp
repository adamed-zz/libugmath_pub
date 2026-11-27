#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <new>




























namespace UGS {
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


extern thread_local std::unique_ptr<ITolerances> s_thread_tolerances;

void SetThreadTolerances(const ITolerances* src)
{


    ThreadTolerances* fresh = new (std::nothrow) ThreadTolerances(src);
    s_thread_tolerances.reset(fresh);
}

}
}
