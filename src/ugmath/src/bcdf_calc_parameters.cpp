















#include <math.h>

void BCDF_CALC_parameters(int n, int stride, double* pts, double alpha, bool normalize, double* out)
{
    *out = 0.0;

    if (fabs(alpha - 0.0) <= 1.0e-10)
    {

        for (int i = 1; i < n; ++i)
            out[i] = out[i - 1] + 1.0;
    }
    else if (fabs(alpha - 1.0) <= 1.0e-10)
    {

        for (int i = 1; i < n; ++i)
        {
            double sum = 0.0;
            for (int j = 0; j < stride; ++j)
            {
                double d = pts[i * stride + j] - pts[(i - 1) * stride + j];
                sum += d * d;
            }
            out[i] = out[i - 1] + sqrt(sum);
        }
    }
    else
    {

        for (int i = 1; i < n; ++i)
        {
            double sum = 0.0;
            for (int j = 0; j < stride; ++j)
            {
                double d = pts[i * stride + j] - pts[(i - 1) * stride + j];
                sum += d * d;
            }
            out[i] = out[i - 1] + pow(sqrt(sum), alpha);
        }
    }

    if (fabs(out[n - 1] - 0.0) <= 1.0e-10)
    {

        out[0] = 0.0;
        double step = (double)(n - 1);
        for (int i = 1; i < n; ++i)
            out[i] = out[i - 1] + step;
    }

    if (normalize)
    {
        for (int i = 1; i < n - 1; ++i)
            out[i] /= out[n - 1];
        out[n - 1] = 1.0;
    }
}
