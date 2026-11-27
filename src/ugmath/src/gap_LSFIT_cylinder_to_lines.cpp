















#include <cstddef>
#include <exception>
#include <math.h>

namespace UGS {
namespace Math {

struct Point2
{
    double x, y;
};

struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};

}
}



struct CSYS_s
{
    double origin[3];
    double x_axis[3];
    double y_axis[3];
    double z_axis[3];
};

namespace UGS {
namespace Error {



class Exception : public std::exception
{
public:
    virtual void doDefaultStartAction(const char* file, int line, int recover_type) const;
    [[noreturn]] __declspec(dllimport) void Rethrow() const;

protected:
    unsigned char m_reserved[0x78];
};

class Severe : public Exception
{
public:
    __declspec(dllimport) Severe();
    __declspec(dllimport) const Exception& Convert(const std::exception& ex);
};

}
}


__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void SM_free(void* p);



extern "C" void sub_180051CD0(int a1, double* a2, int a3, UGS::Math::Point3* a4,
                               UGS::Math::Vector3* a5, UGS::Math::Vector3* a6,
                               UGS::Math::Vector3* a7, UGS::Math::Point3* a8,
                               UGS::Math::Vector3* a9, int* a10, UGS::Math::Point3* a11);
extern "C" void sub_180055700(int n, UGS::Math::Point3* points, UGS::Math::Point3* center,
                               UGS::Math::Vector3* normal, UGS::Math::Point2* out2d,
                               CSYS_s* csys);
extern "C" void sub_180053800(int n, UGS::Math::Point3* points, double* pars, bool mode,
                               UGS::Math::Point3* center, double radius,
                               UGS::Math::Vector3* vec11, UGS::Math::Vector3* vec7,
                               void* p9, void* p10, void* p11, void* p12, void* p13);


void __cdecl LSFIT_circle_to_points_2d(UGS::Math::Point2* pts, int count, double tolerance,
                                       UGS::Math::Point2* result, double* radius,
                                       int* status, double* resid);

void __cdecl LSFIT_cylinder_to_lines(int a1, UGS::Math::Point3* a2, UGS::Math::Vector3* a3,
                                     int a4, double* a5, UGS::Math::Vector3* const a6,
                                     UGS::Math::Vector3* a7, UGS::Math::Point3* a8,
                                     UGS::Math::Point3* a9, double* a10,
                                     UGS::Math::Vector3* a11, UGS::Math::Vector3* a12,
                                     double* const a13, UGS::Math::Point3* const a14,
                                     int* a15, double* a16)
{
    int v35 = 0;
    void* v36 = 0;
    UGS::Math::Point3 v37 = {0.0, 0.0, 0.0};
    UGS::Math::Point2 v38;
    UGS::Math::Point3 v39;
    UGS::Math::Point3 v41 = {0.0, 0.0, 0.0};
    CSYS_s csys = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

    a8->x = a8->y = a8->z = 0.0;
    a9->x = a9->y = a9->z = 0.0;
    *a10 = 1.0e19;
    a11->x = a11->y = a11->z = 0.0;
    a12->x = a12->y = a12->z = 0.0;
    a13[0] = 360.0;
    a13[1] = -360.0;
    a14[0].x = a14[0].y = a14[0].z = 0.0;
    a14[1].x = a14[1].y = a14[1].z = 0.0;
    *a15 = 0;
    a16[0] = 0.0;
    a16[1] = 0.0;
    a16[2] = 0.0;

    try
    {
        sub_180051CD0(a4, a5, a1, a2, a3, a6, a7, a8, a11, a15, &v37);
        if (*a15 != 1)
        {
            v38.x = 0.0;
            v38.y = 0.0;
            v36 = SM_alloc(16 * (__int64)a1);
            sub_180055700(a1, a2, a8, a11, (UGS::Math::Point2*)v36, &csys);
            LSFIT_circle_to_points_2d((UGS::Math::Point2*)v36, a1, 0.01, &v38, a10, &v35,
                                      a16);
            SM_free(v36);
            v36 = 0;
            if (!v35)
            {
                *(UGS::Math::Point2*)a9 = v38;
                v37.z = 0.0;
                a9->z = 0.0;
                double x = a9->x;
                double y = a9->y;
                double z = a9->z;
                a9->x = x * csys.x_axis[0] + y * csys.y_axis[0] + z * csys.z_axis[0] +
                        csys.origin[0];
                a9->y = x * csys.x_axis[1] + y * csys.y_axis[1] + z * csys.z_axis[1] +
                        csys.origin[1];
                a9->z = x * csys.x_axis[2] + y * csys.y_axis[2] + z * csys.z_axis[2] +
                        csys.origin[2];

                sub_180053800(a1, a2, a5, true, a9, *a10, a11, a7, &v37, &v41, a12, a13, a14);
                double v27 = a5[1];
                if (v27 >= fabs(a13[0] - 0.0) && v27 >= fabs(a13[1] - 360.0))
                {
                    csys.origin[0] = csys.origin[1] = csys.origin[2] = 0.0;
                    csys.x_axis[0] = csys.x_axis[1] = csys.x_axis[2] = 0.0;
                    v37.x = v37.y = v37.z = 0.0;
                    v39.x = 0.0;
                    v39.y = 0.0;
                    v39.z = 0.0;
                    double v49[11];
                    sub_180053800(a1, a2, a5, false, a9, *a10, a11, a7, &v49, &v39, &v37,
                                  &v38, &csys);
                    double v31 = a5[1];
                    double v32 = v38.x;
                    double v33 = v38.y;
                    if (v31 < fabs(v38.x - 0.0) || v31 < fabs(v38.y - 360.0))
                    {
                        v41 = v39;
                        *(UGS::Math::Point3*)a12 = v37;
                        a13[0] = v32;
                        a13[1] = v33;
                        a14[0] = *(const UGS::Math::Point3*)&csys.origin[0];
                        a14[1] = *(const UGS::Math::Point3*)&csys.x_axis[0];
                    }
                }
            }
        }
    }




    catch (std::exception& e)
    {
        UGS::Error::Severe sev;
        UGS::Error::Exception* ex = dynamic_cast<UGS::Error::Exception*>(&e);
        if (!ex)
            ex = const_cast<UGS::Error::Exception*>(&sev.Convert(e));
        ex->doDefaultStartAction("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 6052, 0);
        if (v36)
            SM_free(v36);
        ex->Rethrow();
    }
}
