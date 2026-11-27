

























#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Part {





}
}






extern unsigned long long libugmath_dev_acom_instance;

namespace UGS {
namespace Part {

void IAcomParameterAccess::RegisterMe(IAcomParameterAccess* p) const
{
    libugmath_dev_acom_instance = (unsigned long long)p;
}

}
}
