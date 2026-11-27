


#include <cmath>

namespace UGS {
namespace Math {

bool IntersectSegmentRectangle2D(const double* const segment, const double* const rect)
{
    double x0 = segment[0];
    double x1 = segment[2];

    double xmin = x0;
    double xmax = x1;
    if (x0 > x1)
    {
        xmin = x1;
        xmax = x0;
    }

    double hi = rect[2] < xmax ? rect[2] : xmax;
    double lo = rect[0] > xmin ? rect[0] : xmin;
    if (lo > hi)
        return false;

    double yLo = segment[1];
    double yHi = segment[3];
    if (fabs(segment[2] - segment[0]) > 1e-6f)
    {
        double slope = (segment[3] - segment[1]) / (segment[2] - segment[0]);
        double intercept = segment[1] - segment[0] * slope;
        yLo = slope * lo + intercept;
        yHi = slope * hi + intercept;
    }

    if (yLo > yHi)
    {
        double t = yHi;
        yHi = yLo;
        yLo = t;
    }

    return (rect[1] > yLo ? rect[1] : yLo) <= (rect[3] < yHi ? rect[3] : yHi);
}

}
}
