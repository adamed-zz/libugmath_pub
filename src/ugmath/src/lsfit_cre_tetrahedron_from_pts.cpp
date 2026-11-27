






#include <math.h>

namespace UGS {
namespace Math {
struct Point3 {
    double x, y, z;
};
struct Vector3 {
    double x, y, z;
};
}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;


__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file_name, int line,
                                                               const char* message, ...);


void LSFIT_plane_to_points(int flag, Point3* pts, int npts, Point3* plane_pt, Vector3* plane_n,
                           int* idx, double* dists);
void FACET_point_line_proj(Point3* pt, Point3* line_pt, Vector3* line_dir, int flag,
                           Point3* proj_pt, double* param);
void ARC_SPLINE_adjust_vec_on_pln(bool flag, Vector3* pl_n, Vector3* vec);
int VEC3_unitize(const Vector3* vec, double tol, double* len, Vector3* unit_vec);

static const char* const LSFIT_SRC_FILE = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c";

void LSFIT_cre_tetrahedron_from_pts(int npts, Point3* pts, double tol, int* rc, int* max_idx,
                                    Point3* p1, Point3* p2, Point3* p3, Point3* p4)
{
    *rc = 0;
    *max_idx = 0;
    double t;
    Point3 pl_pt = {0.0, 0.0, 0.0};
    Vector3 pl_n = {0.0, 0.0, 0.0};
    Point3 q = {0.0, 0.0, 0.0};
    double dists[3];

    LSFIT_plane_to_points(0, pts, npts, &pl_pt, &pl_n, max_idx, dists);
    if (*max_idx == 1 || tol > dists[1]) {
        *rc = 1;
        return;
    }

    double maxd = 0.0;
    int i1 = -1;
    for (int i = 0; i < npts; ++i) {
        double t = ((pts[i].x - pl_pt.x) * pl_n.x
                  + (pts[i].y - pl_pt.y) * pl_n.y
                  + (pts[i].z - pl_pt.z) * pl_n.z)
                 / sqrt(pl_n.x * pl_n.x + pl_n.y * pl_n.y + pl_n.z * pl_n.z);
        if (fabs(t) > maxd) {
            maxd = t;
            i1 = i;
        }
    }
    if (i1 == -1) {
        ERROR_internal(LSFIT_SRC_FILE, 397,
                       "There was no point found at max distance from the plane (pl_pt,pl_n).");
    }
    p1->x = pts[i1].x;
    p1->y = pts[i1].y;
    p1->z = pts[i1].z;

    double maxd2 = 0.0;
    int i2 = -1;
    for (int i = 0; i < npts; ++i) {
        if (i != i1) {
            FACET_point_line_proj(&pts[i], p1, &pl_n, 1, &q, &t);
            double d2 = (pts[i].x - q.x) * (pts[i].x - q.x)
                      + (pts[i].y - q.y) * (pts[i].y - q.y)
                      + (pts[i].z - q.z) * (pts[i].z - q.z);
            if (d2 > maxd2) {
                maxd2 = d2;
                i2 = i;
            }
        }
    }
    if (i2 == -1) {
        ERROR_internal(LSFIT_SRC_FILE, 425,
                       "There was no point found at max distance from the line (p1,pl_n).");
    }
    p2->x = pts[i2].x;
    p2->y = pts[i2].y;
    p2->z = pts[i2].z;

    Vector3 u;
    u.x = p2->x - p1->x;
    u.y = p2->y - p1->y;
    u.z = p2->z - p1->z;
    ARC_SPLINE_adjust_vec_on_pln(true, &pl_n, &u);

    double mind = 1.0e19;
    int i3 = -1;
    for (int i = 0; i < npts; ++i) {
        if (i != i1 && i != i2) {
            FACET_point_line_proj(&pts[i], &pl_pt, &u, 1, &q, &t);
            if (mind > t) {
                mind = t;
                i3 = i;
            }
        }
    }
    if (i3 == -1) {
        ERROR_internal(LSFIT_SRC_FILE, 456,
                       "There was no point found at min parameter on the line (pl_pt,u0).");
    }
    p3->x = pts[i3].x;
    p3->y = pts[i3].y;
    p3->z = pts[i3].z;

    Vector3 w;
    w.x = u.y * pl_n.z - u.z * pl_n.y;
    w.y = u.z * pl_n.x - u.x * pl_n.z;
    w.z = u.x * pl_n.y - u.y * pl_n.x;
    double wlen;
    VEC3_unitize(&w, 1.0e-10, &wlen, &w);

    double maxd3 = 0.0;
    int i4 = -1;
    for (int i = 0; i < npts; ++i) {
        if (i != i1 && i != i2 && i != i3) {
            double t = ((pts[i].x - pl_pt.x) * w.x
                      + (pts[i].y - pl_pt.y) * w.y
                      + (pts[i].z - pl_pt.z) * w.z)
                     / sqrt(w.x * w.x + w.y * w.y + w.z * w.z);
            if (fabs(t) > maxd3) {
                maxd3 = t;
                i4 = i;
            }
        }
    }
    if (i4 == -1) {
        ERROR_internal(LSFIT_SRC_FILE, 486,
                       "There was no point found at max distance from the plane (p1,p2,p3).");
    }
    p4->x = pts[i4].x;
    p4->y = pts[i4].y;
    p4->z = pts[i4].z;
}
