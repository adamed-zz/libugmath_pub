






namespace UGS {
namespace Part {
class IAcomParameterAccess
{
public:
    virtual void v0() = 0;
    virtual double v1() = 0;
    virtual double v2() = 0;
    virtual double v3() = 0;
    virtual double v4() = 0;
    virtual double v5() = 0;
    virtual double v6() = 0;
    virtual double v7() = 0;
    static IAcomParameterAccess* GetAcomParameterAccess();
};
}
}

extern void h300(const double* a, const double* b, double* out);
extern void h806(const double* a, const double* b, double* tol, int* out);

static const double kZero306 = 0.0;

void h306(const double* a1, const double* a2, int* a3)
{
    double v5;
    double v6;
    h300(a1, a2, &v6);
    UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    v5 = p->v7();
    h806(&v6, &kZero306, &v5, a3);
}
