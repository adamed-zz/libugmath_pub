


namespace UGS {
namespace Math {
struct Vector3 {
    double x, y, z;
};
struct Matrix3 {
    double m[9];
};
}
}

using UGS::Math::Vector3;
using UGS::Math::Matrix3;

bool VEC3_is_parallel(const Vector3* a, const Vector3* b, double tol);
int VEC3_unitize(const Vector3* v, double tol, double* len, Vector3* out);
int MTX3_init(const Vector3* x, const Vector3* y, Matrix3* out);

void v6043(double* a1, double* a2, double* a3, double* a4, double* a5, int* a6)
{
    Vector3 v22, v24, v26, v16, v18, v20;
    v22.x = *a2 - *a1;
    v22.y = a2[1] - a1[1];
    v22.z = a2[2] - a1[2];
    v24.x = *a3 - *a1;
    v24.y = a3[1] - a1[1];
    v24.z = a3[2] - a1[2];
    int v13 = 0;
    if (!VEC3_is_parallel(&v22, &v24, 1.0e-10)) {
        v18.z = 0.0;
        v16.z = 0.0;
        v20.x = 0.0;
        v20.y = 0.0;
        v20.z = 0.0;
        v18.x = 0.0;
        v18.y = 0.0;
        v16.x = 0.0;
        v16.y = 0.0;
        double v28;
        if (VEC3_unitize(&v22, 1.0e-10, &v28, &v18) &&
            VEC3_unitize(&v24, 1.0e-10, &v28, &v16)) {
            v26.x = v16.z * v18.y - v16.y * v18.z;
            v26.y = v16.x * v18.z - v16.z * v18.x;
            v26.z = v16.y * v18.x - v16.x * v18.y;
            if (VEC3_unitize(&v26, 1.0e-10, &v28, &v20)) {
                v16.x = v20.y * v18.z - v20.z * v18.y;
                v16.y = v20.z * v18.x - v20.x * v18.z;
                v16.z = v20.x * v18.y - v20.y * v18.x;
                v13 = MTX3_init(&v18, &v16, reinterpret_cast<Matrix3*>(a4));
            }
        }
        a5[0] = a1[0];
        a5[1] = a1[1];
        a5[2] = a1[2];
    }
    *a6 = 2 - (v13 != 0);
}
