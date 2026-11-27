










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

}
}

void LSFIT_ask_pts_centroid_3d(int n, UGS::Math::Point3* pts, UGS::Math::Point3* centroid)
{
    double sx = 0.0;
    double sy = 0.0;
    double sz = 0.0;

    if (n > 0)
    {
        const UGS::Math::Point3* p = pts;
        for (__int64 i = n; i != 0; --i)
        {
            sx += p->x;
            sy += p->y;
            sz += p->z;
            ++p;
        }
    }

    double dn = (double)n;
    centroid->x = sx / dn;
    centroid->y = sy / dn;
    centroid->z = sz / dn;
}
