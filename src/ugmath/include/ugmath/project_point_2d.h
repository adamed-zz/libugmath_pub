#pragma once


















namespace UGS {
namespace Math {

void __cdecl ProjectPointOn2DLineT(const double* const p, const double* const line, double& t);
















void __cdecl ProjectPointOn2DLine(const double* const point, const double* const line,
                                  double& t, double* const proj);

}
}
