









#include <cmath>



double EQ_ask_length_squared_tolerance();

int bc_POLE_equal_in_4d(double* const a1, double* const a2)
{
    if (!(fabs(a1[3] - a2[3]) <= 1.0e-10))
        return 0;
    double tol = EQ_ask_length_squared_tolerance();
    double rw1 = 1.0 / a1[3];
    double rw2 = 1.0 / a2[3];
    double dx = rw1 * a1[0] - rw2 * a2[0];
    double dy = rw1 * a1[1] - rw2 * a2[1];
    double dz = rw1 * a1[2] - rw2 * a2[2];
    double d2 = dx * dx + dy * dy + dz * dz;
    int r = 0;
    if (tol >= d2) r = 1;
    return r;
}
