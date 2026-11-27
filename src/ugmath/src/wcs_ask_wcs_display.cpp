



























#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

void WCS_ask_wcs_display(int* out)
{
    *out = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p57() != 0;
}
