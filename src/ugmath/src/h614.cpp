











#include <math.h>

void h100(const double* a1, const double* a2, double* a3);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h605(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7);
void h110(const double* a1, double* a2);

void h614(const double* a1, const double* a2, const double* a3, int* a4, double* a5,
          double* a6)
{
    static const double kZero = 0.0;
    static const double kOne = 1.0;
    static const int kSelOne = 1;

    double p1[3];
    double p2[3];
    double dx, dy, dz;
    double u1, w1, u2, w2;
    double dir[2];
    double nrm[2];
    double uv[2];
    double center[2];
    double radius;
    double world[4][3];
    double v125[9];
    int st;

    *a4 = 1;
    h100(a1, a3, p1);
    h100(a1 + 3, a3, p2);
    dx = p2[0] - p1[0];
    dy = p2[1] - p1[1];
    dz = p2[2] - p1[2];
    h805(&dz, &kZero, &kSelOne, &st);
    if (st)
    {

        h805(&p1[2], a2 + 2, &kSelOne, &st);
        if (!st)
            return;
        {
            double c = a2[12];
            double s = a2[11];
            double q1x = p1[0] - a2[7];
            double q1y = p1[1] - a2[8];
            double q2x = p2[0] - a2[7];
            double q2y = p2[1] - a2[8];
            u1 = q1x * c + q1y * s;
            w1 = c * q1y - q1x * s;
            u2 = q2x * c + q2y * s;
            w2 = c * q2y - q2x * s;
        }
        {
            double du = u2 - u1;
            double dw = w2 - w1;
            double ny = -du * a2[10];
            double nx = u1 * dw - du * w1;
            double dist = sqrt(nx * nx + ny * ny);
            double aw, any, scale;

            h805(&dist, &kZero, &kSelOne, &st);
            if (st == 1)
                return;
            aw = nx;
            if (nx < 0.0)
                aw = -nx;
            any = ny;
            if (ny < 0.0)
                any = -ny;
            scale = dw * a2[9];
            if (aw <= any)
            {
                dir[0] = 0.0;
                dir[1] = -scale / ny;
            }
            else
            {
                dir[1] = 0.0;
                dir[0] = scale / nx;
            }
            nrm[0] = ny;
            nrm[1] = nx;
            uv[0] = dir[0] + nrm[0];
            uv[1] = dir[1] + nrm[1];
            center[0] = 0.0;
            center[1] = 0.0;
            radius = 1.0;
            h605(dir, uv, center, &radius, a4, a5, a5 + 3);
        }
        {
            int status = *a4;
            int cnt;
            if (status == 1)
                return;
            if (status != 2)
            {
                if (a5[3] > 0.0)
                {
                    cnt = status;
                    if (a5[0] <= 0.0)
                    {
                        *a4 = status - 1;
                        a5[0] = a5[3];
                        a5[1] = a5[4];
                        cnt = *a4;
                    }
                    goto CONVERT;
                }
                status = status - 1;
                *a4 = status;
            }
            cnt = status;
            if (a5[0] <= 0.0)
            {
                *a4 = status - 1;
                return;
            }
        CONVERT:
            if (cnt >= 2)
            {
                for (int k = 0; k < cnt - 1; ++k)
                {
                    double x = a5[k * 3 + 0];
                    double y = a5[k * 3 + 1];
                    double yy = y * a2[10] / x;
                    double xx = a2[9] / x;
                    a5[k * 3 + 0] = xx;
                    a5[k * 3 + 1] = yy;
                    world[k][0] = a2[12] * xx - a2[11] * yy + a2[7];
                    world[k][1] = a2[11] * xx + a2[12] * yy + a2[8];
                    world[k][2] = a2[2];
                }
            }
        }
    }
    else
    {

        double t = (a2[2] - p1[2]) / dz;
        double xw = dx * t + p1[0];
        double yw = dy * t + p1[1];
        double zw = dz * t + p1[2];
        double px = xw - a2[7];
        double py = yw - a2[8];
        double u = px * a2[12] + py * a2[11];
        double w = a2[12] * py - px * a2[11];
        world[0][0] = xw;
        world[0][1] = yw;
        world[0][2] = zw;
        if (u >= 0.0)
        {
            uv[0] = u;
            uv[1] = w;
            h805(uv, &kZero, &kSelOne, &st);
            if (st != 1)
            {
                double xx = a2[9] / u;
                double yy = xx * w / a2[10];
                double d2 = sqrt(yy * yy + xx * xx);
                h805(&d2, &kOne, &kSelOne, &st);
                if (st)
                    *a4 = 2;
            }
        }
    }
    if (*a4 >= 2)
    {
        int cnt = *a4;
        h110(a3, v125);
        for (int k = 0; k < cnt - 1; ++k)
        {
            h100(&world[k][0], v125, &a5[k * 3]);
            a6[k] = (world[k][1] - a2[8]) * a2[12] - (world[k][0] - a2[7]) * a2[11];
        }
    }
}
