












#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Math {


struct Matrix3
{
    double m00, m01, m02;
    double m10, m11, m12;
    double m20, m21, m22;
};

}

namespace Part {



struct AcomWcsData
{
    double m00, m01, m02;
    double m10, m11, m12;
    double m20, m21, m22;
};




}
}

void WCS_ask_matrix(UGS::Math::Matrix3* out)
{
    UGS::Part::AcomWcsData* v = (UGS::Part::AcomWcsData*)UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p39();
    out->m00 = v->m00;
    out->m01 = v->m01;
    out->m02 = v->m02;
    out->m10 = v->m10;
    out->m11 = v->m11;
    out->m12 = v->m12;
    out->m20 = v->m20;
    out->m21 = v->m21;
    out->m22 = v->m22;
}
