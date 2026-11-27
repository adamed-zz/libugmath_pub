#include "kits/b18_kit/b18_support.h"


void map13(const double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    const double *origin = b18_acom_pt(p);
    double v8[3];
    v8[0] = a1[0] - origin[0];
    v8[1] = a1[1] - origin[1];
    v8[2] = a1[2] - origin[2];
    map11(v8, a2);
}
