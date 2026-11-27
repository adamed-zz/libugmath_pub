#include "kits/b18_kit/b18_support.h"


void map12(const double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    double v8[3];
    map10(a1, v8);
    const double *origin = b18_acom_pt(p);
    a2[0] = v8[0] + origin[0];
    a2[1] = v8[1] + origin[1];
    a2[2] = v8[2] + origin[2];
}
