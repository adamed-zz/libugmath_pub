












#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Math {


struct Vector3
{
    double x, y, z;
};

}

namespace Part {


struct AcomWcsData
{
    unsigned char pad[0x30];
    double x;
    double y;
    double z;
};




}
}

void WCS_ask_z_axis(UGS::Math::Vector3* out)
{
    UGS::Part::AcomWcsData* v = (UGS::Part::AcomWcsData*)UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p39();
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
}
