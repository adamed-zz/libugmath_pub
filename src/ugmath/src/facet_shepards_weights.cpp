





#include <math.h>

void FACET_shepards_weights(int n, double* const a2, double a3, double a4, double* const a5)
{
    if (n >= 1)
    {
        int idx = 0;
        int found = 0;
        for (int i = 0; i < n; ++i)
        {
            a5[i] = 0.0;
            if (a3 >= a2[i])
            {
                found = 1;
                idx = i;
            }
        }
        if (found == 1)
        {
            a5[idx] = 1.0;
        }
        else
        {
            if (a4 == 1.0)
            {
                for (int i = 0; i < n; ++i)
                {
                    a5[i] = a2[i];
                }
            }
            else
            {
                for (int i = 0; i < n; ++i)
                {
                    a5[i] = pow(a2[i], a4);
                }
            }
            for (int i = 0; i < n; ++i)
            {
                a5[i] = 1.0 / a5[i];
            }
            double sum = a5[0];
            for (int i = 1; i < n; ++i)
            {
                sum += a5[i];
            }
            for (int i = 0; i < n; ++i)
            {
                a5[i] = a5[i] / sum;
            }
        }
    }
}
