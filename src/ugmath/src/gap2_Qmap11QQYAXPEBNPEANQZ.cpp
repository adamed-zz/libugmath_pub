#include "kits/b18_kit/b18_support.h"



void map11(const double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    double *m = b18_acom_mtx(p);
    a2[0] = m[1] * a1[1] + m[0] * a1[0] + m[2] * a1[2];
    a2[1] = m[3] * a1[0] + m[4] * a1[1] + m[5] * a1[2];
    a2[2] = m[6] * a1[0] + m[7] * a1[1] + m[8] * a1[2];
}
