










#include <math.h>

void h100(const double* a1, const double* a2, double* a3);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
int eqz(const double* a1, const double* a2, const int* a3);
void h806(const double* a1, const double* a2, const double* a3, int* a4);
void h110(const double* a1, double* a2);

void h613(const double* a1, const double* a2, const double* a3, int* a4, double* a5,
          double* a6)
{
    static const double kZero = 0.0;
    static const double kTol = 1e-05;
    static const int kSelOne = 1;
    static const int kSelZero = 0;

    double pt[6];
    double pts[14];
    double v85[2];
    double v86[9];
    double dx, dy, dz;
    int st, i1, i2;

    *a4 = 1;
    h100(a1, a3, &pt[0]);
    h100(a1 + 3, a3, &pt[3]);
    dx = pt[3] - pt[0];
    dy = pt[4] - pt[1];
    dz = pt[5] - pt[2];
    h805(&dz, &kZero, &kSelOne, &st);
    if (st)
    {
        h805(&pt[2], a2 + 2, &kSelOne, &st);
        if (!st)
            return;
        {
            double c = a2[11];
            double s = a2[12];
            double px = pt[0] - a2[7];
            double py = pt[1] - a2[8];
            double qx = pt[3] - a2[7];
            double qy = pt[4] - a2[8];
            double u0 = py * c + s * px;
            double w0 = py * s - c * px;
            double u1 = s * qx + c * qy;
            double w1 = s * qy - c * qx;
            double du = u1 - u0;
            double dw = w1 - w0;
            double cross = dw * u0 - du * w0;

            h014(&cross, a6, v85, &st, &i1, &i2);
            if (st == 1 || st == 2 || st == 4)
                return;
            *a4 = i2 + 1;
            if (*a4 == 3 && eqz(a6, a6 + 1, &kSelZero))
                *a4 = 2;
            if (*a4 >= 2)
            {
                int cnt = *a4 - 1;
                for (int k = 0; k < cnt; ++k)
                {
                    double t = a6[k];
                    double a = t * t / a2[9];
                    pts[k * 3 + 0] = s * a - c * t + a2[7];
                    pts[k * 3 + 1] = c * a + s * t + a2[8];
                    pts[k * 3 + 2] = a2[2];
                }
            }
        }
    }
    else
    {
        double t = (a2[2] - pt[2]) / dz;
        pts[0] = dx * t + pt[0];
        pts[1] = dy * t + pt[1];
        pts[2] = dz * t + pt[2];
        {
            double px = pts[0] - a2[7];
            double py = pts[1] - a2[8];
            double u = py * a2[11] + a2[12] * px;
            double w = py * a2[12] - a2[11] * px;
            if (0.0 > u)
                return;
            {
                double w2s = w * w / a2[9];
                double aw = w;
                if (w < 0.0)
                    aw = -w;
                double r = sqrt(a2[9] * u);
                double d1 = u - w2s;
                double d2 = w - r * w / aw;
                double dist = sqrt(d1 * d1 + d2 * d2);
                h806(&dist, &kZero, &kTol, &st);
                if (!st)
                    return;
            }
            *a4 = 2;
            a6[0] = w;
        }
    }
    h110(a3, v86);
    if (*a4 >= 2)
    {
        int cnt = *a4 - 1;
        for (int k = 0; k < cnt; ++k)
            h100(&pts[k * 3], v86, &a5[k * 3]);
    }
}
