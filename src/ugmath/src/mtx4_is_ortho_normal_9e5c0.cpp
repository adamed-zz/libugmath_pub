
























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



namespace UGS {
namespace Math {



struct Matrix3Copy {
    double m[9];
    Matrix3Copy(const double (&v)[9]) {
        for (int i = 0; i < 9; ++i) {
            m[i] = v[i];
        }
    }
};

}
}



bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* matrix, double tolerance);

bool MTX4_is_ortho_normal(const UGS::Math::TransformMatrix* m, double tolerance) {
    const double vals[9] = { m->m[0], m->m[1], m->m[2],
                             m->m[4], m->m[5], m->m[6],
                             m->m[8], m->m[9], m->m[10] };
    UGS::Math::Matrix3Copy rotation(vals);
    return MTX3_is_ortho_normal(
        reinterpret_cast<const UGS::Math::Matrix3*>(&rotation), tolerance);
}
