




















#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {




}
}

void WCS_set_linked_to_view(bool linked)
{
    UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p56(linked);
}
