


















#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace {


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


    const bool ok = tol < n;
    if (tol >= n) {
        *len = 0.0;
        out[0] = 0.0;
        out[1] = 0.0;
        out[2] = 0.0;
    } else {
        *len = n;
        const double inv = 1.0 / n;
        out[0] = v[0] * inv;
        out[1] = v[1] * inv;
        out[2] = v[2] * inv;
    }
    return ok;
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


    if (det < 0.0) return OrthoNormalizeReflection(m);
    if (IsOrthoNormal3(m, 1.0e-14)) return false;

    bool first = true;
    int iter = 0;
    bool changed = false;
    while (!IsOrthoNormal3(m, 1.0e-14)) {
        ++iter;
        if (iter > 1000) {


            throw std::runtime_error("Failed to orthonormalize matrix");
        }

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


inline double AngleBetween(const double* a, const double* b) {
    const double la2 = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    const double la = std::sqrt(la2);
    double uax, uay, uaz;
    if (la == 0.0) {
        uax = a[0]; uay = a[1]; uaz = a[2];
    } else {
        uax = a[0] / la; uay = a[1] / la; uaz = a[2] / la;
    }
    const double lb2 = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
    const double lb = std::sqrt(lb2);
    double ubx, uby, ubz;
    if (lb == 0.0) {
        ubx = b[0]; uby = b[1]; ubz = b[2];
    } else {
        ubx = b[0] / lb; uby = b[1] / lb; ubz = b[2] / lb;
    }

    const double t1 = ubx * uaz - uax * ubz;
    const double t2 = ubz * uay - uaz * uby;
    const double t3 = uax * uby - ubx * uay;
    const double cross2 = t1 * t1 + t2 * t2 + t3 * t3;
    const double dot = uax * ubx + uay * uby + uaz * ubz;
    return std::atan2(std::sqrt(cross2), dot);
}


inline void RotAboutAxis(double angle, const double* axis, double* m) {
    double u[3] = {0.0, 0.0, 0.0};
    double len = 0.0;
    double s = 0.0;
    double c;
    if (Vec3Unitize(axis, 1.0e-10, &len, u)) {
        s = std::sin(angle);
        c = std::cos(angle);
    } else {
        c = 1.0;
    }
    const double ux = u[0], uy = u[1], uz = u[2];
    const double r = 1.0 - c;
    const double uys = uy * s;
    const double uxs = ux * s;
    const double rxy = (r * ux) * uy;
    const double ryz = (r * uy) * uz;
    const double rxz = (r * ux) * uz;
    const double ryy = (r * uy) * uy;
    const double rxx = (r * ux) * ux;
    const double rzz = (r * uz) * uz;
    m[0] = rxx + c;
    m[1] = rxy - uz * s;
    m[2] = uys + rxz;
    m[3] = uz * s + rxy;
    m[4] = ryy + c;
    m[5] = ryz - uxs;
    m[6] = rxz - uys;
    m[7] = uxs + ryz;
    m[8] = rzz + c;
    OrthoNormalize3(m);
}


const double kLengthTolerance = 1.0e-8;

inline void RotFromTwo(const double* a, const double* b, double* m) {
    const double la2 = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    const double la = std::sqrt(la2);
    if (kLengthTolerance >= la) {
        const double ident[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        std::memcpy(m, ident, sizeof ident);
        return;
    }
    const double lb2 = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
    const double lb = std::sqrt(lb2);
    if (kLengthTolerance >= lb) {
        const double ident[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        std::memcpy(m, ident, sizeof ident);
        return;
    }

    double ua[3], ub[3];
    if (la == 0.0) {
        ua[0] = a[0]; ua[1] = a[1]; ua[2] = a[2];
    } else {
        ua[0] = a[0] / la; ua[1] = a[1] / la; ua[2] = a[2] / la;
    }
    if (lb == 0.0) {
        ub[0] = b[0]; ub[1] = b[1]; ub[2] = b[2];
    } else {
        ub[0] = b[0] / lb; ub[1] = b[1] / lb; ub[2] = b[2] / lb;
    }

    double axis[3];
    axis[0] = ua[1] * ub[2] - ub[1] * ua[2];
    axis[1] = ub[0] * ua[2] - ua[0] * ub[2];
    axis[2] = ua[0] * ub[1] - ub[0] * ua[1];
    const double cm2 = axis[1] * axis[1] + axis[0] * axis[0] + axis[2] * axis[2];
    const double cm = std::sqrt(cm2);
    if (kLengthTolerance >= cm) {
        if (std::fabs(ua[0] - ua[1]) > 1.0e-10 || std::fabs(ua[1] - ua[2]) > 1.0e-10) {
            double e0 = ua[0] - ua[1];
            double e1 = ua[1] - ua[2];
            double e2 = ua[2] - ua[0];
            const double n2 = e2 * e2 + e1 * e1 + e0 * e0;
            const double n = std::sqrt(n2);
            if (n != 0.0) {
                e1 /= n;
                e2 /= n;
                e0 /= n;
            }
            axis[0] = e1;
            axis[1] = e2;
            axis[2] = e0;
        } else {
            const double s6 = std::sqrt(6.0);
            if (s6 == 0.0) {
                axis[0] = 1.0;
                axis[1] = 1.0;
                axis[2] = -2.0;
            } else {
                const double inv = 1.0 / s6;
                axis[0] = inv;
                axis[1] = inv;
                axis[2] = (-2.0) / s6;
            }
        }
    }

    const double angle = AngleBetween(ua, ub);
    RotAboutAxis(angle, axis, m);
}

}

namespace UGS {
namespace Math {

struct Vector3 {
    double x, y, z;
};

struct Matrix3 {
    double M[9];
};

namespace PointCloudUtils {

enum Alignment { kAlignmentNone = 0, kAlignmentFlip = 1 };

Matrix3 RotationFromTwoVectors(const Vector3& a, const Vector3& b, Alignment alignment);

Matrix3 RotationFromTwoVectors(const Vector3& a, const Vector3& b, Alignment alignment) {
    Matrix3 out;
    const double av[3] = {a.x, a.y, a.z};
    const double bv[3] = {b.x, b.y, b.z};
    double m[9];
    RotFromTwo(av, bv, m);
    const double angle1 = AngleBetween(av, bv);

    if (alignment != 0) {
        const double na[3] = {-a.x, -a.y, -a.z};
        double m2[9];
        RotFromTwo(na, bv, m2);
        const double angle2 = AngleBetween(na, bv);


        if (!(angle2 >= angle1)) {
            std::memcpy(m, m2, sizeof m);
        }
    }
    std::memcpy(out.M, m, sizeof m);
    return out;
}

}
}
}
