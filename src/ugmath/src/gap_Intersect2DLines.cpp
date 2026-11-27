
#include <cmath>

















namespace UGS {
namespace Math {

void Intersect2DLines(const double* const l1, const double* const l2, double eps,
                      bool& ok, double* const out);

void Intersect2DLines(const double* const l1, const double* const l2, double eps,
                      bool& ok, double* const out)
{
    ok = true;
    out[0] = out[1] = 0.0;
    const double w = (l2[1] - l2[3]) * (l1[0] - l1[2]) -
                     (l1[1] - l1[3]) * (l2[0] - l2[2]);
    if (eps > std::fabs(w)) {
        ok = false;
        return;
    }
    const double r1 = l1[0] * l1[3] - l1[1] * l1[2];
    const double r2 = l2[0] * l2[3] - l2[2] * l2[1];
    out[0] = ((l2[0] - l2[2]) * r1 - (l1[0] - l1[2]) * r2) / w;
    out[1] = ((l2[1] - l2[3]) * r1 - (l1[1] - l1[3]) * r2) / w;
}

}
}
