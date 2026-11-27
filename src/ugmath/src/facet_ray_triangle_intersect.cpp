






namespace UGS {
namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;




extern Point3* sub_180001820(Point3* out, double w, const Point3* v);

bool __cdecl FACET_ray_triangle_intersect(const Point3* a1, const Vector3* a2,
                                          const Point3* a3, Point3* a4,
                                          double* a5)
{
    const Point3* p0 = a3;
    const Point3* p1 = a3 + 1;
    const Point3* p2 = a3 + 2;

    double v8  = p0->y;
    double v9  = p2->y - v8;
    double v10 = a2->y;
    double v11 = p1->x - p0->x;
    double v12 = p1->y - v8;
    double v13 = p1->z - p0->z;
    double v42 = v9;
    double v39 = p2->x - p0->x;
    double v40 = p2->z - p0->z;

    double v14 = v10 * v40 - a2->z * v9;
    double v15 = a2->z * v39 - a2->x * v40;
    double v16 = a2->x * v9 - v10 * v39;
    double v17 = v15 * v12 + v14 * v11 + v16 * v13;

    if (v17 > -1.0e-14 && v17 < 1.0e-14)
        return false;

    double v18 = 1.0 / v17;
    double v19 = a1->x - p0->x;
    double v20 = a1->z - p0->z;
    double v21 = a1->y - v8;
    double v22 = (v21 * v15 + v19 * v14 + v20 * v16) * v18;
    if (v22 < 0.0)
        return false;
    if (v22 > 1.0)
        return false;

    double v23 = v21 * v13 - v20 * v12;
    double v24 = v20 * v11 - v19 * v13;
    double v25 = v19 * v12 - v21 * v11;
    double v26 = (v10 * v24 + a2->x * v23 + a2->z * v25) * v18;
    if (v26 < 0.0 || v26 + v22 > 1.0)
        return false;

    alignas(16) Point3 buf;
    *a5 = (v24 * v42 + v23 * v39 + v25 * v40) * v18;

    Point3 A = *sub_180001820(&buf, (1.0 - v22) - v26, p0);
    Point3 B = *sub_180001820(&buf, v22, p1);
    Point3 C = *sub_180001820(&buf, v26, p2);

    a4->x = A.x + B.x + C.x;
    a4->y = A.y + B.y + C.y;
    a4->z = A.z + B.z + C.z;

    *a5 = (a4->x - a1->x) * a2->x + (a4->y - a1->y) * a2->y +
          (a4->z - a1->z) * a2->z;
    return true;
}
