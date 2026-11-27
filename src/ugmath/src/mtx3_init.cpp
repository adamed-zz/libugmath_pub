



























namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

struct Matrix3 {
    double m[9];
};

}
}




int MTX3_init_impl(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                   UGS::Math::Matrix3* out, bool use_tol);

int MTX3_init(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
              UGS::Math::Matrix3* out) {
    return MTX3_init_impl(a1, a2, out, false);
}
