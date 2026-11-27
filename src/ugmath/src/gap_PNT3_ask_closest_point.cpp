








#include "b37_math.h"

#include <cmath>

namespace {

constexpr double kTwoPi = 6.283185307179586;
constexpr double kNumberTol = 1.0e-10;

inline double MinAngleToZero(double a) {
    double x1 = std::fabs(kTwoPi - a);
    double x6 = std::fabs(a);

    return (x1 > x6) ? x6 : x1;
}

}

void PNT3_ask_closest_point(const UGS::Math::Point3* a1, const UGS::Math::Vector3* a2,
                            const UGS::Math::Point3* a3, int a4, UGS::Math::Point3* a5) {
    if (a4 <= 0)
        return;

    double best = 0.0;
    long long index = 0;
    long long count = a4;

    do {
        double px = a3->x;
        double py = a3->y;
        double pz = a3->z;

        double dx = px - a1->x;
        double dy = py - a1->y;
        double dz = pz - a1->z;
        double dist_sq = dy * dy + dx * dx;
        dist_sq += dz * dz;
        double dist = sqrt(dist_sq);

        bool update;
        if (!index) {
            update = true;
        } else {
            double tol1 = EQ_ask_length_tolerance();
            if (best - tol1 > dist) {
                update = true;
            } else {
                double tol2 = EQ_ask_length_tolerance();
                if (!(tol2 < std::fabs(dist - best))) {
                    UGS::Math::Vector3 cur = {a1->x - px, a1->y - py, a1->z - pz};
                    UGS::Math::Vector3 prev = {a1->x - a5->x, a1->y - a5->y, a1->z - a5->z};
                    UGS::Math::Vector3 cr;
                    cr.x = cur.z * a2->y - cur.y * a2->z;
                    cr.y = cur.x * a2->z - cur.z * a2->x;
                    cr.z = cur.y * a2->x - cur.x * a2->y;

                    double a1a = VEC3_angle_between(a2, &cur, &cr);
                    double m1 = MinAngleToZero(a1a);
                    double a2a = VEC3_angle_between(a2, &prev, &cr);
                    double m2 = MinAngleToZero(a2a);
                    update = (m2 - kNumberTol > m1);
                } else {
                    update = false;
                }
            }
        }

        if (update) {
            a5->x = px;
            a5->y = py;
            a5->z = pz;
            best = dist;
        }
        ++index;
        a3 = (const UGS::Math::Point3*)((const char*)a3 + 24);
    } while (index < count);
}
