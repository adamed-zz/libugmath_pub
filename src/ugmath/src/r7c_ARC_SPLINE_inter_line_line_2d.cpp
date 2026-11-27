







#include <bit>
#include <cmath>
#include <cstdint>
#include <emmintrin.h>

namespace UGS {
namespace Math {
struct alignas(16) Point2 { double x, y; };
struct alignas(16) Vector2 { double x, y; };
}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;



static_assert(std::bit_cast<std::uint64_t>(0.01745329251994328)
                  == 0x3F91DF46A2529D35ull,
              "deg2rad constant must match raw bit pattern");


static int __declspec(noinline) VEC2_unitize(const Vector2* v, double tol, double* len,
                                      Vector2* out);
static int __declspec(noinline) SOLVE_solve_3equations(double (*const A)[3], double* const b,
                                                double* const x);

void ARC_SPLINE_inter_line_line_2d(const double* const a1, const Point2* a2,
                                   const Point2* a3, int a4, Vector2* a5, Vector2* a6,
                                   Point2* a7, double* a8, double* a9, int* a10)
{


    int* const st = a10;
    *st = 0;

    struct Frame { Vector2 du, dv, u, v; } f;
    f.u = *a5;
    f.v = *a6;

    const double cos_tol = cos(a1[1] * 0.01745329251994328);

    const double dy = a3->y - a2->y;
    const double dx = a3->x - a2->x;
    const double dist = sqrt(dx * dx + dy * dy);
    const double half = 0.5 * dist;

    int far = 0;
    if (a1[0] > dist)
    {
        far = 1;
        const __m128d halfv = _mm_set_pd(0.5, 0.5);
        const __m128d sum = _mm_unpacklo_pd(_mm_set_sd(a2->x + a3->x),
                                            _mm_set_sd(a2->y + a3->y));
        _mm_storeu_pd(&a7->x, _mm_mul_pd(halfv, sum));
        _mm_storeu_pd(a8, _mm_set1_pd(half));
        *a9 = 1.0;
    }
    const __m128d params = _mm_set1_pd(half);

    double ux, uy, vx, vy;
    if (a4 == 0)
    {
        double len2;
        VEC2_unitize(&f.u, 1.0e-8, reinterpret_cast<double*>(&a10), &f.du);
        VEC2_unitize(&f.v, 1.0e-8, &len2, &f.dv);
        ux = f.du.x;
        uy = f.du.y;
        vx = f.dv.x;
        vy = f.dv.y;
        a5->x = ux;
        a5->y = uy;
        a6->x = vx;
        a6->y = vy;
    }
    else
    {
        f.du = f.u;
        f.dv = f.v;
        ux = f.du.x;
        uy = f.du.y;
        vx = f.dv.x;
        vy = f.dv.y;
    }

    const double d = vx * ux + vy * uy;

    if (fabs(d) >= cos_tol)
    {
        *st = 1;
        if (far != 0 || fabs((dx * ux + dy * uy) / dist) >= cos_tol)
            *st = 2;
        *a9 = d;
        const __m128d halfv = _mm_set_pd(0.5, 0.5);
        const __m128d sum = _mm_unpacklo_pd(_mm_set_sd(a2->x + a3->x),
                                            _mm_set_sd(a3->y + a2->y));
        _mm_storeu_pd(&a7->x, _mm_mul_pd(halfv, sum));
        _mm_storeu_pd(a8, params);
        return;
    }

    if (far != 1)
    {
        double A[3][3] = {{ux, -vx, 0.0}, {uy, -vy, 0.0}, {0.0, 0.0, 1.0}};
        double b[3] = {dx, dy, 0.0};
        double sol[3];
        if (SOLVE_solve_3equations(A, b, sol) != 0)
        {
            *st = 1;
            *a9 = 1.0;
            const __m128d halfv2 = _mm_set_pd(0.5, 0.5);
            const __m128d sum2 = _mm_unpacklo_pd(_mm_set_sd(a2->x + a3->x),
                                                 _mm_set_sd(a3->y + a2->y));
            _mm_storeu_pd(&a7->x, _mm_mul_pd(halfv2, sum2));
            _mm_storeu_pd(a8, params);
            return;
        }
        a7->x = sol[0] * ux + a2->x;
        a7->y = sol[0] * uy + a2->y;
        a8[0] = sol[0];
        a8[1] = sol[1];
    }
    *a9 = d;
}



static int __declspec(noinline) VEC2_unitize(const Vector2* v, double tol, double* len,
                                      Vector2* out)
{
    const double x = v->x;
    const double y = v->y;
    const double l = sqrt(x * x + y * y);

    const int result = !(tol >= l);
    if (tol >= l)
    {

        *len = 0.0;
        out->x = 0.0;
        out->y = 0.0;
    }
    else
    {
        *len = l;
        const double inv = 1.0 / l;
        out->x = x * inv;
        out->y = y * inv;
    }
    return result;
}

static int __declspec(noinline) SOLVE_solve_3equations(double (*const A)[3], double* const b,
                                                double* const x)
{
    const double a00 = A[0][0], a01 = A[0][1], a02 = A[0][2];
    const double a10 = A[1][0], a11 = A[1][1], a12 = A[1][2];
    const double a20 = A[2][0], a21 = A[2][1], a22 = A[2][2];
    const double c00 = a11 * a22 - a12 * a21;
    const double c01 = a01 * a22 - a02 * a21;
    const double c02 = a01 * a12 - a02 * a11;
    const double det = a00 * c00 - a10 * c01 + a20 * c02;
    if (det == 0.0)
        return 1;
    const double b0 = b[0], b1 = b[1], b2 = b[2];
    x[0] = (b0 * c00 - b1 * c01 + b2 * c02) / det;
    x[1] = ((a20 * a12 - a10 * a22) * b0 + (a22 * a00 - a20 * a02) * b1
            + (a10 * a02 - a00 * a12) * b2)
           / det;
    x[2] = ((a20 * a01 - a00 * a21) * b1 + (a10 * a21 - a20 * a11) * b0
            + (a00 * a11 - a10 * a01) * b2)
           / det;
    return 0;
}
