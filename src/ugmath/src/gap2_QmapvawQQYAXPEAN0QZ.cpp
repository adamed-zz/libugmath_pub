#include "kits/b18_kit/b18_support.h"


void mapvaw(double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    double *m = b18_acom_mtx(p);
    double y = a1[1];
    double x = a1[0];
    double z = a1[2];
    a2[0] = x * m[0] + y * m[1] + z * m[2];
    a2[1] = x * m[3] + y * m[4] + z * m[5];
    a2[2] = x * m[6] + y * m[7] + z * m[8];
}
