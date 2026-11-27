







#include <cmath>
#include <cstdint>
#include <algorithm>

double EQ_ask_length_tolerance();

void k4306c(int a1, int a2, double (**a3)[4], int a4, int a5, int* a6, int* a7)
{
    *a6 = 1;
    __int64 n1 = a1;
    __int64 n2 = a2;
    if (!a4 && a2 > 0)
    {
        __int64 i = 0;
        __int64 stride = 4LL * a1;
        while (true)
        {
            double* p = (double*)a3[i];
            double* q = p + stride - 4;
            double wp = p[3];
            if (wp < 1.0e-19)
            {
                if (wp < 0.0)
                    wp = std::min(wp, -1.0e-19);
                else
                    wp = 1.0e-19;
            }
            double wq = q[3];
            if (wq < 1.0e-19)
            {
                if (wq < 0.0)
                    wq = std::min(wq, -1.0e-19);
                else
                    wq = 1.0e-19;
            }
            double dx = p[0] / wp;
            double dy = p[1] / wp;
            double dz = p[2] / wp;
            dx -= q[0] / wq;
            dy -= q[1] / wq;
            dz -= q[2] / wq;
            double d2 = dy * dy + dx * dx + dz * dz;
            double d = d2 < 0.0 ? sqrt(d2) : sqrt(d2);
            if (!(EQ_ask_length_tolerance() >= d))
            {
                *a6 = 0;
                break;
            }
            if (++i >= n2)
                break;
        }
    }
    *a7 = 1;
    if (!a5)
    {
        double* first = (double*)*a3;
        double* last = (double*)a3[n2 - 1];
        {
            double* p = first;
            for (__int64 j = 0; j < n1; ++j)
            {
                double wp = p[3];
                if (wp < 1.0e-19)
                {
                    if (wp < 0.0)
                        wp = std::min(wp, -1.0e-19);
                    else
                        wp = 1.0e-19;
                }
                double* q = last + 4 * j;
                double wq = q[3];
                if (wq < 1.0e-19)
                {
                    if (wq < 0.0)
                        wq = std::min(wq, -1.0e-19);
                    else
                        wq = 1.0e-19;
                }
                double dx = p[0] / wp;
                double dy = p[1] / wp;
                double dz = p[2] / wp;
                dx -= q[0] / wq;
                dy -= q[1] / wq;
                dz -= q[2] / wq;
                double d2 = dy * dy + dx * dx + dz * dz;
                double d = d2 < 0.0 ? sqrt(d2) : sqrt(d2);
                if (!(EQ_ask_length_tolerance() >= d))
                {
                    *a7 = 0;
                    break;
                }
                p += 4;
            }
        }
    }
}
