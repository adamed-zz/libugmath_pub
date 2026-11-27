#include "kits/b18_kit/b18_support.h"


void mappaw(double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    const double *origin = b18_acom_pt(p);
    a2[0] = a1[0] - origin[0];
    a2[1] = a1[1] - origin[1];
    a2[2] = a1[2] - origin[2];
    mapvaw(a2, a2);
}
