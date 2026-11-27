




























namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
}
}

typedef UGS::Math::Point2 Point2;

#define ELL_RES(xv, yv)                                                       \
    (a[0] + a[0]) * (xv) * (yv) + (xv) * (xv) + (yv) * a[1] * (yv)            \
        + (a[2] + a[2]) * (xv) + (a[3] + a[3]) * (yv) + a[4]

#define ELL_POINT(idx, xv, yv)                                                \
    do                                                                        \
    {                                                                         \
        double xv = pts[idx].x;                                               \
        double yv = pts[idx].y;                                               \
        res[idx] = ELL_RES(xv, yv);                                           \
    } while (0)

void LSFIT_ellipse_func(Point2* pts, int n, int, double* const a,
                        double* const res, int*)
{
    int i = 0;
    if (n >= 4)
    {
        int cnt = ((unsigned)(n - 4) >> 2) + 1;
        i = cnt * 4;
        const Point2* p = pts;
        double* r = res;
        do
        {
            r[0] = ELL_RES(p[0].x, p[0].y);
            r[1] = ELL_RES(p[1].x, p[1].y);
            r[2] = ELL_RES(p[2].x, p[2].y);
            r[3] = ELL_RES(p[3].x, p[3].y);
            p += 4;
            r += 4;
        } while (--cnt);
    }
    if (i < n)
    {
        int rest = n - i;
        do
        {
            ELL_POINT(i, x, y);
            i++;
        } while (--rest);
    }
}
