







#include <cmath>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

typedef UGS::Math::Vector3 Vector3;

extern int VEC3_unitize(const Vector3* vec, double tol, double* len, Vector3* unit);

void LSFIT_ask_mean_vec(int n, Vector3* pts, bool flag, Vector3* out_mean, double* out_angle)
{
    double min_cos = 1.0e19;
    double len;
    Vector3 unit_mean = {0.0, 0.0, 0.0};
    Vector3 u = {0.0, 0.0, 0.0};

    *out_angle = 90.0;
    if (n < 1)
    {
        *out_angle = 0.0;
        return;
    }
    if (n == 1)
    {
        out_mean->x = pts[0].x;
        out_mean->y = pts[0].y;
        out_mean->z = pts[0].z;
        *out_angle = 0.0;
        return;
    }

    double sx = 0.0;
    double sy = 0.0;
    double sz = 0.0;
    const Vector3* q = pts;
    long long cnt0 = n;
    do
    {
        sx += q->x;
        sy += q->y;
        sz += q->z;
        ++q;
    } while (--cnt0);
    out_mean->x = sx / (double)n;
    out_mean->y = sy / (double)n;
    out_mean->z = sz / (double)n;

    VEC3_unitize(out_mean, 1.0e-10, &len, &unit_mean);
    if (len > 1.0e-10)
    {
        unsigned long long cnt = (unsigned int)n;
        const Vector3* p = pts;
        do
        {
            if (!flag)
            {
                VEC3_unitize(p, 1.0e-10, &len, &u);
            }
            else
            {
                u.x = p->x;
                u.y = p->y;
                u.z = p->z;
                len = 1.0;
            }
            if (len > 1.0e-10)
            {
                double d = u.x * unit_mean.x + u.y * unit_mean.y + u.z * unit_mean.z;
                double ad = std::fabs(d);
                min_cos = (ad < min_cos) ? ad : min_cos;
            }
            ++p;
            --cnt;
        } while (cnt);

        *out_angle = std::acos((1.0 < min_cos) ? 1.0 : min_cos) * 57.29577951308235;
    }
    else
    {
        out_mean->x = out_mean->y = out_mean->z = 0.0;
    }
}
