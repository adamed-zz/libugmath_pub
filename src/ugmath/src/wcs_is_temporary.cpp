




















#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

bool WCS_is_temporary()
{
    return UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p57() == 1;
}
