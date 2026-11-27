





#include <cmath>
#include <algorithm>

double EQ_ask_length_tolerance();


static __forceinline double clamp_w(double w)
{
    if (w < 1.0e-19)
    {
        if (w < 0.0)
            w = std::min(w, -1.0e-19);
        else
            w = 1.0e-19;
    }
    return w;
}


static __forceinline void norm_row(const double* p, double* b)
{
    double w = clamp_w(p[3]);
    b[0] = p[0] / w;
    b[1] = p[1] / w;
    b[2] = p[2] / w;
}


static __forceinline bool row_eq(const double* b, const double* q)
{
    double wq = clamp_w(q[3]);
    double dx = b[0] - q[0] / wq;
    double dy = b[1] - q[1] / wq;
    double dz = b[2] - q[2] / wq;
    double d2 = dy * dy + dx * dx + dz * dz;
    double d = d2 < 0.0 ? std::sqrt(d2) : std::sqrt(d2);
    return EQ_ask_length_tolerance() >= d;
}

void k4307c(int a1, int a2, double (**a3)[4], int* a4, int* a5, int* a6, int* a7)
{

    *a4 = 1;
    {
        double b[3];
        norm_row((const double*)a3[0], b);
        for (__int64 i = 1; i < a2; ++i)
        {
            if (!row_eq(b, (const double*)a3[i]))
            {
                *a4 = 0;
                break;
            }
        }
    }


    *a5 = 1;
    {
        double b[3];
        norm_row((const double*)a3[0] + 4 * (__int64)a1 - 4, b);
        for (__int64 i = 1; i < a2; ++i)
        {
            if (!row_eq(b, (const double*)a3[i] + 4 * (__int64)a1 - 4))
            {
                *a5 = 0;
                break;
            }
        }
    }


    *a6 = 1;
    {
        const double* first = (const double*)a3[0];
        double b[3];
        norm_row(first, b);
        const double* end = first + 4 * (__int64)a1;
        for (const double* q = first + 4; q < end; q += 4)
        {
            if (!row_eq(b, q))
            {
                *a6 = 0;
                break;
            }
        }
    }


    *a7 = 1;
    {
        const double* last = (const double*)a3[(__int64)a2 - 1];
        double b[3];
        norm_row(last, b);
        const double* end = last + 4 * (__int64)a1;
        for (const double* q = last + 4; q < end; q += 4)
        {
            if (!row_eq(b, q))
            {
                *a7 = 0;
                break;
            }
        }
    }
}
