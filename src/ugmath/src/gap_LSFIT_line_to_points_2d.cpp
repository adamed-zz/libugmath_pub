




namespace UGS
{
namespace Math
{

struct Point2
{
    double x;
    double y;
};
struct Vector2
{
    double x;
    double y;
};
}
}


void LSFIT_line_to_points_2d(int mode,
                             UGS::Math::Point2* pts,
                             int n,
                             UGS::Math::Point2* out_pt,
                             UGS::Math::Vector2* out_vec,
                             int* ret,
                             double* dist);


void LSFIT_line_to_points_2d(UGS::Math::Point2* pts,
                             int n,
                             UGS::Math::Point2* out_pt,
                             UGS::Math::Vector2* out_vec,
                             int* ret,
                             double* dist)
{
    LSFIT_line_to_points_2d(0, pts, n, out_pt, out_vec, ret, dist);
}
