







#include <cstdint>
#include <cstring>



extern "C" {
extern int g_ugm_hlr_E0584;
extern double g_ugm_hlr_eye[3];
extern double g_ugm_hlr_axis[3][3];
extern double g_ugm_hlr_E06B0;
extern int g_ugm_hlr_vloc_norm;
extern double g_ugm_hlr_E07C8;
extern double g_ugm_hlr_E0880;
extern int g_ugm_hlr_E08B4;
extern int g_ugm_hlr_E08B8;
extern int g_ugm_hlr_E08BC;
extern int g_ugm_hlr_E08C0;
extern int g_ugm_hlr_E08C4;
extern int g_ugm_hlr_E08C8;
extern unsigned long long g_ugm_hlr_span[15];
extern unsigned long long g_ugm_hlr_sentinel[8];
}

long long b15_BDB0();
long long b15_BDF0(double*, double*, double*, double*, double*, double*);
long long b15_A260(double*, double*, double*, double*, double*, double*);


typedef void (__cdecl *b15_hlr_line_cb_t)(const double* const, const double* const,
                                          int, void*);
extern b15_hlr_line_cb_t g_ugm_hlr_line_cb;
typedef long long (__cdecl *b15_cb_ll_t)(double*, double*, int, void*);

static inline double b15_abs(double x)
{
    uint64_t u;
    memcpy(&u, &x, 8);
    u &= 0x7FFFFFFFFFFFFFFFull;
    memcpy(&x, &u, 8);
    return x;
}

static inline double b15_neg(double x)
{
    uint64_t u;
    memcpy(&u, &x, 8);
    u ^= 0x8000000000000000ull;
    memcpy(&x, &u, 8);
    return x;
}

static __forceinline char* b15_G(unsigned rva)
{
    switch (rva)
    {
    case 0xE0584: return (char*)&g_ugm_hlr_E0584;
    case 0xE0588: return (char*)&g_ugm_hlr_eye[0];
    case 0xE0590: return (char*)&g_ugm_hlr_eye[1];
    case 0xE0598: return (char*)&g_ugm_hlr_eye[2];
    case 0xE0660: return (char*)&g_ugm_hlr_axis[0][0];
    case 0xE0668: return (char*)&g_ugm_hlr_axis[0][1];
    case 0xE0670: return (char*)&g_ugm_hlr_axis[0][2];
    case 0xE0678: return (char*)&g_ugm_hlr_axis[1][0];
    case 0xE0680: return (char*)&g_ugm_hlr_axis[1][1];
    case 0xE0688: return (char*)&g_ugm_hlr_axis[1][2];
    case 0xE0690: return (char*)&g_ugm_hlr_axis[2][0];
    case 0xE0698: return (char*)&g_ugm_hlr_axis[2][1];
    case 0xE06A0: return (char*)&g_ugm_hlr_axis[2][2];
    case 0xE06B0: return (char*)&g_ugm_hlr_E06B0;
    case 0xE07A4: return (char*)&g_ugm_hlr_vloc_norm;
    case 0xE07C8: return (char*)&g_ugm_hlr_E07C8;
    case 0xE0880: return (char*)&g_ugm_hlr_E0880;
    case 0xE08B4: return (char*)&g_ugm_hlr_E08B4;
    case 0xE08B8: return (char*)&g_ugm_hlr_E08B8;
    case 0xE08BC: return (char*)&g_ugm_hlr_E08BC;
    case 0xE08C0: return (char*)&g_ugm_hlr_E08C0;
    case 0xE08C4: return (char*)&g_ugm_hlr_E08C4;
    case 0xE08C8: return (char*)&g_ugm_hlr_E08C8;
    case 0xE08E0: return (char*)&g_ugm_hlr_sentinel[0];
    }
    if (rva >= 0xE07D0 && rva <= 0xE0840)
        return (char*)&g_ugm_hlr_span[(rva - 0xE07D0) / 8];
    return nullptr;
}
static inline int b15_Gi(char* b, unsigned rva) { (void)b; int v; memcpy(&v, b15_G(rva), 4); return v; }
static inline void b15_Si(char* b, unsigned rva, int v) { (void)b; memcpy(b15_G(rva), &v, 4); }
static inline double b15_Gd(char* b, unsigned rva) { (void)b; double v; memcpy(&v, b15_G(rva), 8); return v; }

struct B15Node
{
    void* p0;
    void* p1;
    void* p2;
    float nx, ny, nz, nd;
    void* next;
};

extern "C" long long sub_18004B2C0(double a1, double a2, double a3,
                                   double a4, double a5, double a6,
                                   void* a7, long long a8)
{
    char* b = nullptr;
    void* const sentinel = (void*)g_ugm_hlr_sentinel;
    const int persp = b15_Gi(b, 0xE07A4);



    long long rax = 0;

    if (a7 != sentinel)
    {
        int cB4 = b15_Gi(b, 0xE08B4);
        int cB8 = b15_Gi(b, 0xE08B8);
        int cBC = b15_Gi(b, 0xE08BC);
        int cC4 = b15_Gi(b, 0xE08C4);
        void* cur = a7;
        for (;;)
        {
            B15Node* nd = (B15Node*)cur;
            const double nx = (double)nd->nx;
            const double ny = (double)nd->ny;
            const double nz = (double)nd->nz;
            const double nw = (double)nd->nd;
            const double eps = b15_Gd(b, 0xE0880);


            const double d96 = ((nx * a1 + ny * a2) + nz * a3);
            const double d97 = ((nx * a4 + ny * a5) + nz * a6);
            const double tol = b15_abs(nw) * eps + eps;

            if (!(tol >= nw - d96) || !(tol >= nw - d97))
            {
                double e26, e27, e28, e25;
                if (persp)
                {

                    e26 = a2 * a6 - a3 * a5;
                    e27 = a3 * a4 - a1 * a6;
                    e28 = a1 * a5 - a2 * a4;
                    e25 = 0.0;
                }
                else
                {

                    e26 = a5 - a2;
                    e27 = b15_neg(a4 - a1);
                    e28 = 0.0;
                    e25 = e26 * a1 + e27 * a2;
                }

                const float* f0 = (const float*)nd->p0;
                const float* f1 = (const float*)nd->p1;
                const float* f2 = (const float*)nd->p2;

                double x0 = (double)f0[0], y0 = (double)f0[1], z0 = (double)f0[2];
                double x1 = (double)f1[0], y1 = (double)f1[1], z1 = (double)f1[2];
                double x2 = (double)f2[0], y2 = (double)f2[1], z2 = (double)f2[2];


                double v41 = (y0 * e27 + x0 * e26 + z0 * e28) - e25;
                double v90 = (y1 * e27 + x1 * e26 + z1 * e28) - e25;
                double v86 = (y2 * e27 + x2 * e26 + z2 * e28) - e25;


                int c0, c1, c2;
                if (!(v41 > 0.0))
                    c0 = ((!(0.0 > v41)) ? 1 : 0) - 1;
                else
                    c0 = 1;
                if (!(v90 > 0.0))
                    c1 = ((!(0.0 > v90)) ? 1 : 0) - 1;
                else
                    c1 = 1;
                if (!(v86 > 0.0))
                    c2 = ((!(0.0 > v86)) ? 1 : 0) - 1;
                else
                    c2 = 1;
                int sum = c0 + c1 + c2;
                if (sum < 0)
                    sum = -sum;
                if (sum >= 2)
                {
                    b15_Si(b, 0xE08B8, ++cB8);
                    cur = nd->next;
                    if (cur == sentinel)
                        break;
                    continue;
                }

                rax = 0;
                double tmin = 1.0;
                double tmax = 0.0;
                int f48 = 0;
                int f50 = 0;

                for (int it = 0; it < 3; ++it)
                {
                    double e54, e57, e58, e56;
                    if (persp)
                    {

                        e54 = z1 * y0 - y1 * z0;
                        e57 = x1 * z0 - z1 * x0;
                        e58 = y1 * x0 - x1 * y0;
                        e56 = 0.0;
                    }
                    else
                    {

                        e54 = y1 - y0;
                        e57 = b15_neg(x1 - x0);
                        e58 = 0.0;
                        e56 = e57 * y0 + e54 * x0;
                    }

                    const double q60 = ((e57 * y2 + e54 * x2) + e58 * z2) - e56;
                    const double q61 = ((e54 * a4 + e57 * a5) + e58 * a6) - e56;
                    const double q62 = ((e54 * a1 + e57 * a2) + e58 * a3) - e56;

                    int c63, r61;
                    if (!(q60 > 0.0))
                    {

                        if (!(0.0 > q60))
                            goto reject_node;
                        c63 = (q62 > 0.0);
                        r61 = (q61 > 0.0);
                        if (c63 && q61 >= 0.0)
                            goto reject_node;
                        if (r61 && q62 >= 0.0)
                            goto reject_node;
                    }
                    else
                    {

                        c63 = (q62 < 0.0);
                        r61 = (q61 < 0.0);
                        if (c63 && 0.0 >= q61)
                            goto reject_node;
                        if (r61 && 0.0 >= q62)
                            goto reject_node;
                    }


                    {
                        const double d66 = q61 - q62;
                        f48 |= c63;
                        f50 |= r61;
                        double t67;
                        if (!(0.0 >= b15_abs(d66)))
                            t67 = b15_neg(q62) / d66;
                        else
                            t67 = 254000.0;

                        const double dd = v90 - v41;
                        if (!(0.0 >= b15_abs(dd)))
                        {
                            const double t68 = b15_neg(v41) / dd;
                            if (t68 >= 0.0 && 1.0 >= t68 &&
                                t67 >= 0.0 && 1.0 >= t67)
                            {
                                if (!(t67 > tmin))
                                    tmin = t67;
                                if (!(tmax > t67))
                                    tmax = t67;
                            }
                        }
                    }


                    {
                        double tx = x0, ty = y0, tz = z0;
                        double d0 = v41;
                        x0 = x1; y0 = y1; z0 = z1;
                        x1 = x2; y1 = y2; z1 = z2;
                        x2 = tx; y2 = ty; z2 = tz;
                        v41 = v90;
                        v90 = v86;
                        v86 = d0;
                    }
                }

                if (!f48 && !f50)
                {
                    b15_Si(b, 0xE08C0, b15_Gi(b, 0xE08C0) + 1);
                    return rax;
                }


                const double ddx = a4 - a1;
                const double ddy = a5 - a2;
                const double ddz = a6 - a3;
                const double p1x = ddx * tmin + a1;
                const double p1y = ddy * tmin + a2;
                const double p1z = ddz * tmin + a3;
                const double p2x = ddx * tmax + a1;
                const double p2y = ddy * tmax + a2;
                const double p2z = ddz * tmax + a3;
                const double g1 = ((p1y * ny + p1x * nx) + p1z * nz) - nw;
                if (g1 > tol)
                    goto reject_plane;
                const double g2 = ((p2y * ny + p2x * nx) + p2z * nz) - nw;
                if (g2 > tol)
                    goto reject_plane;

                {
                    const double limrec = tol + nw;
                    void** head = (void**)&g_ugm_hlr_span[14];
                    void* prev = *head;
                    if (f48 || d96 > limrec)
                    {
                        long long rec = b15_BDB0();
                        rax = rec;
                        double* r = (double*)rec;
                        r[0] = a1; r[1] = a2; r[2] = a3;
                        r[3] = p1x; r[4] = p1y; r[5] = p1z;
                        *(void**)(rec + 48) = nd->next;
                        *(void**)(rec + 56) = prev;
                        *head = (void*)rec;
                        prev = (void*)rec;
                    }
                    if (f50 || d97 > limrec)
                    {
                        long long rec = b15_BDB0();
                        rax = rec;
                        double* r = (double*)rec;
                        r[0] = p2x; r[1] = p2y; r[2] = p2z;
                        r[3] = a4; r[4] = a5; r[5] = a6;
                        *(void**)(rec + 48) = nd->next;
                        *(void**)(rec + 56) = prev;
                        *head = (void*)rec;
                    }
                }
                b15_Si(b, 0xE08C8, b15_Gi(b, 0xE08C8) + 1);
                return rax;
            }

            b15_Si(b, 0xE08B4, ++cB4);
            cur = nd->next;
            if (cur == sentinel)
                break;
            continue;

        reject_node:
            b15_Si(b, 0xE08BC, ++cBC);
            cur = nd->next;
            if (cur == sentinel)
                break;
            continue;

        reject_plane:
            b15_Si(b, 0xE08C4, ++cC4);
            cur = nd->next;
            if (cur == sentinel)
                break;
            continue;
        }
    }

    {
        double v81;
        if (b15_Gi(b, 0xE0584))
        {
            long long r;
            if (persp)
                r = b15_BDF0(&a1, &a2, &a3, &a4, &a5, &a6);
            else
                r = b15_A260(&a1, &a2, &a3, &a4, &a5, &a6);
            if ((int)r != 0)
                return r;
        }
        v81 = a3;
        const double off = b15_Gd(b, 0xE06B0);
        if (persp)
            v81 = v81 + off;
        double v83 = a6;
        if (persp)
            v83 = v83 + off;

        const double m00 = b15_Gd(b, 0xE0660), m01 = b15_Gd(b, 0xE0678),
                     m02 = b15_Gd(b, 0xE0690), t0 = b15_Gd(b, 0xE0588);
        const double m10 = b15_Gd(b, 0xE0668), m11 = b15_Gd(b, 0xE0680),
                     m12 = b15_Gd(b, 0xE0698), t1 = b15_Gd(b, 0xE0590);
        const double m20 = b15_Gd(b, 0xE0670), m21 = b15_Gd(b, 0xE0688),
                     m22 = b15_Gd(b, 0xE06A0), t2 = b15_Gd(b, 0xE0598);

        double p[3], q[3];
        p[0] = (m00 * a1 + m01 * a2 + m02 * v81) + t0;
        p[1] = (m10 * a1 + m11 * a2 + m12 * v81) + t1;
        p[2] = (m20 * a1 + m21 * a2 + m22 * v81) + t2;
        q[0] = (m00 * a4 + m01 * a5 + m02 * v83) + t0;
        q[1] = (m10 * a4 + m11 * a5 + m12 * v83) + t1;
        q[2] = (m20 * a4 + m21 * a5 + m22 * v83) + t2;

        return reinterpret_cast<b15_cb_ll_t>(g_ugm_hlr_line_cb)(
            p, q, 0, reinterpret_cast<void*>(static_cast<intptr_t>(a8)));
    }
}
