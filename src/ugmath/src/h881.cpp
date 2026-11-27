




















#include <math.h>
#include <string.h>




#define B14_NOINLINE __declspec(noinline)





static double g_b14_len_tol = 1.0e-8;
static double g_b14_acom_slot1 = 1.0e-8;
static double g_b14_acom_slot4 = 1.0e-6;

static B14_NOINLINE void b14_env_set_length_tolerance(double v) { g_b14_len_tol = v; }
static B14_NOINLINE void b14_env_set_acom(double slot1, double slot4) {
    g_b14_acom_slot1 = slot1;
    g_b14_acom_slot4 = slot4;
}

static B14_NOINLINE double EQ_ask_length_tolerance() { return g_b14_len_tol; }

static B14_NOINLINE double EQ_ask_number_tolerance() { return 1.0e-10; }





static inline double b14_dmax0(double x) {
    if (x != x) return x;
    if (x > 0.0) return x;
    if (x == 0.0) return x;
    return 0.0;
}




static const double B14_PI  = 3.141592653589793;
static const double B14_2PI = 6.283185307179586;
static const double B14_PI_2 = 1.5707963267948966;
static const double B14_3PI_2 = 4.712388980384690;




namespace b14_local {
struct Vector3 { double x, y, z; };
typedef Vector3 B14Vec3;
}



static B14_NOINLINE int b14_VEC3_unitize(const b14_local::B14Vec3* v, double tol, double* len_out,
                               b14_local::B14Vec3* out) {
    double n = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    if (tol >= n) {
        *len_out = 0.0;
        out->x = 0.0;
        out->y = 0.0;
        out->z = 0.0;
        return 0;
    }
    double inv = 1.0 / n;
    *len_out = n;
    out->x = v->x * inv;
    out->y = v->y * inv;
    out->z = v->z * inv;
    return 1;
}


static B14_NOINLINE void b14_vunt3(const double* v, int* flag, double* out) {
    b14_local::B14Vec3 t;
    t.x = v[0];
    t.y = v[1];
    t.z = v[2];
    double len = 0.0;
    b14_local::B14Vec3 o;
    *flag = b14_VEC3_unitize(&t, EQ_ask_length_tolerance(), &len, &o);
    out[0] = o.x;
    out[1] = o.y;
    out[2] = o.z;
}


static B14_NOINLINE void b14_vcru3(const double* a, const double* b, int* flag, double* out) {
    b14_local::B14Vec3 c;
    c.x = a[1] * b[2] - a[2] * b[1];
    c.y = b[0] * a[2] - a[0] * b[2];
    c.z = a[0] * b[1] - b[0] * a[1];
    double len = 0.0;
    b14_local::B14Vec3 o;
    *flag = b14_VEC3_unitize(&c, EQ_ask_length_tolerance(), &len, &o);
    out[0] = o.x;
    out[1] = o.y;
    out[2] = o.z;
}


static B14_NOINLINE void b14_movf(const int* count, const double* in, double* out) {
    if (*count > 0) memcpy(out, in, (size_t)(unsigned)*count * sizeof(double));
}






static inline double b14_tol_for_mode(const int* mode) {
    if (*mode == 0) return EQ_ask_number_tolerance();
    if (*mode == 1) return g_b14_acom_slot1;
    return g_b14_acom_slot4;
}


static B14_NOINLINE void b14_h805(const double* a1, const double* a2, const int* a3, int* a4) {
    *a4 = b14_tol_for_mode(a3) >= fabs(*a1 - *a2);
}


static B14_NOINLINE void b14_h806(const double* a1, const double* a2, const double* a3, int* a4) {
    *a4 = 0;
    double t = *a3;
    if (*a3 < 0.0) t = -t;
    if (t >= fabs(*a1 - *a2)) *a4 = 1;
}


static B14_NOINLINE void b14_h804(double* a1, const double* a2, const int* a3, int* a4) {
    double tol = b14_tol_for_mode(a3);
    if (tol >= fabs(*a1 - *a2)) {
        *a4 = 2;
        *a1 = *a2;
        return;
    }
    if (!(*a1 > *a2)) {
        *a4 = 1;
        return;
    }
    double tol2 = b14_tol_for_mode(a3);
    int in2 = tol2 >= fabs(*a1 - a2[1]);
    if (in2) {
        *a4 = 4;
        *a1 = a2[1];
        return;
    }
    *a4 = 3;
    if (*a1 > a2[1]) *a4 = 5;
}





static B14_NOINLINE void b14_h014(double* a1, double* a2, double* a3, int* a4, int* a5,
                        int* a6) {
    *a6 = 0;
    *a5 = 0;
    *a4 = 1;
    a2[0] = 0.0;
    a2[1] = 0.0;
    a3[0] = 0.0;
    a3[1] = 0.0;

    double v11 = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    if (EQ_ask_number_tolerance() >= fabs(v11)) {
        *a4 = 4;
        return;
    }
    double x = a1[0] / v11;
    double y = a1[1] / v11;
    double z = a1[2] / v11;
    double ay = fabs(y);


    if (!(EQ_ask_number_tolerance() >= fabs(z))) {
        *a5 = 2;
        double t2 = z + z;
        double disc;

        if (!(EQ_ask_number_tolerance() >= ay)) {
            disc = y * y - z * 4.0 * x;
        } else {
            disc = z * -4.0 * x;
        }
        double ad = fabs(disc);
        double sq;

        if (!(EQ_ask_number_tolerance() >= ad)) {
            sq = sqrt(ad);
        } else {
            sq = 0.0;
        }
        double ny = -y;

        if (!(disc > 0.0 - EQ_ask_number_tolerance())) {
            *a4 = 2;
            *a2 = ny / t2;
            *a3 = sq / t2;
            a2[1] = *a2;
            a3[1] = -*a3;
        } else {
            *a4 = 3;
            *a6 = 2;
            *a2 = (sq - y) / t2;
            a2[1] = (ny - sq) / t2;
        }
        return;
    }

    if (!(EQ_ask_number_tolerance() >= ay)) {
        *a4 = 3;
        *a5 = 1;
        *a6 = 1;
        *a2 = -x / y;
        return;
    }

    if (EQ_ask_number_tolerance() >= fabs(x)) *a4 = 4;
}





static inline int b14_h016_scan_a(double v) {
    double s = fabs(v);
    int v26 = 0, v27 = 1, v29 = 0;
    do {
        double v32 = s * 10.0;
        if (v32 > 10.0) break;
        double v33 = v32 * 10.0;
        v26 = v29 + 1;
        if (v33 > 10.0) break;
        double v34 = v33 * 10.0;
        int v35 = v29 + 2;
        ++v26;
        if (v34 > 10.0) break;
        double v36 = v34 * 10.0;
        v26 = v35 + 1;
        if (v36 > 10.0) break;
        s = v36 * 10.0;
        int v37 = v35 + 2;
        ++v26;
        if (s > 10.0) break;
        v27 += 5;
        v26 = v37 + 1;
        v29 = v37 + 1;
    } while (v27 <= 100);
    return v26;
}

static inline int b14_h016_scan_b(double v) {
    double s = fabs(v);
    int v38 = 0;
    do {
        double v40 = s * 10.0;
        if (v40 > 10.0) break;
        double v41 = v40 * 10.0;
        if (v41 > 10.0) { ++v38; break; }
        double v42 = v41 * 10.0;
        if (v42 > 10.0) { v38 += 2; break; }
        double v43 = v42 * 10.0;
        if (v43 > 10.0) { v38 += 3; break; }
        s = v43 * 10.0;
        if (s > 10.0) { v38 += 4; break; }
        v38 += 5;
    } while (v38 <= 99);
    return v38;
}


static inline double b14_h016_pow10(int e) {
    double base = (e < 0) ? 0.1 : 10.0;
    unsigned k = (unsigned)(e < 0 ? -e : e);
    double r = 1.0;
    while (1) {
        if (k & 1) r = r * base;
        k >>= 1;
        if (!k) break;
        base = base * base;
    }
    return r;
}


static B14_NOINLINE void b14_h018(double* a1, int* a2, double* a3) {
    double x = a1[0];
    double y = a1[1];
    double mag = sqrt(y * y + x * x);
    double ang = 0.0;
    if (x == 0.0) {
        if (y > 0.0) ang = B14_PI_2;
        if (y < 0.0) ang = B14_3PI_2;
    } else {
        ang = atan(y / x);
    }
    if (y == 0.0) {
        if (x < 0.0) ang = B14_PI;
        else ang = 0.0;
    }
    if (x > 0.0 && y < 0.0) ang = ang + B14_2PI;
    if (x < 0.0) {
        if (y < 0.0) ang = ang + B14_PI;
        if (y > 0.0) ang = ang + B14_PI;
    }
    double n = (double)*a2;
    double an = ang / n;
    double r = pow(mag, 1.0 / n);
    a3[0] = cos(an) * r;
    a3[1] = sin(an) * r;
}

static B14_NOINLINE void b14_h016(double* a1, double* a2, double* a3, int* a4, int* a5,
                        int* a6) {
    const double E158 = 1.0000000000000001e-15;
    const double E160 = 1e-25;
    const double E168 = 1.0000000000000001e-37;
    *a6 = 0;

    double v15 = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2] +
                      a1[3] * a1[3]);
    double v17 = sqrt(sqrt(v15));

    if (EQ_ask_number_tolerance() >= fabs(v17)) {
        *a4 = 4;
        return;
    }
    double v19 = a1[0] / v15;
    double v20 = a1[1] / v15;
    double v21 = a1[2] / v15;
    double v18 = a1[3] / v15;
    int v79 = 3;


    if (!(EQ_ask_number_tolerance() >= fabs(v18))) {
        double v22 = v19 / v18;
        double vy = v20 / v18;
        double vz = v21 / v18;
        *a5 = 3;
        *a4 = 3;

    if (!(EQ_ask_number_tolerance() >= fabs(v22))) {
            double b = vy - vz * vz / 3.0;
            double c = v22 - vz * vy / 3.0 +
                       (vz * vz * vz + vz * vz * vz) / 27.0;
            if (E160 > fabs(b)) b = 0.0;
            if (E168 > fabs(c)) c = 0.0;

            double D = b * b * b * -4.0 - c * c * 27.0;
            int v26 = b14_h016_scan_a(b);
            int v38 = b14_h016_scan_b(c);
            int v44 = v38 - 3;
            if (v44 < v26) v26 = v44;
            double v45;
            if (v26 >= 6) {
                v45 = b14_h016_pow10(6 * (v26 / 2)) * D;
            } else {
                v45 = b * b * b * -4.0 - c * c * 27.0;
            }
            if (E158 > fabs(v45)) D = 0.0;

            double v74[2] = {0.0, 0.0};
            if (D < 0.0) v74[0] = sqrt(D * -3.0);
            if (D >= 0.0) v74[1] = sqrt(D * 3.0);

            double v54[2];
            v54[0] = v74[0] * 1.5;
            v54[1] = v74[1] * 1.5;
            double v76[2];
            v76[0] = c * -13.5;
            v76[1] = 0.0;
            double v55 = sqrt(3.0);
            double v56 = v55 * 0.5;
            double v57 = v55 * -0.5;
            double v74b[2];
            v74b[0] = -0.5;
            v74b[1] = v56;
            double v75[2];
            v75[0] = -0.5;
            v75[1] = v57;
            double v24 = 0.0;


            if (!(D < 0.0)) {
                *a6 = 3;
                v75[0] = v54[0] + v76[0];
                v75[1] = v54[1] + v76[1];
                b14_h018(v75, &v79, v76);
                double v70 = v76[1];
                double v71 = v76[0] * -0.5;
                a2[0] = v76[0] * 2.0 / 3.0;

                double t1 = v71 - v70 * v56;
                double t2b = v71 - v70 * v57;
                a2[1] = (t1 + t1) / 3.0;
                a2[2] = (t2b + t2b) / 3.0;
                a3[0] = 0.0;
                a3[1] = 0.0;
            } else {
                double s1 = c * -13.5 + v54[0];
                double s2 = c * -13.5 - v54[0];
                *a6 = 1;
                double v58 = (s1 < 0.0) ? -1.0 : 1.0;
                double v60 = (s2 < 0.0) ? -1.0 : 1.0;
                double v63 = pow(fabs(s1), 0.3333333333333333) * v58;
                double v64 = pow(fabs(s2), 0.3333333333333333) * v60;


                if (c > 0.0 && !(v64 == 0.0)) {
                    v63 = b * -3.0 / v64;
                }
                if (c < 0.0 && v63 != 0.0) {
                    v64 = b * -3.0 / v63;
                }
                a2[0] = (v64 + v63) / 3.0;
                a3[0] = 0.0;
                double e1 = (v64 * v74b[0] + v63 * v75[0]) * 0.3333333333333333;
                double e2 = (v64 * v74b[1] + v63 * v75[1]) * 0.3333333333333333;
                a2[1] = e1;
                a3[1] = e2;
                a2[2] = a2[1];
                v24 = -a3[1];
            }
            a3[2] = v24;
            double z3 = vz / 3.0;
            a2[0] = a2[0] - z3;
            a2[1] = a2[1] - z3;
            a2[2] = a2[2] - z3;
        } else {
            int v73 = 0;
            int atmp = 0;
            double q[3];
            q[0] = vy;
            q[1] = vz;
            q[2] = v18 / v18;
            a2[0] = 0.0;
            a3[0] = 0.0;
            b14_h014(&q[0], a2 + 1, a3 + 1, &v73, &v79, &atmp);
            *a6 = atmp + 1;
        }
    } else {
        double q[4];
        q[0] = v19;
        q[1] = v20;
        q[2] = v21;
        q[3] = v18;
        b14_h014(q, a2, a3, a4, a5, a6);
    }
}




static B14_NOINLINE void b14_h020(const double* a1, const double* a2, const double* a3,
                        double* a4, double* a5, int* a6) {
    static const double zero_d = 0.0;
    static const int mode1 = 1;
    int flag = 0;
    *a6 = 0;
    b14_h805(a1, &zero_d, &mode1, &flag);
    if (flag) {
        b14_h805(a2, &zero_d, &mode1, &flag);
        if (flag != 1) {
            *a4 = -*a3 / *a2;
            *a6 = 1;
        }
    } else {
        double disc = *a2 * *a2 - *a1 * 4.0 * *a3;
        b14_h805(&disc, &zero_d, &mode1, &flag);
        if (flag) {
            double v = -*a2 / (*a1 + *a1);
            *a4 = v;
            *a5 = v;
            *a6 = 2;
        } else if (!(0.0 > disc)) {
            double sq = sqrt(disc);
            *a6 = 2;
            if (*a2 >= 0.0) {
                *a4 = *a3 * -2.0 / (*a2 + sq);
                *a5 = -(sq + *a2) / (*a1 + *a1);
            } else {
                *a4 = (sq - *a2) / (*a1 + *a1);
                *a5 = (*a3 + *a3) / (sq - *a2);
            }
        }
    }
}




static B14_NOINLINE void b14_h053(const double* a1, const double* a2, double* a3) {
    static const double zero_d = 0.0;
    static const int mode0 = 0;
    int flag = 0;
    b14_h805(a1, &zero_d, &mode0, &flag);
    if (flag) {
        *a3 = 0.0;
        if (*a2 < 0.0) *a3 = B14_PI;
        return;
    }
    b14_h805(a2, &zero_d, &mode0, &flag);
    if (flag) {
        *a3 = B14_PI_2;
        if (*a1 < 0.0) *a3 = B14_3PI_2;
        return;
    }
    double v6 = atan(*a1 / *a2);
    *a3 = v6;
    double v7 = *a2;
    double v8 = v6;
    if (*a2 > 0.0 && *a1 < 0.0) {
        v8 = v6 + B14_2PI;
        *a3 = v6 + B14_2PI;
        v7 = *a2;
    }
    if (v7 < 0.0) {
        if (*a1 < 0.0) {
            v8 = v8 + B14_PI;
            *a3 = v8;
            v7 = *a2;
        }
        if (v7 < 0.0 && *a1 > 0.0) *a3 = v8 + B14_PI;
    }
}





static B14_NOINLINE void b14_h100(const double* a1, const double* a2, double* a3) {
    a3[0] = a1[1] * a2[1] + *a1 * *a2 + a1[2] * a2[2];
    a3[1] = *a1 * a2[3] + a1[1] * a2[4] + a1[2] * a2[5];
    a3[2] = *a1 * a2[6] + a1[1] * a2[7] + a1[2] * a2[8];
}


static B14_NOINLINE void b14_h110(const double* a1, double* a2) {
    a2[0] = a1[0];
    a2[4] = a1[4];
    a2[8] = a1[8];
    a2[3] = a1[1];
    a2[1] = a1[3];
    a2[6] = a1[2];
    a2[2] = a1[6];
    a2[7] = a1[5];
    a2[5] = a1[7];
}


static B14_NOINLINE void b14_h116(const double* a1, const double* a2, const double* a3,
                        const double* a4, const double* a5, double* a6) {
    a6[0] = a1[1] * *a3 + *a1 * *a2 + a1[2] * *a4 + a1[3] * *a5;
    a6[1] = a2[1] * *a1 + a3[1] * a1[1] + a4[1] * a1[2] + a5[1] * a1[3];
    a6[2] = a2[2] * *a1 + a3[2] * a1[1] + a4[2] * a1[2] + a5[2] * a1[3];
}


static B14_NOINLINE void b14_h300(const double* a1, const double* a2, double* a3) {
    *a3 = (a1[1] - a2[1]) * (a1[1] - a2[1]) + (*a1 - *a2) * (*a1 - *a2) +
          (a1[2] - a2[2]) * (a1[2] - a2[2]);
}


static B14_NOINLINE void b14_h301(const double* a1, const double* a2, double* a3) {
    double dz = a1[2] - a2[2];
    double dy = a1[1] - a2[1];
    *a3 = sqrt(dy * dy + (*a1 - *a2) * (*a1 - *a2) + dz * dz);
}


static B14_NOINLINE int b14_MTX3_is_ortho_normal(const double* m, double tol) {
    double x0 = m[0], x1 = m[1], x2 = m[2];
    double y0 = m[3], y1 = m[4], y2 = m[5];
    double z0 = m[6], z1 = m[7], z2 = m[8];
    if (!(tol >= fabs(x0 * x0 + x1 * x1 + x2 * x2 - 1.0))) return 0;
    if (!(tol >= fabs(y0 * y0 + y1 * y1 + y2 * y2 - 1.0))) return 0;
    if (!(tol >= fabs(z0 * z0 + z1 * z1 + z2 * z2 - 1.0))) return 0;
    if (!(tol >= fabs(x0 * y0 + x1 * y1 + x2 * y2))) return 0;
    if (!(tol >= fabs(z0 * y0 + z1 * y1 + z2 * y2))) return 0;
    if (!(tol >= fabs(x0 * z0 + x1 * z1 + x2 * z2))) return 0;
    return 1;
}





static B14_NOINLINE void b14_h120(const double* a1, const double* a2, double* a3) {
    double r[9];
    r[0] = a2[0] * a1[0] + a2[1] * a1[3] + a2[2] * a1[6];
    r[1] = a1[1] * a2[0] + a1[4] * a2[1] + a1[7] * a2[2];
    r[2] = a1[2] * a2[0] + a1[5] * a2[1] + a1[8] * a2[2];
    r[3] = a2[3] * a1[0] + a2[4] * a1[3] + a2[5] * a1[6];
    r[4] = a1[1] * a2[3] + a1[4] * a2[4] + a1[7] * a2[5];
    r[5] = a1[2] * a2[3] + a1[5] * a2[4] + a1[8] * a2[5];
    r[6] = a2[6] * a1[0] + a2[7] * a1[3] + a2[8] * a1[6];
    r[7] = a1[1] * a2[6] + a1[4] * a2[7] + a1[7] * a2[8];
    r[8] = a1[2] * a2[6] + a1[5] * a2[7] + a1[8] * a2[8];
    for (int i = 0; i < 9; ++i) a3[i] = r[i];
}


static B14_NOINLINE void b14_h815(const double* a1, const double* a2, const double* a3,
                        double* a4) {
    double v4 = *a2 - *a1;
    double v5 = (*a3 - *a1) / v4;
    double v6 = v5 * v5 * v5;
    double v7 = (v6 - v5 * v5) * v4;
    double v8 = v5 * v5 * 3.0 - (v6 + v6);
    a4[3] = v7;
    a4[2] = v8;
    a4[1] = (v5 - v5 * v5) * v4 + v7;
    a4[0] = 1.0 - v8;
}


static B14_NOINLINE void b14_h922(const double* a1, double* a2) {
    a2[0] = *a1;
    a2[1] = 0.0;
    a2[2] = 0.0;
    a2[3] = 0.0;
    a2[4] = *a1;
    a2[5] = 0.0;
    a2[6] = 0.0;
    a2[7] = 0.0;
    a2[8] = *a1;
}


static B14_NOINLINE void b14_h810(const double* a1, const double* a2, const double* a3,
                        const double* a4, const double* a5,
                        const double* a6, const double* a7, double* a8) {
    double v10[4];
    b14_h815(a1, a4, a7, v10);
    b14_h116(v10, a2, a3, a5, a6, a8);
}


static B14_NOINLINE void b14_h823(const double* a1, const double* a2, const double* a3,
                        const double* a4, const double* a5, const double* a6,
                        double* a7) {
    double v9 = a3[1];
    double v10 = a3[2];
    double v11 = a4[1] - v9;
    double v12 = a4[2] - v10;
    double v13 = *a4 - *a3;
    double v15 = b14_dmax0(*a2 - *a1);
    double v16 = a5[1];
    double v17 = a5[0];
    double v30 = a5[2];
    double v18 = a6[0];
    double v19 = a6[1];
    double v20 = a6[2];
    a7[0] = *a3;
    a7[1] = v9;
    a7[2] = v10;
    a7[3] = v17 * v15;
    a7[4] = v16 * v15;
    a7[5] = v30 * v15;
    a7[6] = v13 * 3.0 - (v17 * (v15 + v15) + v18 * v15) * 1.0;
    a7[7] = v11 * 3.0 - (v19 * v15 + v16 * (v15 + v15)) * 1.0;
    a7[8] = v12 * 3.0 - (v30 * (v15 + v15) + v20 * v15) * 1.0;
    a7[9] = (v17 + v18) * v15 - v13 * 2.0;
    a7[10] = (v19 + v16) * v15 - v11 * 2.0;
    a7[11] = (v30 + v20) * v15 - v12 * 2.0;
}


static B14_NOINLINE void b14_h822(const double* a1, const double* a2, double* a3,
                        const double* a4, double* a5, double* a6, double* a7,
                        double* a8, double* a9) {
    double v9 = a3[1];
    double v10 = a3[2];
    double v11 = a4[1] - v9;
    double v12 = a4[2] - v10;
    double v13 = *a4 - *a3;
    double v15 = b14_dmax0(*a2 - *a1);
    double v16 = a5[1];
    double v17 = *a5;
    double v30 = a5[2];
    double v18 = *a6;
    double v19 = a6[1];
    double v20 = a6[2];
    a7[0] = *a3;
    a7[2] = v10;
    a7[1] = v9;
    a7[3] = v17 * v15;
    a7[4] = v16 * v15;
    a7[5] = v30 * v15;
    a7[6] = v13 * 3.0 - (v17 * (v15 + v15) + v18 * v15) * 1.0;
    a7[7] = v11 * 3.0 - (v19 * v15 + v16 * (v15 + v15)) * 1.0;
    a7[8] = v12 * 3.0 - (v30 * (v15 + v15) + v20 * v15) * 1.0;
    a7[9] = (v17 + v18) * v15 - v13 * 2.0;
    a7[10] = (v19 + v16) * v15 - v11 * 2.0;
    a7[11] = (v30 + v20) * v15 - v12 * 2.0;
    double inv = 0.0;
    if (v15 > 0.0) inv = 1.0 / v15;
    double two = inv + inv;
    double three = inv * 3.0;
    a8[0] = v17;
    a8[1] = v16;
    a8[2] = v30;
    a8[3] = two * a7[6];
    a8[4] = two * a7[7];
    a8[5] = two * a7[8];
    a8[6] = three * a7[9];
    a8[7] = three * a7[10];
    a8[8] = three * a7[11];
    a9[0] = inv * a8[3];
    a9[1] = inv * a8[4];
    a9[2] = inv * a8[5];
    a9[3] = two * a8[6];
    a9[4] = two * a8[7];
    a9[5] = two * a8[8];
}



static B14_NOINLINE void b14_h811(const double* a1, const double* a2, const double* a3,
                        const double* a4, const double* a5, const double* a6,
                        const double* a7, double* a8) {
    double v8 = *a4 - *a1;
    double v9 = (*a7 - *a1) / v8;
    double c[4];
    double v12 = v9 * 3.0 * v9 - (v9 + v9);
    c[3] = v12;
    c[1] = v12 - (v9 + v9) + 1.0;
    double v11 = (v9 - v9 * v9) * 6.0 / v8;
    c[0] = -v11;
    c[2] = v11;
    b14_h116(c, a2, a3, a5, a6, a8);
}

static B14_NOINLINE void b14_h812(const double* a1, const double* a2, const double* a3,
                        const double* a4, const double* a5, const double* a6,
                        const double* a7, double* a8) {
    double v8 = *a4 - *a1;
    double v9 = (*a7 - *a1) / v8;
    double c[4];
    c[3] = (v9 * 6.0 - 2.0) / v8;
    c[1] = (v9 * 6.0 - 4.0) / v8;
    double v11 = (6.0 - v9 * 12.0) / (v8 * v8);
    c[0] = -v11;
    c[2] = v11;
    b14_h116(c, a2, a3, a5, a6, a8);
}


static B14_NOINLINE void b14_h956(const double* a1, const double* a2, double* a3) {
    b14_h100(a1, a2, a3);
    double v5 = a2[10];
    double v6 = a2[11] + a3[2];
    a3[0] = a2[9] + a3[0];
    a3[1] = v5 + a3[1];
    a3[2] = v6;
}


static B14_NOINLINE void b14_h957(const double* a1, const double* a2, const double* a3,
                        const double* a4, double* a5) {
    double v8[3];
    double v9[3];
    double v10[9];
    b14_h110(a3, v10);
    b14_h100(a1, v10, v8);
    b14_h956(v8, a2, v9);
    b14_h100(v9, a4, a5);
}







static B14_NOINLINE void b14_h954(const double* a1, const double* a2, const double* a3,
                        const double* a4, double* a5) {




    double v8[3];
    double v10[12];
    v8[0] = a1[0];
    v8[1] = a1[1];
    v8[2] = 0.0;
    for (int i = 0; i < 9; ++i) v10[i] = a2[i];
    v10[9] = 0.0;
    v10[10] = 0.0;
    v10[11] = 0.0;
    double v9[3];
    b14_h957(v8, v10, a3, a4, v9);
    a5[0] = v9[0];
    a5[1] = v9[1];
}


static B14_NOINLINE void b14_h959(const double* a1, const double* a2, const double* a3,
                        const double* a4, double* a5) {


    double v8[3];
    double v10[12];
    v8[0] = a1[0];
    v8[1] = a1[1];
    v8[2] = 0.0;
    for (int i = 0; i < 9; ++i) v10[i] = a2[i];
    v10[9] = 0.0;
    v10[10] = 0.0;
    v10[11] = 0.0;
    double v9[3];
    b14_h957(v8, v10, a3, a4, v9);
    a5[0] = v9[0];
    a5[1] = v9[1];
}

void h881(const double* a1, const double* a2, double* a3) {
    int flag = 0;
    double v15[3];
    v15[0] = a1[0] - a1[3];
    v15[1] = a1[1] - a1[4];
    v15[2] = a1[2] - a1[5];
    b14_vunt3(v15, &flag, a3);
    v15[0] = a2[0] - a1[3];
    v15[1] = a2[1] - a1[4];
    v15[2] = a2[2] - a1[5];
    b14_vcru3(a3, v15, &flag, a3 + 6);
    double v10 = a3[7];
    double v11 = a3[8];
    double v12 = a3[0];
    double v13 = a3[6] * a3[2];
    double v14 = a3[6] * a3[1] - a3[0] * v10;
    a3[3] = v10 * a3[2] - v11 * a3[1];
    a3[4] = v12 * v11 - v13;
    a3[5] = v14;
}



