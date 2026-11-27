#include "kits/b18_kit/b18_support.h"



void v6051(double *a1, double *a2)
{
    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    b18_acom_take_vec(p, a1);
    b18_acom_put_vec(p, a2);
}
