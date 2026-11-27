









#include <cmath>

namespace UGS {
namespace Math {

struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct TransformMatrix { double m[16]; };

}
}

int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);
void MTX4_multiply(const UGS::Math::TransformMatrix* a1,
                   const UGS::Math::TransformMatrix* a2,
                   UGS::Math::TransformMatrix* a3);
void h924(const double* n, double* out);

int MTX4_mirror(const UGS::Math::Point3* point, const UGS::Math::Vector3* normal,
                UGS::Math::TransformMatrix* matrix)
{
	UGS::Math::Vector3 unit = { 0.0, 0.0, 0.0 };
	double unit_len;

	double len = sqrt(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
	if (len <= 1.0e-10)
		return 1;

	double px = point->x;
	double py = point->y;
	double pz = point->z;

	UGS::Math::TransformMatrix t = {
		1.0, 0.0, 0.0, -px,
		0.0, 1.0, 0.0, -py,
		0.0, 0.0, 1.0, -pz,
		0.0, 0.0, 0.0, 1.0
	};

	VEC3_unitize(normal, 1.0e-10, &unit_len, &unit);

	UGS::Math::TransformMatrix tmp;
	h924(&unit.x, tmp.m);

	UGS::Math::TransformMatrix ref = {
		tmp.m[0], tmp.m[1], tmp.m[2], 0.0,
		tmp.m[3], tmp.m[4], tmp.m[5], 0.0,
		tmp.m[6], tmp.m[7], tmp.m[8], 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	MTX4_multiply(&t, &ref, &tmp);

	t = UGS::Math::TransformMatrix{
		1.0, 0.0, 0.0, px,
		0.0, 1.0, 0.0, py,
		0.0, 0.0, 1.0, pz,
		0.0, 0.0, 0.0, 1.0
	};

	MTX4_multiply(&tmp, &t, matrix);
	return 0;
}
