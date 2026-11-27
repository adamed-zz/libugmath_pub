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
int MTX3_init_x_y_z(const Vector3* x, const Vector3* y, const Vector3* z, Matrix3* out);

void v6043_normal(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6,
                  int* a7)
{
    Vector3 v17, v19, v21, v23, v25;
    v25.x = *a2 - *a1;
    v25.y = a2[1] - a1[1];
    v25.z = a2[2] - a1[2];
    v23.x = *a3 - *a1;
    v23.y = a3[1] - a1[1];
    v23.z = a3[2] - a1[2];
    int inited = 0;
    if (!VEC3_is_parallel(&v25, &v23, 1.0e-10)) {
        v21.z = 0.0;
        v19.z = 0.0;
        v17.x = 0.0;
        v17.y = 0.0;
        v17.z = 0.0;
        v21.x = 0.0;
        v21.y = 0.0;
        v19.x = 0.0;
        v19.y = 0.0;
        double v27;
        if (VEC3_unitize(reinterpret_cast<const Vector3*>(a4), 1.0e-10, &v27, &v17)) {
            if (!VEC3_unitize(&v25, 1.0e-10, &v27, &v21)) {
                if (!VEC3_unitize(&v23, 1.0e-10, &v27, &v19)) goto LABEL_10;
                v25.x = v17.z * v19.y - v17.y * v19.z;
                v25.y = v17.x * v19.z - v17.z * v19.x;
                v25.z = v17.y * v19.x - v17.x * v19.y;
                if (!VEC3_unitize(&v25, 1.0e-10, &v27, &v21)) goto LABEL_10;
                v19.x = v17.y * v21.z - v17.z * v21.y;
                v19.y = v17.z * v21.x - v17.x * v21.z;
                v19.z = v17.x * v21.y - v17.y * v21.x;
                goto LABEL_9;
            }
            v23.x = v17.y * v21.z - v17.z * v21.y;
            v23.y = v17.z * v21.x - v17.x * v21.z;
            v23.z = v17.x * v21.y - v17.y * v21.x;
            if (VEC3_unitize(&v23, 1.0e-10, &v27, &v19)) {
                v21.x = v17.z * v19.y - v17.y * v19.z;
                v21.y = v17.x * v19.z - v17.z * v19.x;
                v21.z = v17.y * v19.x - v17.x * v19.y;
            LABEL_9:
                inited = MTX3_init_x_y_z(&v21, &v19, &v17, reinterpret_cast<Matrix3*>(a5));
            }
        }
    LABEL_10:
        *reinterpret_cast<Vector3*>(a6) = *reinterpret_cast<const Vector3*>(a1);
    }
    *a7 = 2 - (inited != 0);
}
