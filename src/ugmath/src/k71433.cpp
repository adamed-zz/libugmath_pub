





#include <cmath>

double EQ_ask_number_tolerance();




static __declspec(noinline) double norm_period(double* value, const double* range)
{
    double r = *range;
    double a = *value;
    if (0.0 > r)
        return a;
    if (EQ_ask_number_tolerance() >= std::fabs(r - a))
    {
        *value = 0.0;
        return *value;
    }
    if (EQ_ask_number_tolerance() >= std::fabs(r - 0.0))
        return *value;
    if (a > 0.0)
    {
        double x = a - r * ((a / r >= 0.0) ? std::floor(a / r) : -std::floor(-(a / r)));
        if (EQ_ask_number_tolerance() >= std::fabs(x))
        {
            *value = 0.0;
            return *value;
        }
        *value = x;
        return x;
    }
    double b = (a == 0.0) ? a : -a;
    double q = b / r;
    double f = (q >= 0.0) ? std::floor(q) : -std::floor(-q);
    double rem = b - r * f;
    if (EQ_ask_number_tolerance() >= std::fabs(rem))
    {
        *value = 0.0;
        return *value;
    }
    double v = r - rem;
    *value = v;
    if (EQ_ask_number_tolerance() >= std::fabs(v))
    {
        *value = 0.0;
        return *value;
    }
    return v;
}

static const double kOne = 1.0;

void k71433(double* a1, double* a2, int* a3)
{
    const double& one = kOne;
    double span = a1[1] - a1[0];
    double tol = EQ_ask_number_tolerance();
    double lim = one - tol;
    if (span > lim)
    {
        *a3 = 1;
        a2[1] = one;
        a2[0] = 0.0;
        return;
    }
    double t0 = a1[0];
    double t1 = a1[1];
    (void)norm_period(&t0, &one);
    (void)norm_period(&t1, &one);
    double adj = t1;
    if (t0 > t1)
        adj = t1 + one;
    if (adj > one)
    {
        *a3 = 2;
        a2[0] = t0;
        a2[1] = one;
        a2[2] = 0.0;
        a2[3] = adj - one;
    }
    else
    {
        *a3 = 1;
        a2[0] = t0;
        a2[1] = adj;
    }
}
