








#include <cmath>
#include <cstddef>

#include "ugmath/point3.h"
#include "ugmath/vector3.h"
#include "ugmath/mtx4.h"

namespace UGS {
namespace Math {
struct Vector2 {
    double x, y;
};
}
}


using P3 = UGS::Math::Point3;
using V3 = UGS::Math::Vector3;
using V2 = UGS::Math::Vector2;
using M4 = UGS::Math::TransformMatrix;

void ARC_SPLINE_adjust_vec_on_pln(bool flag, V3* normal, V3* vec);
void LSFIT_cre_local_csys(P3* origin, V3* xaxis, V3* zaxis, M4* m, M4* local);
double* sub_18005E110(double* out, double* in, double* m);
int VEC2_unitize(const V2* v, double tol, double* len, V2* out);
int VEC3_unitize(const V3* v, double tol, double* len, V3* out);
double ARC_SPLINE_ask_inclination_angle_from_tan_2d(const V2* v);
void ARC_SPLINE_rotate_vector_around_axis(V3* v, V3* axis, double angle, bool flag, V3* out);
double LSFIT_ask_dist_pt_to_line_3d(P3* p, P3* origin, V3* dir, double tol, P3* foot,
                                    double* dist);
void ARC_SPLINE_transform_vec_3d(V3* v, M4* m, bool flag, V3* out);


void* SM_alloc(size_t n);
void SM_free(void* p);

namespace {
const double kUnitTol = 1.0e-10;

V3 kAxis = {0.0, 0.0, 1.0};
P3 kZero = {0.0, 0.0, 0.0};
}

extern "C" void sub_180053800(int npts, const double* ptsRaw, const double* tol, int flag,
                              const double* originRaw, double a6, const double* normalRaw,
                              const double* vecRaw, double* out1, double* out2, double* out3,
                              double* angles, double* outpts) {
    P3* pts = reinterpret_cast<P3*>(const_cast<double*>(ptsRaw));
    P3* origin = reinterpret_cast<P3*>(const_cast<double*>(originRaw));
    V3* normal = reinterpret_cast<V3*>(const_cast<double*>(normalRaw));
    V3* vec = reinterpret_cast<V3*>(const_cast<double*>(vecRaw));
    const double tol0 = tol[0];
    const double tol1 = tol[1];


    out1[0] = 0.0;
    out1[1] = 0.0;
    out1[2] = 0.0;
    out2[0] = 0.0;
    out2[1] = 0.0;
    out2[2] = 0.0;
    out3[0] = 0.0;
    out3[1] = 0.0;
    out3[2] = 0.0;
    angles[0] = 360.0;
    angles[1] = -360.0;
    for (int i = 0; i < 6; ++i) outpts[i] = 0.0;

    double minang = 360.0;
    double maxang = -360.0;
    double firstang = -360.0;
    double mindist = 1.0e19;
    double maxdist = -1.0e19;
    int minidx = -1;
    int maxidx = -1;
    double scratchLen = 0.0;
    double dist = 0.0;
    P3 foot = {0.0, 0.0, 0.0};
    P3 v75 = {0.0, 0.0, 0.0};
    P3 v77 = {0.0, 0.0, 0.0};
    double tmpOut[3] = {0.0, 0.0, 0.0};

    V3 v24;
    if (flag) {
        v24.x = -vec->x;
        v24.y = -vec->y;
        v24.z = -vec->z;
    } else {
        v24.x = vec->x;
        v24.y = vec->y;
        v24.z = vec->z;
    }
    out3[0] = v24.x;
    out3[1] = v24.y;
    out3[2] = v24.z;

    ARC_SPLINE_adjust_vec_on_pln(1, normal, &v24);

    V3 v63;
    v63.x = v24.z * normal->y - v24.y * normal->z;
    v63.y = v24.x * normal->z - normal->x * v24.z;
    v63.z = normal->x * v24.y - v24.x * normal->y;
    VEC3_unitize(&v63, kUnitTol, &scratchLen, &v63);

    M4 M;
    M4 Mlocal;
    LSFIT_cre_local_csys(origin, &v63, normal, &M, &Mlocal);
    out3[0] = M.m[0];
    out3[1] = M.m[1];
    out3[2] = M.m[2];

    P3* v32 = static_cast<P3*>(SM_alloc(static_cast<size_t>(24) * npts));
    P3* v33 = static_cast<P3*>(SM_alloc(static_cast<size_t>(24) * npts));

    for (int i = 0; i < npts; ++i) {
        sub_18005E110(tmpOut, &pts[i].x, &Mlocal.m[0]);
        v32[i].x = tmpOut[0];
        v32[i].y = tmpOut[1];
        v32[i].z = tmpOut[2];

        V2 p2;
        p2.x = v32[i].x;
        p2.y = v32[i].y;
        VEC2_unitize(&p2, kUnitTol, &scratchLen, &p2);

        if (!(tol0 >= scratchLen)) {
            const double ang = ARC_SPLINE_ask_inclination_angle_from_tan_2d(&p2);
            V3 v67;
            v67.x = v32[i].x;
            v67.y = v32[i].y;
            v67.z = v32[i].z;
            V3 v69;
            ARC_SPLINE_rotate_vector_around_axis(&v67, &kAxis, -ang, 0, &v69);
            v33[i].x = v69.x;
            v33[i].y = v69.y;
            v33[i].z = v69.z;
            minang = fmin(ang, minang);
            maxang = fmax(ang, maxang);
            if (firstang <= -360.0 && !(fabs(ang - minang) <= kUnitTol) &&
                !(fabs(ang - maxang) <= kUnitTol))
                firstang = ang;
        } else {
            v33[i].x = 0.0;
            v33[i].y = 0.0;
            v33[i].z = 0.0;
        }
    }

    if (tol1 >= fabs(minang - 0.0)) minang = 0.0;
    if (tol1 >= fabs(maxang - 360.0)) maxang = 360.0;
    double second;
    if (!(firstang >= minang) || !(maxang >= firstang)) {
        second = minang;
        minang = maxang - 360.0;
    } else {
        second = maxang;
    }
    angles[0] = minang;
    angles[1] = second;

    const double v45 = a6 + 0.0;
    const double v46 = 0.0 * a6 + 0.0;

    for (int i = 0; i < npts; ++i) {
        LSFIT_ask_dist_pt_to_line_3d(&v33[i], &kZero, &kAxis, tol0, &foot, &dist);
        if (mindist > dist) {
            mindist = dist;
            minidx = i;
        }
        if (dist > maxdist) {
            maxdist = dist;
            maxidx = i;
        }
    }
    LSFIT_ask_dist_pt_to_line_3d(&v33[minidx], &kZero, &kAxis, tol0, &v75, &dist);
    LSFIT_ask_dist_pt_to_line_3d(&v33[maxidx], &kZero, &kAxis, tol0, &v77, &dist);

    double w = v46 * M.m[7] + v45 * M.m[3] + v46 * M.m[11] + M.m[15];
    const double p1 = v46 * M.m[5] + v45 * M.m[1] + v46 * M.m[9] + M.m[13];
    const double p2v = v45 * M.m[2] + v46 * M.m[6] + v46 * M.m[10] + M.m[14];
    if (w < 1.0e-19) {
        if (w < 0.0)
            w = fmin(-1.0e-19, w);
        else
            w = 1.0e-19;
    }
    out1[0] = (v46 * M.m[4] + v45 * M.m[0] + v46 * M.m[8] + M.m[12]) / w;
    out1[1] = p1 / w;
    out1[2] = p2v / w;

    ARC_SPLINE_transform_vec_3d(&kAxis, &M, 1, reinterpret_cast<V3*>(out2));

    sub_18005E110(tmpOut, &v75.x, &M.m[0]);
    outpts[0] = tmpOut[0];
    outpts[1] = tmpOut[1];
    outpts[2] = tmpOut[2];
    sub_18005E110(tmpOut, &v77.x, &M.m[0]);
    outpts[3] = tmpOut[0];
    outpts[4] = tmpOut[1];
    outpts[5] = tmpOut[2];

    if (v32) SM_free(v32);
    if (v33) SM_free(v33);
}
