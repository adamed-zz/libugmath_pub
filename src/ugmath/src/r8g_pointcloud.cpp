






#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

namespace UGS { namespace Memory {
template <class T>
class SMAlloc {
public:
    using value_type = T;
    SMAlloc() = default;
    template <class U> SMAlloc(const SMAlloc<U>&) {}
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t);
};
template <class T, class U> bool operator==(const SMAlloc<T>&, const SMAlloc<U>&) { return true; }
template <class T, class U> bool operator!=(const SMAlloc<T>&, const SMAlloc<U>&) { return false; }
}}

namespace UGS { namespace Math {

struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct Matrix3 { double m[9]; };
struct TransformMatrix { double m[16]; };

namespace {

struct Vec3d { double x, y, z; };


void jacobi_eigen3(double a[3][3], double eval[3], Vec3d evec[3])
{
    double v[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    for (int sweep = 0; sweep < 24; ++sweep)
    {
        double off = a[0][1]*a[0][1] + a[0][2]*a[0][2] + a[1][2]*a[1][2];
        if (off < 1e-30) break;
        for (int p = 0; p < 2; ++p)
            for (int q = p + 1; q < 3; ++q)
            {
                if (std::fabs(a[p][q]) < 1e-300) continue;
                const double theta = (a[q][q] - a[p][p]) / (2.0 * a[p][q]);
                const double t = (theta >= 0 ? 1.0 : -1.0) /
                                 (std::fabs(theta) + std::sqrt(theta * theta + 1.0));
                const double c = 1.0 / std::sqrt(t * t + 1.0);
                const double s = t * c;
                for (int k = 0; k < 3; ++k)
                {
                    const double akp = a[k][p], akq = a[k][q];
                    a[k][p] = c * akp - s * akq;
                    a[k][q] = s * akp + c * akq;
                }
                for (int k = 0; k < 3; ++k)
                {
                    const double apk = a[p][k], aqk = a[q][k];
                    a[p][k] = c * apk - s * aqk;
                    a[q][k] = s * apk + c * aqk;
                }
                for (int k = 0; k < 3; ++k)
                {
                    const double vkp = v[k][p], vkq = v[k][q];
                    v[k][p] = c * vkp - s * vkq;
                    v[k][q] = s * vkp + c * vkq;
                }
            }
    }
    int idx[3] = {0,1,2};
    for (int i = 0; i < 2; ++i)
        for (int j = i + 1; j < 3; ++j)
            if (a[idx[j]][idx[j]] < a[idx[i]][idx[i]]) { const int t = idx[i]; idx[i] = idx[j]; idx[j] = t; }
    for (int i = 0; i < 3; ++i)
    {
        eval[i] = a[idx[i]][idx[i]];
        evec[i] = { v[0][idx[i]], v[1][idx[i]], v[2][idx[i]] };
    }
}


inline void row_mul(const double p[3], const double m[9], double out[3])
{
    out[0] = p[0]*m[0] + p[1]*m[3] + p[2]*m[6];
    out[1] = p[0]*m[1] + p[1]*m[4] + p[2]*m[7];
    out[2] = p[0]*m[2] + p[1]*m[5] + p[2]*m[8];
}

inline void mat4_mul(const double a[16], const double b[16], double out[16])
{
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
        {
            double s = 0.0;
            for (int k = 0; k < 4; ++k) s += a[r*4+k] * b[k*4+c];
            out[r*4+c] = s;
        }
}

}

namespace PointCloudUtils {

bool ComputePlaneNormal(const std::vector<Point3, UGS::Memory::SMAlloc<Point3>>& points,
                        Vector3& normal)
{
    const Point3* p = points.empty() ? nullptr : &points[0];
    const std::size_t n = points.size();
    if (n < 3) { normal.x = normal.y = 0.0; normal.z = 1.0; return false; }

    double cx = 0, cy = 0, cz = 0;
    for (std::size_t i = 0; i < n; ++i) { cx += p[i].x; cy += p[i].y; cz += p[i].z; }
    cx /= (double)n; cy /= (double)n; cz /= (double)n;

    double cov[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    for (std::size_t i = 0; i < n; ++i)
    {
        const double d[3] = { p[i].x - cx, p[i].y - cy, p[i].z - cz };
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c) cov[r][c] += d[r] * d[c];
    }
    double eval[3]; Vec3d evec[3];
    jacobi_eigen3(cov, eval, evec);
    Vec3d nrm = evec[0];
    const double len = std::sqrt(nrm.x*nrm.x + nrm.y*nrm.y + nrm.z*nrm.z);
    if (len > 0) { nrm.x /= len; nrm.y /= len; nrm.z /= len; }
    normal.x = nrm.x; normal.y = nrm.y; normal.z = nrm.z;
    return true;
}

TransformMatrix ComputeTransform2D(
    std::vector<std::pair<Point3, Point3>, UGS::Memory::SMAlloc<std::pair<Point3, Point3>>>& pairs,
    const Matrix3& a3)
{
    TransformMatrix ret;
    for (int i = 0; i < 16; ++i) ret.m[i] = (i % 5 == 0) ? 1.0 : 0.0;
    if (pairs.empty()) return ret;

    const std::size_t n = pairs.size();
    double mcx = 0, mcy = 0, pcx = 0, pcy = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        double a[3] = { pairs[i].first.x, pairs[i].first.y, pairs[i].first.z };
        double b[3] = { pairs[i].second.x, pairs[i].second.y, pairs[i].second.z };
        double ta[3], tb[3];
        row_mul(a, a3.m, ta); row_mul(b, a3.m, tb);
        mcx += ta[0]; mcy += ta[1]; pcx += tb[0]; pcy += tb[1];
    }
    mcx /= (double)n; mcy /= (double)n; pcx /= (double)n; pcy /= (double)n;


    double sxx = 0, sxy = 0, syx = 0, syy = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        double a[3] = { pairs[i].first.x, pairs[i].first.y, pairs[i].first.z };
        double b[3] = { pairs[i].second.x, pairs[i].second.y, pairs[i].second.z };
        double ta[3], tb[3];
        row_mul(a, a3.m, ta); row_mul(b, a3.m, tb);
        const double mx = ta[0] - mcx, my = ta[1] - mcy;
        const double px = tb[0] - pcx, py = tb[1] - pcy;
        sxx += mx * px; sxy += mx * py; syx += my * px; syy += my * py;
    }
    const double theta = std::atan2(sxy - syx, sxx + syy);
    const double c = std::cos(theta), s = std::sin(theta);

    double R[4] = { c, -s, s, c };
    double t[2] = { pcx - (R[0]*mcx + R[1]*mcy), pcy - (R[2]*mcx + R[3]*mcy) };

    double m4[16] = { R[0], R[1], 0, 0,
                      R[2], R[3], 0, 0,
                      0,    0,    1, 0,
                      t[0], t[1], 0, 1 };


    double v63[16] = { a3.m[0], a3.m[3], a3.m[6], 0,
                       a3.m[1], a3.m[4], a3.m[7], 0,
                       a3.m[2], a3.m[5], a3.m[8], 0,
                       0, 0, 0, 1 };

    double tmp[16];
    mat4_mul(m4, v63, tmp);
    mat4_mul(tmp, v63, m4);

    for (int i = 0; i < 16; ++i) ret.m[i] = m4[i];
    return ret;
}

}

}}
