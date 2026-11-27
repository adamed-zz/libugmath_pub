













#pragma once
#include "iacomparameteraccess_shared.h"



namespace UGS {
namespace Math {



struct Point3
{
    double x;
    double y;
    double z;
};

}

namespace Part {








}
}


void WCS_ask_origin(struct UGS::Math::Point3* out)
{
    UGS::Math::Point3 const* p =
        (UGS::Math::Point3 const*)UGS::Part::IAcomParameterAccess::GetAcomParameterAccess()->p42();
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
}
