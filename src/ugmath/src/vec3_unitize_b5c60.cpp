
















namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}



double EQ_ask_length_tolerance();




int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


int VEC3_unitize(UGS::Math::Vector3* u, double* len_out)
{
    return VEC3_unitize(u, EQ_ask_length_tolerance(), len_out, u);
}
