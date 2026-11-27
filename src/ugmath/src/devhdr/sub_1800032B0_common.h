
#pragma once
#include <math.h>

namespace UGS { namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
} }

void ARC_SPLINE_solve_quadratic_eqt(double, double, double, int, double * const, int *);

static const double kDeg2Rad = 0.01745329251994328;
