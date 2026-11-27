






#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector2
{
    double x, y;
};
struct Vector3
{
    double x, y, z;
};
struct Point3
{
    double x, y, z;
};
struct TransformMatrix
{
    double m[4][4];
};
}
}

using UGS::Math::Point3;
using UGS::Math::TransformMatrix;
using UGS::Math::Vector2;
using UGS::Math::Vector3;


int VEC3_unitize(const Vector3* u, double tol, double* len_out, Vector3* out);
void LSFIT_cre_local_csys(Point3* origin, Vector3* dir, Vector3* axis,
                          TransformMatrix* xform, TransformMatrix* inv);
double* sub_18005E110(double* a1, double* a2, double* a3);
int VEC2_unitize(const Vector2* u, double tol, double* len_out, Vector2* out);
double ARC_SPLINE_ask_inclination_angle_from_tan_2d(const Vector2* v);
void ARC_SPLINE_rotate_vector_around_axis(Vector3* vector, Vector3* axis, double angle_deg,
                                          bool normalize, Vector3* out);
void* SM_alloc(unsigned __int64 n);
void SM_free(void* p);

void sub_180050820(int a1, const Point3* a2, const double* a3, __int64 a4, Vector3* a5,
                   Point3* a6, const double* a7, double* a8)
{
    (void)a4;

    double v11 = -360.0;
    double v12 = 360.0;
    double v13 = -360.0;

    a8[0] = 360.0;
    a8[1] = -360.0;


    double nrm[3];
    nrm[0] = a7[2] * a5->y - a7[1] * a5->z;
    nrm[1] = a7[0] * a5->z - a5->x * a7[2];
    nrm[2] = a5->x * a7[1] - a7[0] * a5->y;

    double len_stub = 0.0;
    VEC3_unitize((const Vector3*)nrm, 1.0e-10, &len_stub, (Vector3*)nrm);

    TransformMatrix xform;
    TransformMatrix inv;
    LSFIT_cre_local_csys(a6, (Vector3*)nrm, a5, &xform, &inv);

    const __int64 v9 = (__int64)a1;
    char* v17 = (char*)SM_alloc((unsigned __int64)(24 * v9));
    char* v18 = (char*)SM_alloc((unsigned __int64)(24 * v9));

    int i = 0;
    while (i < (int)v9)
    {
        double scratch[4];
        double* r = sub_18005E110(scratch, (double*)((const char*)a2 + 24 * (__int64)i),
                                   &inv.m[0][0]);
        double* p17 = (double*)(v17 + 24 * (__int64)i);
        p17[0] = r[0];
        p17[1] = r[1];
        p17[2] = r[2];

        Vector3 v34;
        v34.x = p17[0];
        v34.y = p17[1];
        v34.z = p17[2];

        Vector2 v31;
        v31.x = p17[0];
        v31.y = p17[1];

        double v32 = 0.0;
        VEC2_unitize(&v31, 1.0e-10, &v32, &v31);


        if (!(*a3 >= v32))
        {
            double v23 = ARC_SPLINE_ask_inclination_angle_from_tan_2d(&v31);
            Vector3 axis01;
            axis01.x = 0.0;
            axis01.y = 0.0;
            axis01.z = 1.0;
            Vector3 v36;
            ARC_SPLINE_rotate_vector_around_axis(&v34, &axis01, -v23, false, &v36);

            double* p18 = (double*)(v18 + 24 * (__int64)i);
            p18[0] = v36.x;
            p18[1] = v36.y;
            p18[2] = v36.z;


            v12 = (v23 < v12) ? v23 : v12;
            v11 = (v23 > v11) ? v23 : v11;


            if (v13 <= -360.0 && !(fabs(v23 - v12) <= 1.0e-10) &&
                !(fabs(v23 - v11) <= 1.0e-10))
                v13 = v23;
            ++i;
        }
        else
        {
            double* p18 = (double*)(v18 + 24 * (__int64)i);
            p18[0] = 0.0;
            p18[1] = 0.0;
            p18[2] = 0.0;
            ++i;
        }
    }

    const double v27 = a3[1];
    if (v27 >= fabs(v12))
        v12 = 0.0;
    if (v27 >= fabs(v11 - 360.0))
        v11 = 360.0;


    if (!(v13 >= v12) || !(v11 >= v13))
    {
        const double v28 = v12;
        v12 = v11 - 360.0;
        a8[0] = v12;
        a8[1] = v28;
    }
    else
    {
        a8[0] = v12;
        a8[1] = v11;
    }

    if (v17)
        SM_free(v17);
    if (v18)
        SM_free(v18);
}
