










#include <cmath>


double EQ_ask_length_squared_tolerance();



__declspec(noinline) static void b2x_pole_average_in_3d(double (*a1)[4], int n, double (*a3)[3])
{
    double sx = 0.0;
    double sy = 0.0;
    double sz = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double w = a1[i][3];
        sx = a1[i][0] / w + sx;
        sy = a1[i][1] / w + sy;
        sz = a1[i][2] / w + sz;
    }
    double inv = 1.0 / (double)n;
    (*a3)[0] = sx * inv;
    (*a3)[1] = sy * inv;
    (*a3)[2] = sz * inv;
}

int bc_POLE_identical_poles_in_3d(double (*a1)[4], int a2)
{
    double tol = EQ_ask_length_squared_tolerance();
    double n = (double)a2;
    int mid = (int)ceil(n * 0.5);
    double(*pm)[4] = a1 + mid;
    double r0 = 1.0 / a1[0][3];
    double rm = 1.0 / pm[0][3];
    double dx0 = r0 * a1[0][0] - rm * pm[0][0];
    double dy0 = r0 * a1[0][1] - rm * pm[0][1];
    double dz0 = r0 * a1[0][2] - rm * pm[0][2];
    double d20 = dy0 * dy0 + dx0 * dx0 + dz0 * dz0;
    if (!(tol >= d20))
        return 0;

    double avg[3];
    b2x_pole_average_in_3d(a1, a2, &avg);
    long long cnt = (long long)a2;
    if ((int)cnt <= 0)
        return 1;

    long long i = 0;
    double ax = avg[0];
    double ay = avg[1];
    double thr = (n - 1.0) * 1.0e-10 / n;
    double az = avg[2];
    for (; i < cnt; ++i)
    {
        double w = a1[i][3];
        double dx = ax - a1[i][0] / w;
        double dy = ay - a1[i][1] / w;
        double dz = az - a1[i][2] / w;
        double dd = dy * dy + dx * dx + dz * dz;
        double dist = sqrt(dd);
        if (!(thr >= dist))
            return 0;
    }
    return 1;
}
