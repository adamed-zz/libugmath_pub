











#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

unsigned int WCS_ask_view_names_skeleton()
{
    UGS::Part::IAcomParameterAccess* acom =
        UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    return acom->p45();
}
