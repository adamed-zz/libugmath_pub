






#pragma once




namespace UGS {
namespace Math {

struct TransformMatrix {
    double m[16];
};

}
}



bool MTX4_is_equal(const UGS::Math::TransformMatrix* a,
                   const UGS::Math::TransformMatrix* b,
                   double tolerance);


bool MTX4_is_identity(const UGS::Math::TransformMatrix* m, double tolerance) {
    const UGS::Math::TransformMatrix identity = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    };
    return MTX4_is_equal(m, &identity, tolerance);
}
