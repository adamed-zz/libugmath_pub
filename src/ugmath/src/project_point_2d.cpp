#include "ugmath/project_point_2d.h"













namespace UGS {
namespace Math {

void ProjectPointOn2DLineT(const double* const p, const double* const line, double& t)
{
    t = 0.0;
    double dx = line[2] - line[0];
    double dy = line[3] - line[1];
    double den = dy * dy + dx * dx;
    if (den > 1.0e-7f)
        t = ((p[1] - line[1]) * dy + (p[0] - line[0]) * dx) / den;
}









void __cdecl ProjectPointOn2DLine(const double* const point, const double* const line,
                                  double& t, double* const proj)
{
    double tt = 0.0;
    t = tt;
    proj[0] = line[0];
    proj[1] = line[1];
    t = tt;

    double dx = line[2] - line[0];
    double dy = line[3] - line[1];
    double len2 = dy * dy;
    len2 += dx * dx;

    if (len2 > 1.0e-7f)
    {
        tt = ((point[1] - line[1]) * dy + (point[0] - line[0]) * dx) / len2;
        t = tt;
    }

    proj[0] = (line[2] - line[0]) * tt + line[0];
    proj[1] = (line[3] - line[1]) * t + line[1];
}

}
}
