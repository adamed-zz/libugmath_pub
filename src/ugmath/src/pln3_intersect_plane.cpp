










namespace UGS {
namespace Math {

struct Point3 {
    double x;
    double y;
    double z;
};

struct Vector3 {
    double x;
    double y;
    double z;
};

}
}

struct PLN3_s {
    double origin[3];
    double normal[3];
};


void h634(const double* o1, const double* n1, const double* o2, const double* n2,
          int* flag, double* point, double* dir);

int PLN3_intersect_plane(const PLN3_s* a1, const PLN3_s* a2,
                         UGS::Math::Point3& a3, UGS::Math::Vector3& a4)
{
    if (a1 == a2)
        return 0;
    int flag = 0;
    h634(reinterpret_cast<const double*>(a1),
         reinterpret_cast<const double*>(a1) + 3,
         reinterpret_cast<const double*>(a2),
         reinterpret_cast<const double*>(a2) + 3,
         &flag,
         reinterpret_cast<double*>(&a3),
         reinterpret_cast<double*>(&a4));
    return flag;
}
