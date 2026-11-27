



#include <cmath>

namespace UGS {
namespace Part {
struct IAcomParameterAccess {
    virtual ~IAcomParameterAccess();
    virtual double slot08();
    virtual double slot10();
    virtual double slot18();
    virtual double slot20();
    static IAcomParameterAccess* GetAcomParameterAccess();
};
}
}

double EQ_ask_number_tolerance();

static double ask_tol(const int* mode)
{
    const int m = *mode;
    if (m == 0)
        return EQ_ask_number_tolerance();
    if (m == 1)
        return UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->slot08();
    return UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->slot20();
}

void h809(double* a1, const double* a2, const int* a3, int* a4)
{
    *a4 = 1;
    if (!(*a1 >= *a2) || !(a2[1] >= *a1)) {
        double tol = ask_tol(a3);
        int hit = tol >= fabs(*a1 - *a2);
        if (!hit) {
            tol = ask_tol(a3);
            double hi = a2[1];
            hit = tol >= fabs(*a1 - hi);
            if (!hit)
                *a4 = hit;
            else
                *a1 = hi;
        } else {
            *a1 = *a2;
        }
    }
}
