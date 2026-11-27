











#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

extern double EQ_ask_number_tolerance();

#include <math.h>

void h805(const double* a, const double* b, const int* mode, int* out)
{
    double tol;
    if (*mode == 0)
        tol = EQ_ask_number_tolerance();
    else if (*mode == 1)
        tol = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p01();
    else
        tol = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p04();
    *out = tol >= fabs(*a - *b);
}
