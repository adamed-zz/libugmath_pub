












#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

void WCS_set_view_names_skeleton(unsigned int v)
{
    UGS::Part::IAcomParameterAccess* acom =
        UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    acom->p46(v);
}
