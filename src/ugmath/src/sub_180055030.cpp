
















#include <math.h>

namespace UGS {
namespace Math {

struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};

}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;


int VEC3_unitize(const Vector3* v, double tol, double* len, Vector3* out);
void ERROR_internal(const char* file, int line, const char* msg, ...);

namespace {

const double kUnitTol = 1.0e-10;




void FarthestPoint(int n, const Point3* pts, Point3* out, double* outlen) {
    *outlen = 0.0;
    if (n == 1) {
        *out = pts[0];
        return;
    }
    int idx = 0;
    double best = pts[0].x * pts[0].x + pts[0].y * pts[0].y + pts[0].z * pts[0].z;
    for (int i = 1; i < n; ++i) {
        const double d = pts[i].x * pts[i].x + pts[i].y * pts[i].y + pts[i].z * pts[i].z;
        if (d > best) {
            best = d;
            idx = i;
        }
    }
    *out = pts[idx];
    *outlen = sqrt(best);
}

}

extern "C" void sub_180055030(int npts, const double* ptsRaw, double tol, Point3* part_a,
                              Point3* part_b, Vector3* normal, int* degen, int* special) {
    const Point3* pts = reinterpret_cast<const Point3*>(ptsRaw);
    *degen = 0;
    *special = 0;
    if (npts < 1) {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 820,
                       "There are no input points.");
        __debugbreak();
    }
    if (npts == 1) {
        *special = 1;
        *degen = 1;
        normal->x = 0.0;
        normal->y = 0.0;
        normal->z = 0.0;
        *part_a = pts[0];
        *part_b = pts[0];
        return;
    }
    if (npts == 2) {
        *special = 1;
        normal->x = 0.0;
        normal->y = 0.0;
        normal->z = 0.0;
        *part_a = pts[0];
        *part_b = pts[1];
        const double d2 = (part_a->y - part_b->y) * (part_a->y - part_b->y)
                        + (part_a->x - part_b->x) * (part_a->x - part_b->x)
                        + (part_a->z - part_b->z) * (part_a->z - part_b->z);
        if (tol > sqrt(d2)) *degen = 1;
        return;
    }

    double scratch = 0.0;
    FarthestPoint(npts, pts, part_a, &scratch);
    if (!(tol > scratch)) {
        Vector3 d = { part_a->x, part_a->y, part_a->z };
        VEC3_unitize(&d, kUnitTol, &scratch, &d);
        const double dx = d.x;
        const double dy = d.y;
        const double dz = d.z;

        double w = -(pts[0].y * dy + pts[0].x * dx + pts[0].z * dz);
        double best = (dy * w + pts[0].y) * (dy * w + pts[0].y)
                    + (w * dx + pts[0].x) * (w * dx + pts[0].x)
                    + (dz * w + pts[0].z) * (dz * w + pts[0].z);
        int idx = 0;
        for (int i = 1; i < npts; ++i) {
            const double wi = -(pts[i].y * dy + pts[i].x * dx + pts[i].z * dz);
            const double d2 = (dy * wi + pts[i].y) * (dy * wi + pts[i].y)
                            + (wi * dx + pts[i].x) * (wi * dx + pts[i].x)
                            + (dz * wi + pts[i].z) * (dz * wi + pts[i].z);
            if (d2 > best) {
                best = d2;
                idx = i;
            }
        }

        if (!(tol * tol > best)) {
            *part_b = pts[idx];
            Vector3 nrm;
            nrm.x = part_b->z * dy - part_b->y * dz;
            nrm.y = part_b->x * dz - part_b->z * dx;
            nrm.z = part_b->y * dx - part_b->x * dy;
            VEC3_unitize(&nrm, kUnitTol, &scratch, &nrm);
            *normal = nrm;
        } else {
            *special = 1;
            *part_b = *part_a;
            normal->x = 0.0;
            normal->y = 0.0;
            normal->z = 0.0;
        }
        return;
    }

    *degen = 1;
    *special = 1;
    *part_b = *part_a;
    normal->x = 0.0;
    normal->y = 0.0;
    normal->z = 0.0;
}
