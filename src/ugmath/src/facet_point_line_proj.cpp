












namespace UGS
{
namespace Math
{

struct Point3
{
    double x;
    double y;
    double z;
};

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}

void FACET_point_line_proj(UGS::Math::Point3 *a1, UGS::Math::Point3 *a2,
                           UGS::Math::Vector3 *a3, int a4,
                           UGS::Math::Point3 *a5, double *a6)
{
    double v6 = (a1->y - a2->y) * a3->y
              + (a1->x - a2->x) * a3->x
              + (a1->z - a2->z) * a3->z;
    *a6 = v6;
    double v7 = v6;
    if (!a4)
    {
        double v8 = a3->x * a3->x + a3->y * a3->y + a3->z * a3->z;
        v7 = v6;
        if (v8 != 0.0)
        {
            v7 = v6 / v8;
            *a6 = v6 / v8;
        }
    }
    a5->x = v7 * a3->x + a2->x;
    a5->y = v7 * a3->y + a2->y;
    a5->z = v7 * a3->z + a2->z;
}
