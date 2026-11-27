






#include <math.h>

namespace UGS
{
namespace Math
{
struct Point2
{
    double x, y;
};
struct Point3
{
    double x, y, z;
};
struct Vector3
{
    double x, y, z;
};
struct TransformMatrix
{
    double m[4][4];
};
}
}

using UGS::Math::Point2;
using UGS::Math::Point3;
using UGS::Math::TransformMatrix;
using UGS::Math::Vector3;


void ARC_SPLINE_adjust_vec_on_pln(bool unitize, Vector3* n, Vector3* v);
void LSFIT_cre_local_csys(Point3* origin, Vector3* dir, Vector3* axis,
                          TransformMatrix* xform, TransformMatrix* inv);
double* sub_18005E110(double* a1, double* a2, double* a3);
void LSFIT_circle_to_points_2d(Point2* pts, int n, double tol, Point2* center,
                               double* radius, int* status, double* resid);
int VEC3_unitize(const Vector3* u, double tol, double* len_out, Vector3* out);
void* SM_alloc(unsigned __int64 n);
void SM_free(void* p);

void sub_180052030(__int64 a1, int a2, const Point3* a3, __int64 a4, double a5,
                   Vector3* a6, Point3* a7, Vector3* a8, Vector3* a9, double* a10)
{
    (void)a1;
    (void)a4;
    (void)a5;

    double len_stub = 0.0;
    int status = 0;



    double resid[4] = {0.0, 0.0, 0.0, 0.0};

    a10[0] = 0.0;
    a10[1] = 0.0;
    a10[2] = 0.0;


    a9->x = -a6->x;
    a9->y = -a6->y;
    a9->z = -a6->z;

    ARC_SPLINE_adjust_vec_on_pln(true, a8, a9);


    Vector3 nrm;
    double v16 = a9->x * a8->z - a8->x * a9->z;
    double v17 = a8->x * a9->y - a9->x * a8->y;
    nrm.x = a9->z * a8->y - a9->y * a8->z;
    nrm.y = v16;
    nrm.z = v17;
    VEC3_unitize(&nrm, 1.0e-10, &len_stub, &nrm);

    TransformMatrix xform;
    TransformMatrix inv;
    LSFIT_cre_local_csys(a7, &nrm, a8, &xform, &inv);


    a9->x = xform.m[0][0];
    a9->y = xform.m[0][1];
    a9->z = xform.m[0][2];


    Point2* buf = (Point2*)SM_alloc((unsigned __int64)(16 * (__int64)a2));
    if (a2 > 0)
    {
        double scratch[16];
        const Point3* p = a3;
        for (int i = 0; i < a2; ++i)
        {
            double* r = sub_18005E110(scratch, (double*)p, &inv.m[0][0]);
            buf[i].x = *(double*)r;
            buf[i].y = *((double*)r + 1);
            p = (const Point3*)((const char*)p + 24);
        }
    }

    Point2 center;
    center.x = 0.0;
    center.y = 0.0;
    LSFIT_circle_to_points_2d(buf, a2, 0.01, &center, &len_stub, &status, resid);
    SM_free(buf);

    const double cx = center.x;
    const double cy = center.y;

    double num0 = xform.m[1][0] * cy + xform.m[0][0] * cx + xform.m[2][0] * 0.0 + xform.m[3][0];
    double num1 = xform.m[1][1] * cy + xform.m[0][1] * cx + xform.m[2][1] * 0.0 + xform.m[3][1];
    double num2 = xform.m[1][2] * cy + xform.m[0][2] * cx + xform.m[2][2] * 0.0 + xform.m[3][2];
    double w = xform.m[1][3] * cy + xform.m[0][3] * cx + xform.m[2][3] * 0.0 + xform.m[3][3];



    if (w < 1.0e-19)
    {
        if (w < 0.0)
            w = fmin(-1.0e-19, w);
        else
            w = 1.0e-19;
    }

    num1 = num1 / w;
    num2 = num2 / w;
    num0 = num0 / w;
    a10[0] = num0;
    a10[1] = num1;
    a10[2] = num2;
}
