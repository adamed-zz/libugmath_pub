












#include "iacomparameteraccess_shared.h"
struct PLN3_s
{
    unsigned __int64 origin[3];
    unsigned __int64 normal[3];
};

namespace UGS {
namespace Part {





}
}

void WCS_ask_work_plane(struct PLN3_s* out)
{
    UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    unsigned __int64* a = (unsigned __int64*)p->p42();
    out->origin[0] = a[0];
    out->origin[1] = a[1];
    out->origin[2] = a[2];
    unsigned __int64* b = (unsigned __int64*)p->p39();
    out->normal[0] = b[6];
    out->normal[1] = b[7];
    out->normal[2] = b[8];
}
