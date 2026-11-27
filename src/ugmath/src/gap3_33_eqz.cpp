


#include <math.h>

double EQ_ask_number_tolerance();
double EQ_ask_length_tolerance();
double EQ_ask_length_squared_tolerance();

int eqz(const double* a, const double* b, const int* mode)
{
    double tol;
    int m = *mode;
    if (m == 0)
        tol = EQ_ask_number_tolerance();
    else if (m == 1)
        tol = EQ_ask_length_tolerance();
    else if (m == 2)
        tol = EQ_ask_length_squared_tolerance();
    else
    {
        double t = EQ_ask_number_tolerance();
        tol = t * t;
    }
    return tol >= fabs(*a - *b);
}
