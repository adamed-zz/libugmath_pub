





#pragma once




namespace UGS {
namespace Math {

struct Point3 {
    double x;
    double y;
    double z;
};

struct Vector3 {
    double x;
    double y;
    double z;
};



struct TransformMatrix {
    double m[16];
};

}
}



struct CSYS_s {
    UGS::Math::Point3 origin;
    UGS::Math::Vector3 x_axis;
    UGS::Math::Vector3 y_axis;
    UGS::Math::Vector3 z_axis;
};


int MTX4_invert(const UGS::Math::TransformMatrix* src,
                UGS::Math::TransformMatrix* dst);
void MTX4_multiply(const UGS::Math::TransformMatrix* a,
                   const UGS::Math::TransformMatrix* b,
                   UGS::Math::TransformMatrix* out);
void MTX4_scaling(const UGS::Math::Point3* origin,
                  const UGS::Math::Vector3* scale,
                  UGS::Math::TransformMatrix* out);

UGS::Math::TransformMatrix MTX4_local_scaling(const CSYS_s& csys,
                                              const UGS::Math::Vector3& scale) {
    UGS::Math::Point3 origin;
    origin.x = 0.0;
    origin.y = 0.0;
    origin.z = 0.0;
    UGS::Math::TransformMatrix scaling;
    MTX4_scaling(&origin, &scale, &scaling);

    UGS::Math::TransformMatrix local;
    local.m[12] = 0.0;
    local.m[13] = 0.0;
    local.m[14] = 0.0;
    local.m[15] = 1.0;
    local.m[0] = csys.x_axis.x;
    local.m[1] = csys.x_axis.y;
    local.m[2] = csys.x_axis.z;
    local.m[3] = 0.0;
    local.m[4] = csys.y_axis.x;
    local.m[5] = csys.y_axis.y;
    local.m[6] = csys.y_axis.z;
    local.m[7] = 0.0;
    local.m[8] = csys.z_axis.x;
    local.m[9] = csys.z_axis.y;
    local.m[10] = csys.z_axis.z;
    local.m[11] = 0.0;

    MTX4_invert(&local, &local);
    local.m[3] = csys.origin.x;
    local.m[7] = csys.origin.y;
    local.m[11] = csys.origin.z;
    MTX4_invert(&local, &local);

    UGS::Math::TransformMatrix result;
    MTX4_multiply(&local, &scaling, &result);
    MTX4_invert(&local, &scaling);
    MTX4_multiply(&result, &scaling, &result);
    return result;
}
