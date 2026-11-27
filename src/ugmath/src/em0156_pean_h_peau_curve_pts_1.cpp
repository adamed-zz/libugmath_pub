

















#include <math.h>

namespace UGS { namespace Math {
struct Vector3 { double x, y, z; };
} }

double EQ_ask_length_tolerance();
int VEC3_unitize(const UGS::Math::Vector3* v, double tol, double* len,
                 UGS::Math::Vector3* out);

struct CURVE_PTS
{
    double param;
    double x;
    double y;
    double z;
};

void em0156(const double* a1, int a2, CURVE_PTS* a3, double* a4)
{
    double best = 0.0;
    double bestParam = 0.0;
    double bestDx = 0.0;
    double bestDy = 0.0;
    double bestDz = 0.0;
    const double* bestPt = 0;
    int bestIdx = 0;

    if (a2 > 0)
    {
        const double qx = a1[0];
        const double qy = a1[1];
        const double qz = a1[2];

        for (int i = 0; i < a2; ++i)
        {
            const double* p = (const double*)&a3[i];
            const double dx = qx - p[1];
            const double dy = qy - p[2];
            const double dz = qz - p[3];
            const double d2 = dy * dy + dx * dx + dz * dz;
            const double d = sqrt(d2);
            if (i == 0 || best > d)
            {
                bestParam = p[0];
                bestDx = dx;
                bestDy = dy;
                bestDz = dz;
                bestPt = p;
                bestIdx = i;
                best = d;
            }
        }

        if (best > 0.0001 && bestIdx > 0 && bestIdx < a2 - 1)
        {
            UGS::Math::Vector3 dir;
            dir.x = bestPt[5] - bestPt[-3];
            dir.y = bestPt[6] - bestPt[-2];
            dir.z = bestPt[7] - bestPt[-1];
            double len = 0.0;
            const double tol1 = EQ_ask_length_tolerance();
            VEC3_unitize(&dir, tol1, &len, &dir);
            if (!(0.0001 > len))
            {
                const double dot =
                    bestDy * dir.y + bestDx * dir.x + bestDz * dir.z;
                if (dot > 0.0001)
                {
                    UGS::Math::Vector3 nxt;
                    nxt.x = bestPt[5] - bestPt[1];
                    nxt.y = bestPt[6] - bestPt[2];
                    nxt.z = bestPt[7] - bestPt[3];
                    double len2 = 0.0;
                    const double tol2 = EQ_ask_length_tolerance();
                    VEC3_unitize(&nxt, tol2, &len2, &nxt);
                    const double dot2 =
                        bestDy * nxt.y + bestDx * nxt.x + bestDz * nxt.z;
                    if (dot2 > 0.0001 && len2 > dot2)
                    {
                        bestParam = bestParam + (bestPt[4] - bestPt[0]) * (dot2 / len2);
                    }
                }
                else
                {
                    UGS::Math::Vector3 prv;
                    prv.x = bestPt[-3] - bestPt[1];
                    prv.y = bestPt[-2] - bestPt[2];
                    prv.z = bestPt[-1] - bestPt[3];
                    double len3 = 0.0;
                    const double tol3 = EQ_ask_length_tolerance();
                    VEC3_unitize(&prv, tol3, &len3, &prv);
                    const double dot3 =
                        bestDy * prv.y + bestDx * prv.x + bestDz * prv.z;
                    if (dot3 > 0.0001 && len3 > dot3)
                    {
                        bestParam = bestParam - (dot3 / len3) * (bestPt[0] - bestPt[-4]);
                    }
                }
            }
        }
    }
    *a4 = bestParam;
}
