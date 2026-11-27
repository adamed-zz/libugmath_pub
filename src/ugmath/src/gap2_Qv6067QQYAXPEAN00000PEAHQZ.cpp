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

void vunt3(const double* a, int* ok, double* out);
void vcru3(const double* a, const double* b, int* ok, double* out);
int MTX3_init_y_z(const Vector3* y, const Vector3* z, Matrix3* out);
void h100(const double* a, const double* m, double* out);
void h110(const double* src, double* dst);
void h600(const double* a, const double* b, const double* c, const double* d, int* code,
          double* out);

void v6067(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6, int* a7)
{
    double* v10;
    double v16, v17, v18, v19, v20, v21;
    double v22[3];
    double v25[3];
    double v26[3];
    double v27[3];
    double v28[3];
    double v29[3];
    double v30[10];

    v10 = a5;
    volatile double* p2 = v22;
    p2[0] = *a1 - *a2;
    p2[1] = a1[1] - a2[1];
    p2[2] = a1[2] - a2[2];
    vunt3(v22, reinterpret_cast<int*>(&a5), a5);
    if (!*reinterpret_cast<int*>(&a5))
        goto LABEL_5;
    p2[0] = *a3 - *a4;
    p2[1] = a3[1] - a4[1];
    p2[2] = a3[2] - a4[2];
    vcru3(v10, v22, reinterpret_cast<int*>(&a5), v10 + 6);
    if (!*reinterpret_cast<int*>(&a5))
        goto LABEL_5;
    v16 = v10[0];
    v17 = v10[8];
    v18 = v10[6];
    v19 = v10[7];
    v20 = v18 * v10[2];
    v21 = v18 * v10[1] - v10[0] * v19;
    v10[3] = v19 * v10[2] - v17 * v10[1];
    v10[4] = v16 * v17 - v20;
    v10[5] = v21;
    if (MTX3_init_y_z(reinterpret_cast<const Vector3*>(v10 + 3),
                      reinterpret_cast<const Vector3*>(v10 + 6),
                      reinterpret_cast<Matrix3*>(v10)))
    {
        h100(a1, v10, v25);
        h100(a2, v10, v29);
        h100(a3, v10, v28);
        h100(a4, v10, v27);
        h600(v25, v29, v28, v27, reinterpret_cast<int*>(&a5), v26);
        v26[2] = v25[2];
        h110(v10, v30);
        h100(v26, v30, a6);
        *a7 = 1;
    }
    else
    {
    LABEL_5:
        *a7 = 2;
    }
}
