




#pragma once




namespace UGS {
namespace Math {

struct TransformMatrix {
    double m[16];
};



struct Matrix3 {
    double m[9];
};

}
}





bool MTX3_is_identity(const UGS::Math::Matrix3* matrix, double tolerance);



bool MTX4_is_rotation_null(UGS::Math::TransformMatrix* m) {
    UGS::Math::Matrix3 rotation;
    rotation.m[0] = m->m[0];
    rotation.m[1] = m->m[1];
    rotation.m[2] = m->m[2];
    rotation.m[3] = m->m[4];
    rotation.m[4] = m->m[5];
    rotation.m[5] = m->m[6];
    rotation.m[6] = m->m[8];
    rotation.m[7] = m->m[9];
    rotation.m[8] = m->m[10];
    return MTX3_is_identity(&rotation, 1.0e-10) != 0;
}
