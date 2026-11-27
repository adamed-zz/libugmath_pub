







#include <cmath>
#include <intrin.h>

void h0915(const int* a1, const double* a2, double* a3)
{

    const int n = a1[0];
    _ReadWriteBarrier();
    const int periodic = a1[2];
    const int dim = a1[3];

    a3[0] = 0.0;
    if (n > 1)
    {
        int off = dim;
        for (int i = 1; i < n; ++i)
        {
            double s = 0.0;
            for (int j = 0; j < dim; ++j)
            {
                double d = a2[off + j] - a2[off - dim + j];
                s = s + d * d;
            }
            a3[i] = std::sqrt(s) + a3[i - 1];
            off += dim;
        }
    }

    int last = n;
    if (periodic)
    {
        double s = 0.0;
        const int base = dim * (n - 1);
        for (int j = 0; j < dim; ++j)
        {
            double d = a2[base + j] - a2[j];
            s = s + d * d;
        }
        a3[n] = std::sqrt(s) + a3[n - 1];
        last = n + 1;
    }

    const int end = last - 1;

    if (!(1.0e-10 > std::fabs(a3[end])))
    {
        const double total = a3[last - 1];
        for (int i = 1; i < end; ++i)
            a3[i] = a3[i] / total;
        a3[end] = 1.0;
    }
    else
    {
        a3[0] = 0.0;
        a3[end] = 1.0;
        const double step = 1.0 / (double)(last - 1);
        for (int i = 1; i < end; ++i)
            a3[i] = step + a3[i - 1];
    }
}
