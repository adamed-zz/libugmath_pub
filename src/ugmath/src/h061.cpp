











extern void vcru3(const double* a1, const double* a2, int* ok, double* out);
extern void h060(const double* a1, const double* a2, const double* a3, double* a4);

void h061(const double* a1, const double* a2, double* a3)
{
    int ok;
    double axis[3];
    *a3 = 0.0;
    vcru3(a1, a2, &ok, axis);
    if (ok == 1) {
        h060(a1, a2, axis, a3);
    } else if (a1[1] * a2[1] + *a1 * *a2 + a1[2] * a2[2] < 0.0) {
        *a3 = 3.141592653589793;
    }
}
