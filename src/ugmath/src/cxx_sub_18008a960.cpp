















#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <emmintrin.h>

extern "C" void* sub_180079AB0(unsigned long long n);
extern "C" double sub_180093E90(void* self, long long n);

struct B30View { long long pad; const double* x; };
struct B30Src  { long long pad0; const double* x_unused; long long n; };
extern "C" __m128d sub_18007F750(const void* a, const void* unused, const void* s);
extern "C" __m128d sub_18007FBC0(const void* a, const void* unused, const void* s);

extern "C" __int64 sub_18007C0E0(long long* a1, unsigned long long* a2, double* a3, double* a4,
                                long long a5, long long a6);


extern "C" void sub_1800764D0(const long long* a1, const long long* a2, const double* a3,
                              long long a4, long long a5, long long a6);
struct D7C0A1 { long long x; long long n; long long pad2; long long pad3;
                long long pad4; long long pad5; long long ctx; };
struct D7C0A2 { unsigned long long dst; long long m; long long pad2; long long pad3;
                long long pad4; long long pad5; long long pad6; long long pad7;
                long long pad8; long long ctx; };
struct D764A1 { long long mat; long long count; long long nrows; long long desc; long long ld2; };

extern "C" long long sub_18008A960(long long* a1, long long a2) {
    long long v103 = 0;
    long long v51 = 0;
    long long v52 = 0;
    const long long ld = a1[1];
    const long long n = a1[2];
    long long v5 = ld;
    if (n < ld) v5 = n;
    long long v6 = 0;
    const long long v78 = a1[1];
    const long long v88 = n;
    const long long v106 = v5;


    if (v5 != a1[4]) {
        std::free(reinterpret_cast<void*>(a1[3]));
        a1[3] = v5 <= 0 ? 0 : reinterpret_cast<long long>(sub_180079AB0((unsigned long long)v5));
    }
    a1[4] = v5;
    if (n != a1[10]) {
        std::free(reinterpret_cast<void*>(a1[9]));
        a1[9] = n <= 0 ? 0 : reinterpret_cast<long long>(sub_180079AB0((unsigned long long)n));
    }
    a1[10] = n;
    const long long v7 = a1[2];
    if (v7 != a1[8]) {
        std::free(reinterpret_cast<void*>(a1[7]));
        a1[7] = v7 <= 0 ? 0 : reinterpret_cast<long long>(sub_180079AB0((unsigned long long)v7));
    }
    long long* v8 = a1 + 11;
    a1[8] = v7;
    long long v74 = 0;
    if (n != a1[12]) {
        std::free(reinterpret_cast<void*>(*v8));
        *v8 = n <= 0 ? 0 : reinterpret_cast<long long>(sub_180079AB0((unsigned long long)n));
    }
    a1[12] = n;
    if (n == a1[14]) {
        a1[14] = n;
        if (n <= 0) goto LABEL_29;
    } else {
        std::free(reinterpret_cast<void*>(a1[13]));
        if (n <= 0) {
            a1[13] = 0;
            a1[14] = n;
            goto LABEL_29;
        }
        a1[13] = reinterpret_cast<long long>(sub_180079AB0((unsigned long long)n));
        a1[14] = n;
    }


    for (long long i = 0; i < n; ++i) {
        const long long v10 = a1[1];
        const long long v11 = *a1;
        B30View vv;
        B30Src ss;
        vv.pad = 0;
        vv.x = reinterpret_cast<const double*>(v11 + 8 * i * v10);
        ss.pad0 = 0;
        ss.x_unused = vv.x;
        ss.n = v10;
        double v12 = 0.0;
        if (v10)
            v12 = _mm_cvtsd_f64(sub_18007F750(&vv, &v103, &ss));
        const double nr = std::sqrt(v12);
        *reinterpret_cast<double*>(a1[13] + 8 * i) = nr;
        *reinterpret_cast<double*>(*v8 + 8 * i) = nr;
    }

LABEL_29:

    const long long v104 = *v8;
    const double v14 = _mm_cvtsd_f64(sub_18007FBC0(&v104, &v103, a1 + 11));
    a1[18] = v5;
    const double v15 = std::sqrt(2.220446049250313e-16);
    a1[17] = 0;
    const double v16 = (double)(int)ld;
    long long v17 = 0;
    const double v18 = v14 * 2.220446049250313e-16 * (v14 * 2.220446049250313e-16) / v16;

    long long v69;
    if (v5 <= 0) {
        sub_180093E90(a1 + 5, (long long)n);
        v69 = 0;
    } else {
        long long v19 = n - v78;
        long long v20 = v78 - 1;
        long long v105 = v78 - 1;
        const long long v79 = n - v78;
        do {
            const long long v21 = v8[1];
            const long long v22 = *v8;
            const long long v23 = v20 + v19 + 1;
            double v24 = 0.0;
            const double* v25 = reinterpret_cast<const double*>(v22 + 8 * (v21 - v23));
            long long j = -1;
            if (v23) {
                v24 = *v25;
                long long v27 = 1;
                for (j = 0; v27 < v23; ++v27) {
                    if (v25[v27] > v24) { v24 = v25[v27]; j = v27; }
                }
            }
            const long long v28 = j + v17;
            if (a1[18] == v106 && (double)((int)v20 + 1) * v18 > v24 * v24)
                a1[18] = v17;
            *reinterpret_cast<long long*>(a1[7] + 8 * v17) = v28;
            if (v17 != v28) {
                const long long v29 = a1[1];
                const long long v30 = *a1;
                long long v31 = v29;
                long long* r17 = reinterpret_cast<long long*>(v30 + 8 * v17 * v29);
                long long* r28 = reinterpret_cast<long long*>(v30 + 8 * v28 * v29);
                long long v33 = 0;
                if ((reinterpret_cast<long long>(r17) & 7) == 0)
                    v33 = -static_cast<int>(reinterpret_cast<long long>(r17) >> 3) & 1;
                if (v33 < v29) v31 = v33;
                const long long v34 = v31 + 2 * ((v29 - v31) / 2);
                for (long long s = 0; s < v31; ++s) {
                    const long long t = r17[s];
                    r17[s] = r28[s];
                    r28[s] = t;
                }
                for (long long s = v31; s < v34; s += 2) {
                    const long long t0 = r17[s];
                    const long long t1 = r17[s + 1];
                    r17[s] = r28[s];
                    r17[s + 1] = r28[s + 1];
                    r28[s] = t0;
                    r28[s + 1] = t1;
                }
                for (long long s = v34; s < v29; ++s) {
                    const long long t = r17[s];
                    r17[s] = r28[s];
                    r28[s] = t;
                }
                long long* dg = reinterpret_cast<long long*>(a1[11]);
                const long long t1 = dg[v17];
                dg[v17] = dg[v28];
                dg[v28] = t1;
                long long* nm = reinterpret_cast<long long*>(a1[13]);
                const long long t2 = nm[v17];
                nm[v17] = nm[v28];
                nm[v28] = t2;
                ++v74;
            }

            const long long v40 = *a1;
            const long long v41 = a1[1];
            const long long col = v40 + 8 * v17 * v41;
            const long long v76 = v41 - (v20 + 1);
            long long ctx2[2] = {0, a1[11]};
            D7C0A1 d7c;
            d7c.x = col + 8 * v76;
            d7c.n = v20 + 1;
            d7c.pad2 = d7c.pad3 = d7c.pad4 = d7c.pad5 = 0;
            d7c.ctx = (long long)ctx2;
            D7C0A2 d7c2;
            d7c2.dst = (unsigned long long)(col + 8 * (v17 + 1));
            d7c2.m = v20;
            d7c2.pad2 = d7c2.pad3 = d7c2.pad4 = d7c2.pad5 = 0;
            d7c2.pad6 = d7c2.pad7 = d7c2.pad8 = 0;
            d7c2.ctx = (long long)a1;
            double v87 = 0.0;
            sub_18007C0E0(&d7c.x, reinterpret_cast<unsigned long long*>(&d7c2.dst),
                          reinterpret_cast<double*>(a1[3] + 8 * v17), &v87,
                          col + 8 * v17 * v41, v41);
            const double v42 = v87;
            *reinterpret_cast<double*>(*a1 + 8 * v17 * (a1[1] + 1)) = v42;
            const double v43 = std::fabs(v42);
            if (v43 > *reinterpret_cast<double*>(reinterpret_cast<char*>(a1) + 0x88))
                *reinterpret_cast<double*>(reinterpret_cast<char*>(a1) + 0x88) = v43;

            const long long v44 = a1[1];
            const long long v45 = *a1;
            const long long v46 = a1[2];
            const long long v84 = v44 - (v20 + 1);
            const long long v47 = v46 - (v20 + v79);
            const long long v48 = v47 * v44;
            const long long v80 = v45 + 8 * (v84 + v48);
            D764A1 d764;
            d764.mat = v80;
            d764.count = v20 + 1;
            d764.nrows = v20 + v79;
            d764.desc = (long long)a1;
            d764.ld2 = v84;
            long long a2d[13] = {0};
            a2d[0] = *a1 + 8 * (v17 * v41 + v17 + 1);
            a2d[1] = v20;
            a2d[6] = (long long)a1;
            sub_1800764D0(&d764.mat, a2d, reinterpret_cast<const double*>(a1[3] + 8 * v17),
                          (long long)(a1[9] + 8 + 8 * v17), v45 + 8 * v17 * v44, v44);
            v51 = v88;
            v52 = v17 + 1;
            long long v89 = v17 + 1;
            long long v53 = v17 + 1;
            if (v17 + 1 < v88) {
                do {
                    const double v54 = *reinterpret_cast<double*>(*v8 + 8 * v53);
                    if (v54 != 0.0) {
                        const long long v55 = a1[1];
                        const long long v56 = *a1;
                        const long long v57 = a1[13];
                        const double v58 = std::fabs(*reinterpret_cast<double*>(*a1 + 8 * (v53 * v55 + v17)));
                        const double v59 = _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(0.0),
                                _mm_set_sd((1.0 - v58 / v54) * (v58 / v54 + 1.0))));
                        const double v54d = v54 / *reinterpret_cast<double*>(v57 + 8 * v53);
                        if (!(v15 >= v54d * v54d * v59)) {
                            const double v62 = std::sqrt(v59);
                            *reinterpret_cast<double*>(*v8 + 8 * v53) = v62 * v54;
                        } else {
                            B30View dv;
                            B30Src ds;
                            dv.pad = 0;
                            dv.x = reinterpret_cast<const double*>(v56 + 8 * (v53 * v55 + v17 + 1));
                            ds.pad0 = 0;
                            ds.x_unused = dv.x;
                            ds.n = v20;
                            double v60 = 0.0;
                            if (v20)
                                v60 = _mm_cvtsd_f64(sub_18007F750(&dv, &v104, &ds));
                            const double v61 = std::sqrt(v60);
                            *reinterpret_cast<double*>(v57 + 8 * v53) = v61;
                            *reinterpret_cast<double*>(*v8 + 8 * v53) = *reinterpret_cast<double*>(a1[13] + 8 * v53);
                        }
                    }
                    ++v53;
                } while (v53 < v51);
                v20 = v105;
                v52 = v89;
            }
            v19 = v79;
            --v20;
            v17 = v52;
            v105 = v20;
        } while (v52 < v106);
        sub_180093E90(a1 + 5, (long long)v51);

        const long long v63 = v106;
        long long v64 = 0;
        long long v65 = 0;
        long long v66 = a1[5];
        do {
            v64 += 8;
            ++v65;
            const long long v67 = *reinterpret_cast<int*>(a1[7] + v64 - 8);
            const int v68 = *reinterpret_cast<int*>(v66 + 4 * (v65 - 1));
            *reinterpret_cast<int*>(v66 + 4 * (v65 - 1)) = *reinterpret_cast<int*>(v66 + 4 * v67);
            *reinterpret_cast<int*>(v66 + 4 * v67) = v68;
        } while (v65 < v63);
        v69 = v74;
    }
    *reinterpret_cast<char*>(reinterpret_cast<char*>(a1) + 120) = 1;
    const long long result = 2LL * ((v69 & 1) == 0) - 1;
    a1[19] = result;
    return result;
}
