












#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {





}
}

unsigned int WCS_ask_tag()
{
    UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    return p->p51();
}
