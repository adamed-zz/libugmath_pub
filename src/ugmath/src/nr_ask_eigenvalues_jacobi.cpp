




















#include <cmath>

__declspec(dllimport) void* SM_alloc(unsigned __int64, unsigned __int64);
__declspec(dllimport) void SM_free(void*);
__declspec(dllimport) void ERROR_internal(const char*, int, const char*, ...);
namespace UGS {
namespace Memory {
__declspec(dllimport) void ThrowIndexOutOfRange(int, int, int);
}
}

void NR_2d_matrix_identity(double** a, int n);


class LocalVector {
public:
    LocalVector(int n) : m_n(n), m_p(0)
    {
        m_p = (n > 3) ? (double*)SM_alloc((unsigned __int64)n, sizeof(double)) : m_buf;
    }
    ~LocalVector()
    {
        if (m_p && m_p != m_buf)
            SM_free(m_p);
        m_n = 0;
        m_p = 0;
    }
    double& operator[](int i)
    {
        if ((unsigned)i >= (unsigned)m_n)
            UGS::Memory::ThrowIndexOutOfRange(i, 0, m_n);
        return m_p[i];
    }

private:
    int m_n;
    double* m_p;
    double m_buf[3];
};

#define NR_NEAR_ZERO(x) (fabs((x) - 0.0) <= 1.0e-10)
#define NR_ROTATE(T, i, j, k, l)            \
    {                                       \
        gg = T[i][j];                       \
        hh = T[k][l];                       \
        T[i][j] = gg - s * (hh + gg * tau); \
        T[k][l] = hh + s * (gg - hh * tau); \
    }

void NR_ask_eigenvalues_jacobi(double** a, int n, int max_iter, double* const d,
                               double** v, int* nrot)
{
    LocalVector b(n), z(n);

    NR_2d_matrix_identity(v, n);

    for (int i = 0; i < n; i++) {
        double aii = a[i][i];
        d[i] = aii;
        b[i] = aii;
        z[i] = 0.0;
    }
    *nrot = 0;

    int i;
    for (i = 1; i < max_iter; i++) {
        double sm = 0.0;
        for (int ip = 0; ip < n - 1; ip++)
            for (int iq = ip + 1; iq < n; iq++)
                sm += fabs(a[ip][iq]);

        if (NR_NEAR_ZERO(sm))
            break;

        double tresh = (i < 4) ? 0.2 * sm / (double)(n * n) : 0.0;

        for (int ip = 0; ip < n - 1; ip++) {
            for (int iq = ip + 1; iq < n; iq++) {
                double g = 100.0 * fabs(a[ip][iq]);
                if (i > 4 &&
                    fabs((fabs(d[ip]) + g) - fabs(d[ip])) <= 1.0e-10 &&
                    fabs((fabs(d[iq]) + g) - fabs(d[iq])) <= 1.0e-10) {
                    a[ip][iq] = 0.0;
                } else if (fabs(a[ip][iq]) > tresh) {
                    double h = d[iq] - d[ip];
                    double t;
                    if (fabs((fabs(h) + g) - fabs(h)) <= 1.0e-10) {
                        t = a[ip][iq] / h;
                    } else {
                        double theta = 0.5 * h / a[ip][iq];
                        t = 1.0 / (fabs(theta) + sqrt(1.0 + theta * theta));
                        if (theta < 0.0)
                            t = -t;
                    }
                    double c = 1.0 / sqrt(1.0 + t * t);
                    double s = t * c;
                    double tau = s / (1.0 + c);
                    h = t * a[ip][iq];
                    z[ip] -= h;
                    z[iq] += h;
                    d[ip] -= h;
                    d[iq] += h;
                    a[ip][iq] = 0.0;

                    double gg, hh;
                    for (int j = 0; j < ip; j++) NR_ROTATE(a, j, ip, j, iq);
                    for (int j = ip + 1; j < iq; j++) NR_ROTATE(a, ip, j, j, iq);
                    for (int j = iq + 1; j < n; j++) NR_ROTATE(a, ip, j, iq, j);
                    for (int j = 0; j < n; j++) NR_ROTATE(v, j, ip, j, iq);
                    ++*nrot;
                }
            }
        }

        for (int ip = 0; ip < n; ip++) {
            double zz = z[ip];
            b[ip] += zz;
            d[ip] = b[ip];
            z[ip] = 0.0;
        }
    }

    if (i >= max_iter)
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\nr_eigensystems.c",
                       235,
                       "Too many iterations in routine NR_ask_eigenvalues_jacobi.");
}
