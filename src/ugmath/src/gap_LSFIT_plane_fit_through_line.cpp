










#include <cmath>
#include <cstddef>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
    Vector3() {}
    Vector3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
};

struct Matrix3
{
    double m[9];
};


int VEC3_unitize(const Vector3* u, double eps, double* len_out, Vector3* out);
int MTX3_init_x_y_z(const Vector3* x, const Vector3* y, const Vector3* z, Matrix3* m);
void NR_ask_eigenvalues_jacobi(double** a, int n, int max_iter, double* const eval,
                               double** evec, int* nrot);
}
}

using UGS::Math::Matrix3;
using UGS::Math::Vector3;
using UGS::Math::MTX3_init_x_y_z;
using UGS::Math::NR_ask_eigenvalues_jacobi;
using UGS::Math::VEC3_unitize;



#ifdef LSFIT_SELFTEST
#define LSFIT_SM_IMPORT
#else
#define LSFIT_SM_IMPORT __declspec(dllimport)
#endif
LSFIT_SM_IMPORT void* SM_alloc(std::size_t n);
LSFIT_SM_IMPORT void SM_free(void* p);

int LSFIT_plane_fit_through_line(int num_pts, double* pts, double* wts,
                                 double* const lp0, double* const lp1,
                                 double* const plane, double* res)
{
    Vector3 zaxis;
    Vector3 xaxis{0.0, 0.0, 0.0};
    Vector3 ldir;
    Vector3 v;
    Vector3 yaxis{0.0, 0.0, 0.0};
    Vector3 n;
    Matrix3 mtx = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    double err = 0.0;
    double err2 = 0.0;
    double c1;
    double c2;
    double lam;

    plane[0] = 0.0;
    plane[1] = 0.0;
    plane[2] = 0.0;
    plane[3] = 0.0;
    *res = 0.0;

    ldir = Vector3(lp1[0] - lp0[0], lp1[1] - lp0[1], lp1[2] - lp0[2]);

    VEC3_unitize(&ldir, 1.0e-10, &err, &ldir);
    if (num_pts < 1 || fabs(err) <= 1.0e-10)
        return 1;

    if (num_pts == 1)
    {


        v.x = pts[0] - lp0[0];
        v.y = pts[1] - lp0[1];
        v.z = pts[2] - lp0[2];
        VEC3_unitize(&v, 1.0e-10, &err, &v);


        if (!(fabs(err) <= 1.0e-10))
        {
            n = Vector3(ldir.y * v.z - ldir.z * v.y,
                        ldir.z * v.x - ldir.x * v.z,
                        ldir.x * v.y - ldir.y * v.x);
            VEC3_unitize(&n, 1.0e-10, &err, &n);

            if (!(fabs(err) <= 1.0e-10))
            {
                plane[1] = n.y;
                plane[0] = n.x;
                plane[2] = n.z;
                plane[3] = n.y * lp0[1] + n.x * lp0[0] + n.z * lp0[2];
                return 0;
            }
        }
        return 1;
    }

    if (fabs(ldir.x) <= 1.0e-10 && fabs(ldir.y) <= 1.0e-10 && fabs(ldir.z) <= 1.0e-10)
        return 1;

    VEC3_unitize(&ldir, 1.0e-10, &err2, &xaxis);

    int k;
    if (fabs(xaxis.z) >= fabs(xaxis.y))
        k = (fabs(xaxis.z) >= fabs(xaxis.x)) ? 2 : 0;
    else
        k = (fabs(xaxis.y) >= fabs(xaxis.x)) ? 1 : 0;
    switch (k)
    {
    case 0:
        yaxis.x = -xaxis.y;
        yaxis.y = xaxis.x;
        break;
    case 1:
        yaxis.y = -xaxis.z;
        yaxis.z = xaxis.y;
        break;
    case 2:
        yaxis.z = -xaxis.x;
        yaxis.x = xaxis.z;
        break;
    }
    VEC3_unitize(&yaxis, 1.0e-10, &err2, &yaxis);

    zaxis = Vector3(yaxis.z * xaxis.y - yaxis.y * xaxis.z,
                    yaxis.x * xaxis.z - yaxis.z * xaxis.x,
                    yaxis.y * xaxis.x - yaxis.x * xaxis.y);
    VEC3_unitize(&zaxis, 1.0e-10, &err2, &zaxis);

    MTX3_init_x_y_z(&xaxis, &yaxis, &zaxis, &mtx);

    Vector3* tbuf = (Vector3*)SM_alloc(3 * num_pts * sizeof(double));

    for (long long i = 0; i < num_pts; ++i)
    {
        double dx = pts[3 * i] - lp0[0];
        double dy = pts[3 * i + 1] - lp0[1];
        double dz = pts[3 * i + 2] - lp0[2];
        tbuf[i] = Vector3(mtx.m[0] * dx + mtx.m[1] * dy + mtx.m[2] * dz,
                          mtx.m[3] * dx + mtx.m[4] * dy + mtx.m[5] * dz,
                          mtx.m[6] * dx + mtx.m[7] * dy + mtx.m[8] * dz);
    }

    double syy = 0.0;
    double syz = 0.0;
    double szz = 0.0;
    for (long long i = 0; i < num_pts; ++i)
    {
        double w = wts ? wts[i] : 1.0;
        double wy = tbuf[i].y * w;
        syz += wy * tbuf[i].z;
        syy += wy * tbuf[i].y;
        szz += tbuf[i].z * w * tbuf[i].z;
    }

    double evec[2][2] = {{0.0, 0.0}, {0.0, 0.0}};
    double* vrows[2];
    double* mrows[2];
    double eval[2];
    double mm[2][2];
    int nrot;
    mm[0][0] = syy;
    mm[0][1] = syz;
    mm[1][0] = syz;
    mm[1][1] = szz;
    mrows[0] = mm[0];
    mrows[1] = mm[1];
    vrows[0] = evec[0];
    vrows[1] = evec[1];
    NR_ask_eigenvalues_jacobi(mrows, 2, 60, eval, vrows, &nrot);

    if (eval[1] <= eval[0])
    {
        c1 = evec[0][1];
        lam = eval[1];
        c2 = evec[1][1];
    }
    else
    {
        c1 = evec[0][0];
        lam = eval[0];
        c2 = evec[1][0];
    }
    *res = lam / (double)num_pts;

    for (int j = 0; j < 3; ++j)
        ((double*)&n)[j] = 0.0 * mtx.m[j] + c1 * mtx.m[3 + j] + c2 * mtx.m[6 + j];
    VEC3_unitize(&n, 1.0e-10, &err, &n);

    plane[1] = n.y;
    plane[0] = n.x;
    plane[2] = n.z;
    plane[3] = n.y * lp0[1] + n.x * lp0[0] + n.z * lp0[2];

    SM_free(tbuf);
    return 0;
}
