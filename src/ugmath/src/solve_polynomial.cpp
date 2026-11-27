







#include <math.h>
#include <intrin.h>


double EQ_ask_number_tolerance();


extern __declspec(dllimport) int MACH__checking_level;
extern __declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);


struct SOLVE_complex
{
    double real;
    double imag;
};


void sub_1800AB130(int degree, SOLVE_complex* work, SOLVE_complex* roots_work, bool flag);
int sub_1800AAF80(int degree, SOLVE_complex* roots_work, double* roots);

int SOLVE_polynomial(int degree, const double* const coeffs, double* const roots)
{
    int i, n, num_roots;
    double tol, c;
    SOLVE_complex work[5];
    SOLVE_complex roots_work[4];

    tol = EQ_ask_number_tolerance();
    if (MACH__checking_level > 0 && degree > 4)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\solve.c", 1657,
                       "Degree is too large in SOLVE_polynomial())!!!\n");
        __debugbreak();
        __assume(0);
    }
    n = degree;
    if (tol >= fabs(coeffs[n]))
    {
        do
        {
            if (n < 0)
                break;
            c = coeffs[--n];
        } while (tol >= fabs(c));
    }
    if (n != 0)
    {
        if (n >= 0)
        {
            for (i = 0; i <= n; i++)
            {
                work[i].real = coeffs[i];
                work[i].imag = 0.0;
            }
        }
        sub_1800AB130(n, work, roots_work, true);
        num_roots = sub_1800AAF80(n, roots_work, roots);
    }
    else
    {
        num_roots = 0;
    }
    return num_roots;
}
