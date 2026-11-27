






#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>


__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void *ptr);
__declspec(dllimport) void ERROR_note(const char *file, int line, const char *msg, ...);

namespace UGS { namespace System {
__declspec(dllimport) int SYSS_fprintf(struct _iobuf *stream, const char *format, ...);
} }


extern "C" {
double qword_1800E1DA8;
double qword_1800E1DB0;
double qword_1800E1DB8;
double qword_1800E1DC0;
double qword_1800E1DC8;
int    dword_1800E1DD0;
}


#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define FMAX(a, b) ((a) > (b) ? (a) : (b))

static const char *const SVD_FILE = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\svd.c";

__forceinline static double pythag(double a, double b)
{
    double absa, absb;
    absa = fabs(a);
    absb = fabs(b);
    qword_1800E1DA8 = absa;
    qword_1800E1DB0 = absb;
    if (absa > absb) {
        qword_1800E1DB8 = absb / absa;
        return absa * sqrt(1.0 + (absb / absa) * (absb / absa));
    } else {
        if (absb == 0.0)
            return 0.0;
        qword_1800E1DB8 = absa / absb;
        return absb * sqrt(1.0 + (absa / absb) * (absa / absb));
    }
}

void __cdecl SOLVE_svd_decompose(double **a, int m, int n, double *w, double **v)
{
    int flag, i, its, j, jj, k, l = 0, nm = 0;
    double anorm, c, f, g, h, s, scale, x, y, z, *rv1;

    if (m < n)
        ERROR_note(SVD_FILE, 170, "SVDCMP: You must augment A with extra zero rows");
    rv1 = (double *)SM_alloc(n * sizeof(double));
    g = scale = anorm = 0.0;
    for (i = 0; i < n; i++) {
        l = i + 1;
        rv1[i] = scale * g;
        g = scale = 0.0;
        if (i < m) {
            s = 0.0;
            for (k = i; k < m; k++) scale += fabs(a[k][i]);
            if (scale) {
                for (k = i; k < m; k++) {
                    a[k][i] /= scale;
                    s += a[k][i] * a[k][i];
                }
                f = a[i][i];
                g = -SIGN(sqrt(s), f);
                h = f * g - s;
                a[i][i] = f - g;
                if (i != n - 1) {
                    for (j = l; j < n; j++) {
                        s = 0.0;
                        for (k = i; k < m; k++) s += a[k][i] * a[k][j];
                        f = s / h;
                        for (k = i; k < m; k++) a[k][j] += f * a[k][i];
                    }
                }
                for (k = i; k < m; k++) a[k][i] *= scale;
            }
        }
        w[i] = scale * g;
        g = scale = 0.0;
        if (i < m && i != n - 1) {
            s = 0.0;
            for (k = l; k < n; k++) scale += fabs(a[i][k]);
            if (scale) {
                for (k = l; k < n; k++) {
                    a[i][k] /= scale;
                    s += a[i][k] * a[i][k];
                }
                f = a[i][l];
                g = -SIGN(sqrt(s), f);
                h = f * g - s;
                a[i][l] = f - g;
                for (k = l; k < n; k++) rv1[k] = a[i][k] / h;
                if (i != m - 1) {
                    for (j = l; j < m; j++) {
                        s = 0.0;
                        for (k = l; k < n; k++) s += a[j][k] * a[i][k];
                        for (k = l; k < n; k++) a[j][k] += s * rv1[k];
                    }
                }
                for (k = l; k < n; k++) a[i][k] *= scale;
            }
        }
        qword_1800E1DC0 = anorm;
        s = fabs(w[i]) + fabs(rv1[i]);
        qword_1800E1DC8 = s;
        anorm = FMAX(anorm, s);
    }
    for (i = n - 1; i >= 0; i--) {
        l = i + 1;
        if (i < n - 1) {
            if (g) {
                for (j = l; j < n; j++) {
                    v[j][i] = (a[i][j] / a[i][l]) / g;
                    if (dword_1800E1DD0)
                        UGS::System::SYSS_fprintf(stdout, "SVD_decompose: set v[j][i] j = %d i = %d to %g\n",
                                     j, i, v[j][i]);
                }
                for (j = l; j < n; j++) {
                    for (s = 0.0, k = l; k < n; k++) s += a[i][k] * v[k][j];
                    for (k = l; k < n; k++) {
                        v[k][j] += s * v[k][i];
                        if (dword_1800E1DD0)
                            UGS::System::SYSS_fprintf(stdout, "SVD_decompose: update v[k][j] k = %d j = %d to %g\n",
                                         k, j, v[k][j]);
                    }
                }
            }
            for (j = l; j < n; j++) {
                v[i][j] = v[j][i] = 0.0;
                if (dword_1800E1DD0)
                    UGS::System::SYSS_fprintf(stdout, "SVD_decompose: zero v[i][j] & v[j][i] i = %d j = %d\n",
                                 i, j);
            }
        }
        v[i][i] = 1.0;
        if (dword_1800E1DD0)
            UGS::System::SYSS_fprintf(stdout, "SVD_decompose: set v[i][i] to 1.0 i = %d\n", i);
        g = rv1[i];
        l = i;
    }
    for (i = n - 1; i >= 0; i--) {
        l = i + 1;
        g = w[i];
        if (i < n - 1)
            for (j = l; j < n; j++) a[i][j] = 0.0;
        if (g) {
            g = 1.0 / g;
            if (i != n - 1) {
                for (j = l; j < n; j++) {
                    for (s = 0.0, k = l; k < m; k++) s += a[k][i] * a[k][j];
                    f = (s / a[i][i]) * g;
                    for (k = i; k < m; k++) a[k][j] += f * a[k][i];
                }
            }
            for (j = i; j < m; j++) a[j][i] *= g;
        } else {
            for (j = i; j < m; j++) a[j][i] = 0.0;
        }
        ++a[i][i];
    }
    for (k = n - 1; k >= 0; k--) {
        for (its = 1; its <= 30; its++) {
            flag = 1;
            for (l = k; l >= 0; l--) {
                nm = l - 1;
                if (fabs(rv1[l]) <= 1e-12) {
                    flag = 0;
                    break;
                }
                if (fabs(w[nm]) <= 1e-12) break;
            }
            if (flag) {
                c = 0.0;
                s = 1.0;
                for (i = l; i <= k; i++) {
                    f = s * rv1[i];
                    rv1[i] = c * rv1[i];
                    if (fabs(f) <= 1e-12) break;
                    g = w[i];
                    h = pythag(f, g);
                    w[i] = h;
                    h = 1.0 / h;
                    c = g * h;
                    s = -f * h;
                    for (j = 0; j < m; j++) {
                        y = a[j][nm];
                        z = a[j][i];
                        a[j][nm] = y * c + z * s;
                        a[j][i] = z * c - y * s;
                    }
                }
            }
            z = w[k];
            if (l == k) {
                if (z < 0.0) {
                    w[k] = -z;
                    if (dword_1800E1DD0)
                        UGS::System::SYSS_fprintf(stdout, "SVD_decompose: update negate all v\n");
                    for (j = 0; j < n; j++) v[j][k] = -v[j][k];
                }
                break;
            }
            if (its == 30)
                ERROR_note(SVD_FILE, 391, "No convergence in 30 SVDCMP iterations");
            x = w[l];
            nm = k - 1;
            y = w[nm];
            g = rv1[nm];
            h = rv1[k];
            f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
            g = pythag(f, 1.0);
            f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h)) / x;
            c = s = 1.0;
            for (j = l; j <= nm; j++) {
                i = j + 1;
                g = rv1[i];
                y = w[i];
                h = s * g;
                g = c * g;
                z = pythag(f, h);
                rv1[j] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = g * c - x * s;
                h = y * s;
                y *= c;
                for (jj = 0; jj < n; jj++) {
                    x = v[jj][j];
                    z = v[jj][i];
                    v[jj][j] = x * c + z * s;
                    if (dword_1800E1DD0)
                        UGS::System::SYSS_fprintf(stdout, "SVD_decompose: jj = %d j = %d v[jj][j] = %g\n",
                                     jj, j, v[jj][j]);
                    v[jj][i] = z * c - x * s;
                    if (dword_1800E1DD0)
                        UGS::System::SYSS_fprintf(stdout, "SVD_decompose: jj = %d i = %d v[jj][i] = %g\n",
                                     jj, i, v[jj][i]);
                }
                z = pythag(f, h);
                w[j] = z;
                if (z) {
                    z = 1.0 / z;
                    c = f * z;
                    s = h * z;
                }
                f = c * g + s * y;
                x = c * y - s * g;
                for (jj = 0; jj < m; jj++) {
                    y = a[jj][j];
                    z = a[jj][i];
                    a[jj][j] = y * c + z * s;
                    a[jj][i] = z * c - y * s;
                }
            }
            rv1[l] = 0.0;
            rv1[k] = f;
            w[k] = x;
        }
    }
    SM_free(rv1);
}
