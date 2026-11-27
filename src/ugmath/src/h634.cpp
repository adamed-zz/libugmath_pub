











namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

}
}


void vcru3(const double* a, const double* b, int* flag, double* out);
void h635(const double* a1, const double* a2, const double* a3, const double* a4,
          int* flag, double* out);
void h805(const double* value, const double* tol, const int* mode, int* flag);


extern const double dbl_1800BA990;
extern const int dword_1800BA998;

void h634(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7)
{

    double t;
    UGS::Math::Vector3 v;
    int flag;
    *a5 = 1;
    vcru3(a2, a4, &flag, a7);
    if (flag == 1)
    {
        *a5 = 2;
        v.x = a7[1] * a2[2] - a7[2] * a2[1];
        v.y = a2[0] * a7[2] - a7[0] * a2[2];
        v.z = a7[0] * a2[1] - a2[0] * a7[1];
        h635(a1, reinterpret_cast<const double*>(&v), a3, a4, &flag, a6);
    }
    else
    {
        v.x = a3[0] - a1[0];
        v.y = a3[1] - a1[1];
        v.z = a3[2] - a1[2];
        t = v.x * a2[0] + v.y * a2[1] + v.z * a2[2];
        h805(&t, &dbl_1800BA990, &dword_1800BA998, &flag);
        if (flag == 1)
            *a5 = 3;
    }
}
