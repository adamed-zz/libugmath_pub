#include "kits/b18_kit/b18_support.h"


void mapvwa(double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    double *m = b18_acom_mtx(p);
    double x = a1[0];
    double y = a1[1];
    double z = a1[2];
    a2[0] = x * m[0] + y * m[3] + z * m[6];
    a2[1] = x * m[1] + y * m[4] + z * m[7];
    a2[2] = x * m[2] + y * m[5] + z * m[8];
}
