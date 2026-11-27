









#include <math.h>

struct Point3 {
    double x;
    double y;
    double z;
};

void ERROR_internal(const char* file, int line, const char* msg, ...);

extern "C" void sub_180054DC0(int n, const Point3* pts, Point3* out, double* outlen) {
    *outlen = 0.0;
    if (n < 1) {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 694,
                       "There are no input points.");
        __debugbreak();
    }
    if (n == 1) {
        out->x = pts->x;
        out->y = pts->y;
        out->z = pts->z;
    } else {
        int idx = 0;
        double best = pts[0].x * pts[0].x + pts[0].y * pts[0].y + pts[0].z * pts[0].z;
        for (int i = 1; i < n; ++i) {
            const double d = pts[i].x * pts[i].x + pts[i].y * pts[i].y + pts[i].z * pts[i].z;
            if (d > best) {
                best = d;
                idx = i;
            }
        }
        out->x = pts[idx].x;
        out->y = pts[idx].y;
        out->z = pts[idx].z;
        *outlen = sqrt(best);
    }
}
