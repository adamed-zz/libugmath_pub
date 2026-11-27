
















namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

struct TransformMatrix {
    double m[16];
};


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


bool MTX3_ortho_normalize(UGS::Math::Matrix3* matrix);

char MTX4_ortho_normalize(UGS::Math::TransformMatrix* m) {
    const double vals[9] = { m->m[0], m->m[1], m->m[2],
                             m->m[4], m->m[5], m->m[6],
                             m->m[8], m->m[9], m->m[10] };
    UGS::Math::Matrix3Copy rotation(vals);
    char status;
    if (MTX3_ortho_normalize(
            reinterpret_cast<UGS::Math::Matrix3*>(&rotation))) {
        const double* r = rotation.m;
        m->m[0] = r[0];
        m->m[1] = r[1];
        m->m[2] = r[2];
        m->m[4] = r[3];
        m->m[5] = r[4];
        m->m[6] = r[5];
        m->m[8] = r[6];
        m->m[9] = r[7];
        m->m[10] = r[8];
        status = 1;
    } else {
        status = 0;
    }
    return status;
}
