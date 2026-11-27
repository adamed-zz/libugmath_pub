








namespace UGS {
namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
}
}



extern void __cdecl LSFIT_plane_to_points(int mode, UGS::Math::Point3* pts, int n,
                                          UGS::Math::Point3* out_pt, UGS::Math::Vector3* out_vec,
                                          int* ret, double* dist);

void __cdecl LSFIT_plane_to_points(UGS::Math::Point3* pts, int n, UGS::Math::Point3* out_pt,
                                   UGS::Math::Vector3* out_vec, int* ret, double* dist)
{
    LSFIT_plane_to_points(0, pts, n, out_pt, out_vec, ret, dist);
}
