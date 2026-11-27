








#include <math.h>


#ifdef NR_AMOEBA_TEST_STUBS
void* SM_alloc(unsigned __int64);
void SM_free(void*);
#else
__declspec(dllimport) void* SM_alloc(unsigned __int64);
__declspec(dllimport) void SM_free(void*);
#endif


static __declspec(noinline) double amotry(
    double* p, double* y, double* psum, int ndim,
    double (*funk)(double* const, void*), void* user,
    int ihi, int* nfunk, double fac)
{
    int j;
    double ytry;
    double* ptry = (double*)SM_alloc(sizeof(double) * ndim);
    double fac1 = (1.0 - fac) / ndim;
    double fac2 = fac1 - fac;
    for (j = 0; j < ndim; j++)
        ptry[j] = psum[j] * fac1 - p[ihi * ndim + j] * fac2;
    ytry = (*funk)(ptry, user);
    ++*nfunk;
    if (y[ihi] > ytry) {
        y[ihi] = ytry;
        for (j = 0; j < ndim; j++) {
            psum[j] += ptry[j] - p[ihi * ndim + j];
            p[ihi * ndim + j] = ptry[j];
        }
    }
    SM_free(ptry);
    return ytry;
}

int NR_amoeba(double* const p, double* const y, int ndim, double ftol, int itmax,
              double (*funk)(double* const, void*), void* user, int* nfunk)
{
    int i, j, ilo, ihi, inhi, mpts = ndim + 1;
    double ytry, ysave, sum, rtol;
    double* psum = (double*)SM_alloc(sizeof(double) * ndim);
    *nfunk = 0;
    for (j = 0; j < ndim; j++) {
        psum[j] = 0.0;
        for (i = 0; i < mpts; i++)
            psum[j] += p[i * ndim + j];
    }
    for (;;) {
        ilo = 1;
        ihi = (y[0] > y[1]) ? 0 : 1;
        inhi = (y[0] > y[1]) ? 1 : 0;
        for (i = 0; i < mpts; i++) {
            if (y[i] < y[ilo])
                ilo = i;
            if (y[i] > y[ihi]) {
                inhi = ihi;
                ihi = i;
            }
            else if (y[i] > y[inhi] && i != ihi) {
                inhi = i;
            }
        }
        if (ihi == ilo) {
            SM_free(psum);
            return 0;
        }
        rtol = y[ihi] - y[ilo];
        sum = 0.0;
        for (j = 0; j < ndim; j++) {
            double d = p[ihi * ndim + j] - p[ilo * ndim + j];
            sum += d * d;
        }
        if (sqrt(sum) * ftol > rtol) {
            SM_free(psum);
            return 0;
        }
        if (*nfunk >= itmax)
            return -1;
        ytry = amotry(p, y, psum, ndim, funk, user, ihi, nfunk, -1.0);
        if (ytry <= y[ilo]) {
            amotry(p, y, psum, ndim, funk, user, ihi, nfunk, 2.0);
        }
        else if (ytry >= y[inhi]) {
            ysave = y[ihi];
            ytry = amotry(p, y, psum, ndim, funk, user, ihi, nfunk, 0.5);
            if (ytry >= ysave) {
                for (i = 0; i < mpts; i++) {
                    if (i != ilo) {
                        for (j = 0; j < ndim; j++)
                            p[i * ndim + j] = psum[j] =
                                0.5 * (p[i * ndim + j] + p[ilo * ndim + j]);
                        y[i] = (*funk)(psum, user);
                    }
                }
                *nfunk += ndim;
                for (j = 0; j < ndim; j++) {
                    psum[j] = 0.0;
                    for (i = 0; i <= ndim; i++)
                        psum[j] += p[i * ndim + j];
                }
            }
        }
    }
}
