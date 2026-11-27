




















#include <cmath>
#include <cstdint>
#include <cstring>

namespace {


inline int DSign(double x) {
    std::uint64_t u;
    std::memcpy(&u, &x, 8);
    return static_cast<int>(u >> 63);
}


inline bool IsOrthoNormal3(const double* m, double tol) {
    const double x0 = m[0], x1 = m[1], x2 = m[2];
    const double y0 = m[3], y1 = m[4], y2 = m[5];
    const double z0 = m[6], z1 = m[7], z2 = m[8];
    if (!(tol >= std::fabs(x0 * x0 + x1 * x1 + x2 * x2 - 1.0))) return false;
    if (!(tol >= std::fabs(y0 * y0 + y1 * y1 + y2 * y2 - 1.0))) return false;
    if (!(tol >= std::fabs(z0 * z0 + z1 * z1 + z2 * z2 - 1.0))) return false;
    if (!(tol >= std::fabs(x0 * y0 + x1 * y1 + x2 * y2))) return false;
    if (!(tol >= std::fabs(z0 * y0 + z1 * y1 + z2 * y2))) return false;
    if (!(tol >= std::fabs(x0 * z0 + x1 * z1 + x2 * z2))) return false;
    return true;
}


inline bool Vec3Unitize(const double* v, double tol, double* len, double* out) {
    const double n2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    const double n = std::sqrt(n2);
    if (tol >= n) {
        *len = 0.0;
        out[0] = 0.0;
        out[1] = 0.0;
        out[2] = 0.0;
        return false;
    }
    *len = n;
    const double inv = 1.0 / n;
    out[0] = v[0] * inv;
    out[1] = v[1] * inv;
    out[2] = v[2] * inv;
    return true;
}



inline bool Mtx3InitYZ(const double* yIn, const double* zIn, double* m) {
    double len = 0.0;
    double y[3] = {0.0, 0.0, 0.0};
    double z[3] = {0.0, 0.0, 0.0};
    if (!Vec3Unitize(yIn, 1.0e-10, &len, y)) return false;
    if (!Vec3Unitize(zIn, 1.0e-10, &len, z)) return false;
    if (std::fabs(z[1] * y[1] + z[0] * y[0] + z[2] * y[2]) > 1.0e-10) return false;

    double x[3];
    x[0] = z[2] * y[1] - z[1] * y[2];
    x[1] = z[0] * y[2] - z[2] * y[0];
    x[2] = z[1] * y[0] - z[0] * y[1];
    Vec3Unitize(x, 1.0e-10, &len, x);
    m[0] = x[0];
    m[1] = x[1];
    m[2] = x[2];
    m[6] = z[0];
    m[7] = z[1];
    m[8] = z[2];
    m[3] = z[1] * x[2] - z[2] * x[1];
    m[4] = z[2] * x[0] - z[0] * x[2];
    m[5] = z[0] * x[1] - z[1] * x[0];
    return true;
}


inline void NormCosSin(double* c, double* s) {
    const double v = *c;
    const double a = std::fabs(*c);
    if (a > 0.9999999999 || std::fabs(*s) <= 1.0e-10) {
        *s = 0.0;
        *c = (v <= 0.0) ? -1.0 : 1.0;
    } else if (std::fabs(*s) > 0.9999999999 || a <= 1.0e-10) {
        *s = (*s <= 0.0) ? -1.0 : 1.0;
        *c = 0.0;
    } else {
        const double sv = *s;
        const double n2 = v * v + sv * sv;
        if (std::fabs(n2 - 1.0) > 1.0e-20) {
            if (a <= std::fabs(sv)) {
                const double sgn = (v <= 0.0) ? -1.0 : 1.0;
                *c = std::sqrt(1.0 - sv * sv) * sgn;
            } else {
                const double sgn = (sv <= 0.0) ? -1.0 : 1.0;
                *s = std::sqrt(1.0 - v * v) * sgn;
            }
        }
    }
}


inline int Massage3(double* m) {
    int changed = 0;
    for (int i = 0; i < 3; ++i) {
        double* row = m + i * 3;
        bool done = false;
        for (int j = 0; j < 3; ++j) {
            if (done) break;
            double v = row[j];
            if (v != 0.0) {
                const double a = std::fabs(v);
                if (a != 1.0) {
                    if (a <= 1.0e-10) {
                        v = 0.0;
                        row[j] = 0.0;
                        changed = 1;
                    }
                    if (std::fabs(std::fabs(v) - 1.0) <= 1.0e-10) {
                        changed = 1;
                        done = true;
                        row[j] = (v <= 0.0) ? -1.0 : 1.0;
                        if (j != 0) row[0] = 0.0;
                        if (j == 1 || (row[1] = 0.0, j != 2)) row[2] = 0.0;
                    }
                }
            }
        }
    }
    return changed;
}


inline void RebuildFromAngles(double cr, double sr, double cp, double sp, double cy, double sy,
                              double* m) {
    m[0] = cp * cy;
    m[3] = cp * sy;
    m[6] = -sp;
    m[1] = (sp * cy) * sr - cr * sy;
    m[8] = cr * cp;
    m[4] = (sp * sy) * sr + cr * cy;
    m[7] = sr * cp;
    m[2] = (sp * cy) * cr + sr * sy;
    m[5] = (sp * sy) * cr - sr * cp;
}


inline void AnglesFromMatrix(const double* m, double* cr, double* sr, double* cp, double* sp,
                             double* cy, double* sy) {
    const double n2 = m[0] * m[0] + m[3] * m[3];
    if (std::fabs(n2) > 1.0e-20) {
        const double n = std::sqrt(n2);
        *cp = n;
        *sp = -m[6];
        *cr = m[8] / *cp;
        *sr = m[7] / *cp;
        *cy = m[0] / *cp;
        *sy = m[3] / *cp;
        NormCosSin(cp, sp);
        NormCosSin(cr, sr);
        NormCosSin(cy, sy);
    } else {
        *cp = 0.0;
        *cy = 1.0;
        *sy = 0.0;
        *cr = m[4];
        if (m[6] >= 0.0) {
            *sp = -1.0;
            *sr = -m[1];
        } else {
            *sp = 1.0;
            *sr = m[1];
        }
        NormCosSin(cr, sr);
    }
}


inline bool OrthoNormalizeReflection(double* m) {
    const double det = ((m[4] * m[8] - m[5] * m[7]) * m[0] -
                        (m[1] * m[8] - m[2] * m[7]) * m[3] +
                        (m[1] * m[5] - m[2] * m[4]) * m[6]);
    if (det >= 0.0) return false;
    if (IsOrthoNormal3(m, 1.0e-14)) return false;

    const double o6 = m[6], o7 = m[7], o8 = m[8];
    const double o0 = m[0], o1 = m[1], o2 = m[2];
    const double o3 = m[3], o4 = m[4], o5 = m[5];

    double y[3];
    y[0] = o8 * o1 - o7 * o2;
    y[1] = o6 * o2 - o8 * o0;
    y[2] = o7 * o0 - o6 * o1;
    const double z[3] = {o6, o7, o8};
    Mtx3InitYZ(y, z, m);

    const double n0 = m[0], n1 = m[1], n2 = m[2];
    const double n3 = m[3], n4 = m[4], n5 = m[5];
    const double n6 = m[6], n7 = m[7], n8 = m[8];

    const double d0 = (n1 * o1 + n0 * o0) + n2 * o2;
    if (d0 < 0.0) {
        m[0] = -n0;
        m[1] = -n1;
        m[2] = -n2;
    }
    const double d1 = (o3 * n3 + n4 * o4) + n5 * o5;
    if (d1 < 0.0) {
        m[3] = -n3;
        m[4] = -n4;
        m[5] = -n5;
    }
    const double d2 = (n7 * o7 + n6 * o6) + o8 * n8;
    if (d2 < 0.0) {
        m[6] = -n6;
        m[7] = -n7;
        m[8] = -n8;
    }



    const double orig[9] = {o0, o1, o2, o3, o4, o5, o6, o7, o8};
    bool same = true;
    for (int i = 0; i < 9; ++i) {
        if (!(std::fabs(orig[i] - m[i]) <= 1.0e-10)) {
            same = false;
            break;
        }
    }
    if (same) return IsOrthoNormal3(m, 1.0e-14);
    return true;
}


inline bool OrthoNormalize3(double* m) {
    const double det = ((m[4] * m[8] - m[5] * m[7]) * m[0] -
                        (m[1] * m[8] - m[2] * m[7]) * m[3] +
                        (m[1] * m[5] - m[2] * m[4]) * m[6]);
    if (!(det >= 0.0)) return OrthoNormalizeReflection(m);
    if (IsOrthoNormal3(m, 1.0e-14)) return false;

    bool first = true;
    int iter = 0;
    bool changed = false;
    while (!IsOrthoNormal3(m, 1.0e-14)) {
        ++iter;
        if (iter > 1000) break;

        const double x0 = m[0], x1 = m[1], x2 = m[2];
        const double z0 = m[6], z1 = m[7], z2 = m[8];
        const double z[3] = {z0, z1, z2};

        const double xn = std::sqrt(x0 * x0 + x1 * x1 + x2 * x2);
        const double zn = std::sqrt(z1 * z1 + z0 * z0 + z2 * z2);
        const double xz = (x1 * z1 + z0 * x0) + x2 * z2;
        if (xn <= 1.0e-14 || zn <= 1.0e-14 || std::fabs(xz) > 1.0e-14) {
            if (first) Massage3(m);
            double cr, sr, cp, sp, cy, sy;
            AnglesFromMatrix(m, &cr, &sr, &cp, &sp, &cy, &sy);
            RebuildFromAngles(cr, sr, cp, sp, cy, sy, m);
            if (first) Massage3(m);
        } else {
            double y[3];
            y[0] = x2 * z1 - x1 * z2;
            y[1] = z2 * x0 - x2 * z0;
            y[2] = x1 * z0 - z1 * x0;
            Mtx3InitYZ(y, z, m);
        }
        first = false;
        changed = true;
    }
    return changed;
}




void QuatFromTwoVectors(double* q, const double* u, const double* v) {
    double u0 = u[0], u1 = u[1], u2 = u[2];
    double v0 = v[0], v1 = v[1], v2 = v[2];

    const double nu = u2 * u2 + (u0 * u0 + u1 * u1);
    if (!(nu <= 0.0)) {
        const double s = std::sqrt(nu);
        u0 /= s;
        u1 /= s;
        u2 /= s;
    }
    const double nv = v2 * v2 + (v0 * v0 + v1 * v1);
    if (!(nv <= 0.0)) {
        const double s = std::sqrt(nv);
        v0 /= s;
        v1 /= s;
        v2 /= s;
    }
    const double dot = (u2 * v2) + (u0 * v0 + u1 * v1);
    if (dot >= -0.999999999999) {
        const double cx = u1 * v2 - u2 * v1;
        const double cy = v0 * u2 - u0 * v2;
        const double cz = u0 * v1 - v0 * u1;
        double t = dot + 1.0;
        t = t + t;
        const double s = std::sqrt(t);
        const double inv = 1.0 / s;
        q[0] = cx * inv;
        q[1] = cy * inv;
        q[2] = cz * inv;
        q[3] = s * 0.5;
    } else {


        const double a[3] = {std::fabs(u0), std::fabs(u1), std::fabs(u2)};
        int k = 0;
        if (a[1] < a[k]) k = 1;
        if (a[2] < a[k]) k = 2;
        double e[3] = {0.0, 0.0, 0.0};
        e[k] = 1.0;
        double ax = u1 * e[2] - u2 * e[1];
        double ay = u2 * e[0] - u0 * e[2];
        double az = u0 * e[1] - u1 * e[0];
        const double n = std::sqrt(ax * ax + ay * ay + az * az);
        if (n > 0.0) {
            ax /= n;
            ay /= n;
            az /= n;
        }
        q[0] = ax;
        q[1] = ay;
        q[2] = az;
        q[3] = 0.0;
    }
}


void Mul3(const double* a1, const double* a2, double* out) {
    const double v3 = a2[1], v5 = a2[0], v7 = a2[2], v8 = a2[3];
    const double v13 = a2[4], v16 = a2[5];
    const double v29 = a2[7], v33 = a2[8], v35 = a2[6];
    const double v9 = a1[4] * v3;
    const double v10 = a1[7] * v7;
    const double v11 = a1[1] * v5 + v9;
    const double v12 = a1[5] * v3;
    const double v14 = v11 + v10;
    const double v17 = a1[2] * v5;
    const double v18 = v8 * a1[1];
    const double v19 = v17 + v12;
    const double v15 = a1[8] * v7;
    const double v20 = v13 * a1[3];
    const double v21 = v19 + v15;
    const double v24 = v13 * a1[4];
    const double v22 = v16 * a1[6];
    const double v23 = v8 * a1[0] + v20;
    const double v26 = v16 * a1[7];
    const double v25 = v23 + v22;
    const double v27 = v16 * a1[8];
    const double v28 = v8 * a1[2] + v13 * a1[5];
    const double v30 = v18 + v24 + v26;
    const double v31 = v29 * a1[3];
    const double v32 = v28 + v27;
    const double v34 = v33 * a1[6];
    const double v36 = v35 * a1[0] + v31 + v34;
    const double v37 = v33 * a1[7];
    const double v38 = v35 * a1[1] + v29 * a1[4];
    out[0] = a2[0] * a1[0] + v3 * a1[3] + v7 * a1[6];
    out[1] = v14;
    out[2] = v21;
    out[3] = v25;
    out[4] = v30;
    out[5] = v32;
    out[6] = v36;
    out[7] = v38 + v37;
    out[8] = v35 * a1[2] + v29 * a1[5] + v33 * a1[8];
}


bool IsCollinear3(const double* p, const double* q) {
    double a[3] = {p[0], p[1], p[2]};
    double b[3] = {q[0], q[1], q[2]};
    double mx = 0.0;
    for (int i = 0; i < 3; ++i) {
        mx = std::fmax(mx, std::fabs(a[i]));
        mx = std::fmax(mx, std::fabs(b[i]));
    }
    const bool scaled = (mx > 0.0) && std::isfinite(mx);
    if (scaled) {
        for (int i = 0; i < 3; ++i) {
            a[i] /= mx;
            b[i] /= mx;
        }
    }
    const double na = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    const double nb = std::sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
    const double c0 = a[1] * b[2] - a[2] * b[1];
    const double c1 = a[2] * b[0] - a[0] * b[2];
    const double c2 = a[0] * b[1] - a[1] * b[0];
    const double nc = std::sqrt(c0 * c0 + c1 * c1 + c2 * c2);
    const double r22 = (na > 0.0) ? (nc / na) : nb;
    const double tol = (scaled ? 1.0 : std::fmax(na, nb)) * 1.0e-10;
    int cnt = 0;
    if (std::fabs(na) > tol) ++cnt;
    if (std::fabs(r22) > tol) ++cnt;
    return cnt <= 1;
}

}

namespace UGS {
namespace Math {

struct Matrix3 {
    double M[9];
};

struct TransformMatrix {
    double M[16];
};

namespace PointCloudUtils {

bool AlignZAxes(const Matrix3& csys, TransformMatrix& transform) {
    double* t = transform.M;
    const double* c = csys.M;

    const double zOld[3] = {t[2], t[6], t[10]};
    const double zCsys[3] = {c[6], c[7], c[8]};

    double q[4];
    QuatFromTwoVectors(q, zOld, zCsys);


    const double q0 = q[0], q1 = q[1], q2 = q[2], q3 = q[3];
    const double d0 = q0 + q0, d1 = q1 + q1, d2 = q2 + q2;
    const double a3 = q3 * d0, b3 = q3 * d1, c3 = q3 * d2;
    const double a0 = q0 * d0, b0 = q0 * d1, c0 = q0 * d2;
    const double b1 = q1 * d1, c1 = q1 * d2;
    const double c2 = q2 * d2;
    double rot[9];
    rot[0] = 1.0 - (b1 + c2);
    rot[1] = b0 - c3;
    rot[2] = c0 + b3;
    rot[3] = c3 + b0;
    rot[4] = 1.0 - (c2 + a0);
    rot[5] = c1 - a3;
    rot[6] = c0 - b3;
    rot[7] = c1 + a3;
    rot[8] = 1.0 - (b1 + a0);

    double old3[9];
    old3[0] = t[0]; old3[1] = t[1]; old3[2] = t[2];
    old3[3] = t[4]; old3[4] = t[5]; old3[5] = t[6];
    old3[6] = t[8]; old3[7] = t[9]; old3[8] = t[10];

    double out[9];
    Mul3(old3, rot, out);
    if (IsOrthoNormal3(old3, 1.0e-14) && IsOrthoNormal3(rot, 1.0e-14))
        OrthoNormalize3(out);

    t[0] = out[0]; t[1] = out[1]; t[2] = out[2];
    t[4] = out[3]; t[5] = out[4]; t[6] = out[5];
    t[8] = out[6]; t[9] = out[7]; t[10] = out[8];


    const double dot = (zCsys[2] * zOld[2]) + (zCsys[0] * zOld[0] + zCsys[1] * zOld[1]);
    return !IsCollinear3(zOld, zCsys) || !DSign(dot);
}

}
}
}
