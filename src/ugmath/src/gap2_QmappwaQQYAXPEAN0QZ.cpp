#include "kits/b18_kit/b18_support.h"


void mappwa(double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    mapvwa(a1, a2);
    const double *origin = b18_acom_pt(p);
    a2[0] = origin[0] + a2[0];
    a2[1] = origin[1] + a2[1];
    a2[2] = origin[2] + a2[2];
}
