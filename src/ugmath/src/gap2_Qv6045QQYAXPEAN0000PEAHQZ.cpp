#include <emmintrin.h>

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

void h430(const double* a, const double* b, const double* c, double* out);
int VEC3_unitize(const Vector3* v, double tol, double* len, Vector3* out);
int MTX3_init_y_z(const Vector3* y, const Vector3* z, Matrix3* out);

void v6045(double* a1, double* a2, double* a3, double* a4, double* a5, int* a6)
{
    const double tol = 1.0e-10;
    int* v6 = a6;
    *a6 = 1;
    Vector3 v15;
    Vector3 v17;
    Vector3 v19;
    double v21[7];
    v19.z = 0.0;
    v17.z = 0.0;
    _mm_storeu_pd(&v19.x, _mm_setzero_pd());
    _mm_storeu_pd(&v17.x, _mm_setzero_pd());
    h430(a1, a2, a3, a5);
    v15.y = a3[1] - a5[1];
    v15.x = *a3 - *a5;
    v15.z = a3[2] - a5[2];
    if (!VEC3_unitize(&v15, tol, reinterpret_cast<double*>(&a6), &v19)) goto LABEL_3;
    v15.x = *a1 - *a2;
    v15.y = a1[1] - a2[1];
    v15.z = a1[2] - a2[2];
    VEC3_unitize(&v15, tol, reinterpret_cast<double*>(&a6), &v17);
    v21[0] = v17.y * v19.z - v17.z * v19.y;
    v21[1] = v17.z * v19.x - v17.x * v19.z;
    v21[2] = v17.x * v19.y - v17.y * v19.x;
    if (!MTX3_init_y_z(reinterpret_cast<const Vector3*>(v21), &v17,
                       reinterpret_cast<Matrix3*>(a4)))
    LABEL_3:
        *v6 = 2;
}
