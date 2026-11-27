
























#include <emmintrin.h>

struct MC_csys_s {
    double origin[3];
    double axis0[3];
    double axis1[3];
    double axis2[3];
};

static __forceinline __m128d mc_ld(double x) { return _mm_set_sd(x); }
static __forceinline __m128d mc_mul(__m128d d, __m128d s) { return _mm_mul_sd(d, s); }
static __forceinline __m128d mc_add(__m128d d, __m128d s) { return _mm_add_sd(d, s); }
static __forceinline __m128d mc_sub(__m128d d, __m128d s) { return _mm_sub_sd(d, s); }

void MC_calc_csys_to_csys_transform(MC_csys_s *a1, MC_csys_s *a2, double (*const a3)[4])
{
    const volatile double *u = (const volatile double *)a1;
    const volatile double *v = (const volatile double *)a2;

    double U[12];
    double V[12];



    V[3]  = v[3];
    V[6]  = v[6];
    V[9]  = v[9];
    U[5]  = u[5];
    V[5]  = v[5];
    V[7]  = v[7];
    V[8]  = v[8];
    U[11] = u[11];
    V[10] = v[10];
    V[11] = v[11];
    U[7]  = u[7];
    U[4]  = u[4];
    U[3]  = u[3];
    U[6]  = u[6];
    U[9]  = u[9];
    V[4]  = v[4];
    U[8]  = u[8];
    U[10] = u[10];



    const __m128d r00 = mc_add(mc_add(mc_mul(mc_ld(V[6]), mc_ld(U[6])), mc_mul(mc_ld(V[3]), mc_ld(U[3]))), mc_mul(mc_ld(V[9]), mc_ld(U[9])));
    const __m128d r01 = mc_add(mc_add(mc_mul(mc_ld(U[7]), mc_ld(V[6])), mc_mul(mc_ld(U[4]), mc_ld(V[3]))), mc_mul(mc_ld(U[10]), mc_ld(V[9])));
    const __m128d r02 = mc_add(mc_add(mc_mul(mc_ld(U[8]), mc_ld(V[6])), mc_mul(mc_ld(U[5]), mc_ld(V[3]))), mc_mul(mc_ld(U[11]), mc_ld(V[9])));
    const __m128d r10 = mc_add(mc_add(mc_mul(mc_ld(V[7]), mc_ld(U[6])), mc_mul(mc_ld(V[4]), mc_ld(U[3]))), mc_mul(mc_ld(V[10]), mc_ld(U[9])));
    const __m128d r11 = mc_add(mc_add(mc_mul(mc_ld(V[7]), mc_ld(U[7])), mc_mul(mc_ld(V[4]), mc_ld(U[4]))), mc_mul(mc_ld(V[10]), mc_ld(U[10])));
    const __m128d r12 = mc_add(mc_add(mc_mul(mc_ld(U[8]), mc_ld(V[7])), mc_mul(mc_ld(U[5]), mc_ld(V[4]))), mc_mul(mc_ld(U[11]), mc_ld(V[10])));
    const __m128d r20 = mc_add(mc_add(mc_mul(mc_ld(V[8]), mc_ld(U[6])), mc_mul(mc_ld(V[5]), mc_ld(U[3]))), mc_mul(mc_ld(V[11]), mc_ld(U[9])));
    const __m128d r21 = mc_add(mc_add(mc_mul(mc_ld(V[8]), mc_ld(U[7])), mc_mul(mc_ld(V[5]), mc_ld(U[4]))), mc_mul(mc_ld(V[11]), mc_ld(U[10])));
    const __m128d r22 = mc_add(mc_add(mc_mul(mc_ld(V[8]), mc_ld(U[8])), mc_mul(mc_ld(V[5]), mc_ld(U[5]))), mc_mul(mc_ld(V[11]), mc_ld(U[11])));

    _mm_store_sd(&a3[0][0], r00);
    _mm_store_sd(&a3[0][1], r01);
    _mm_store_sd(&a3[0][2], r02);
    _mm_store_sd(&a3[1][0], r10);
    _mm_store_sd(&a3[1][1], r11);
    _mm_store_sd(&a3[1][2], r12);
    _mm_store_sd(&a3[2][0], r20);
    _mm_store_sd(&a3[2][1], r21);
    _mm_store_sd(&a3[2][2], r22);



    U[1] = u[1];
    U[0] = u[0];
    U[2] = u[2];
    V[0] = v[0];
    const __m128d t0 = mc_sub(mc_ld(V[0]), mc_add(mc_add(mc_mul(mc_ld(U[1]), r01), mc_mul(mc_ld(U[0]), r00)), mc_mul(mc_ld(U[2]), r02)));
    _mm_store_sd(&a3[0][3], t0);

    V[1] = v[1];
    const __m128d t1 = mc_sub(mc_ld(V[1]), mc_add(mc_add(mc_mul(mc_ld(U[1]), r11), mc_mul(mc_ld(U[0]), r10)), mc_mul(mc_ld(U[2]), r12)));
    _mm_store_sd(&a3[1][3], t1);

    a3[3][0] = 0.0;
    a3[3][1] = 0.0;
    a3[3][2] = 0.0;
    a3[3][3] = 1.0;

    V[2] = v[2];
    const __m128d t2 = mc_sub(mc_ld(V[2]), mc_add(mc_add(mc_mul(mc_ld(U[1]), r21), mc_mul(mc_ld(U[0]), r20)), mc_mul(mc_ld(U[2]), r22)));
    _mm_store_sd(&a3[2][3], t2);
}
