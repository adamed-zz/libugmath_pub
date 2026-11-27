
























#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Math {
struct Matrix3;
}
}

namespace UGS {
namespace Part {




}
}

void WCS__set_matrix_values(const struct UGS::Math::Matrix3* m)
{
    UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p41(m);
}
