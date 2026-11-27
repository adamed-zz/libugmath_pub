












#include "iacomparameteraccess_shared.h"
namespace UGS {
namespace Math {



struct Point3
{
    double x;
    double y;
    double z;
};


struct Matrix3
{
    double m[3][3];
};

}

namespace Part {








}
}



struct CSYS_s
{
    UGS::Math::Point3 origin;
    UGS::Math::Matrix3 matrix;
};

void WCS_ask_coordinate_system(struct CSYS_s* out)
{
    UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    out->origin = *(UGS::Math::Point3 const*)p->p42();
    out->matrix = *(UGS::Math::Matrix3 const*)p->p39();
}
