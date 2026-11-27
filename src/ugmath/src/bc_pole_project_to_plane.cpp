



namespace UGS
{
namespace Math
{
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

double EQ_ask_length_tolerance();
int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);

void bc_POLE_project_to_plane(double* const a1, double* const a2, double* const a3,
                              double* const a4)
{
    double w = a1[3];
    double px = a1[0] / w;
    double py = a1[1] / w;
    double pz = a1[2] / w;
    double ny = a3[1];
    double nx = a3[0];
    double nz = a3[2];
    double dx = px - a2[0];
    double dy = py - a2[1];
    double dz = pz - a2[2];
    double d = dy * ny + dx * nx + dz * nz;
    UGS::Math::Vector3 n;
    n.x = nx;
    n.y = ny;
    n.z = nz;
    double len;
    VEC3_unitize(&n, EQ_ask_length_tolerance(), &len, &n);
    UGS::Math::Vector3 o;
    o.x = px - n.x * d;
    o.y = py - n.y * d;
    o.z = pz - n.z * d;
    a4[0] = o.x * a1[3];
    a4[1] = o.y * a1[3];
    a4[2] = o.z * a1[3];
    a4[3] = a1[3];
}
