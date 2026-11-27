













#include <exception>

namespace UGS {
namespace Math {

struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};

}

namespace Error {



class Exception : public std::exception
{
public:
    virtual void doDefaultStartAction(const char* file, int line, int recover_type) const;
    [[noreturn]] void Rethrow() const;

protected:
    unsigned char m_reserved[0x78];
};

class Severe : public Exception
{
public:
    Severe();
    const Exception& Convert(const std::exception& ex);
};

}
}



extern "C" void sub_180050C50(int a1, double* a2, int a3, UGS::Math::Point3* a4,
                               UGS::Math::Vector3* a5, UGS::Math::Vector3* a6,
                               UGS::Math::Vector3* a7, UGS::Math::Point3* a8,
                               int* a9, UGS::Math::Vector3* a10);
extern "C" void sub_180052030(double* a1, int a2, UGS::Math::Point3* a3,
                               UGS::Math::Vector3* a4, UGS::Math::Vector3* a5,
                               UGS::Math::Vector3* a6, UGS::Math::Point3* a7,
                               UGS::Math::Vector3* a8, UGS::Math::Vector3* a9,
                               UGS::Math::Point3* a10);
extern "C" void sub_1800523D0(int a1, UGS::Math::Point3* a2, UGS::Math::Vector3* a3,
                               UGS::Math::Vector3* a4, double* a5, UGS::Math::Point3* a6,
                               UGS::Math::Point3* a7, UGS::Math::Vector3* a8, bool* a9,
                               UGS::Math::Point3* a10, UGS::Math::Vector3* a11,
                               UGS::Math::Vector3* a12, UGS::Math::Point3* a13);
extern "C" void sub_180050820(int a1, UGS::Math::Point3* a2, double* a3,
                               UGS::Math::Point3* a4, UGS::Math::Vector3* a5,
                               UGS::Math::Point3* a6, UGS::Math::Vector3* a7, double* a8);


void LSFIT_adjust_axis_of_cone_from_ruling(double* a1, bool a2, UGS::Math::Point3* a3,
                                           UGS::Math::Vector3* a4,
                                           UGS::Math::Point3* const a5,
                                           UGS::Math::Vector3* a6,
                                           UGS::Math::Point3* const a7,
                                           double* const a8, double* a9);

void LSFIT_cone_to_lines(int a1, UGS::Math::Point3* a2, UGS::Math::Vector3* a3, int a4,
                         double* a5, UGS::Math::Vector3* const a6, UGS::Math::Vector3* a7,
                         UGS::Math::Point3* a8, int* a9, UGS::Math::Point3* a10,
                         UGS::Math::Vector3* a11, UGS::Math::Vector3* a12,
                         UGS::Math::Vector3* a13, double* const a14,
                         UGS::Math::Point3* const a15, UGS::Math::Point3* const a16,
                         double* const a17, double* a18)
{
    bool v21 = false;
    int v22 = 0;

    a8->x = a8->y = a8->z = 0.0;
    *a9 = 0;
    a11->x = a11->y = a11->z = 0.0;
    a13->x = a13->y = a13->z = 0.0;
    a14[0] = 360.0;
    a14[1] = -360.0;
    a12->x = a12->y = a12->z = 0.0;
    a15[0].x = a15[0].y = a15[0].z = 0.0;
    a15[1].x = a15[1].y = a15[1].z = 0.0;
    a16[0].x = a16[0].y = a16[0].z = 0.0;
    a16[1].x = a16[1].y = a16[1].z = 0.0;
    a17[0] = 0.0;
    a17[1] = 0.0;
    *a18 = 0.0;

    try
    {
        sub_180050C50(a4, a5, a1, a2, a3, a6, a7, a8, &v22, a11);
        if (v22)
            goto SET;
        {
            UGS::Math::Point3 v23 = {0.0, 0.0, 0.0};
            sub_180052030(a5, a1, a2, a3, a6, a7, a8, a11, a13, &v23);
            sub_1800523D0(a1, a2, a6, a7, a5, a8, &v23, a11, &v21, a10, a12, a13, a15);

            UGS::Math::Point3 v25;
            if (v21)
                v25 = v23;
            else
                v25 = *a10;
            LSFIT_adjust_axis_of_cone_from_ruling(a5, v21, &v25, a11, a15, a12, a16, a17, a18);
            sub_180050820(a1, a2, a5, a10, a11, a16, a13, a14);
        }

        if (v21)
        {
    SET:
            *a9 = 1;
        }
    }




    catch (std::exception& e)
    {
        UGS::Error::Severe sev;
        UGS::Error::Exception* ex = dynamic_cast<UGS::Error::Exception*>(&e);
        if (!ex)
            ex = const_cast<UGS::Error::Exception*>(&sev.Convert(e));
        ex->doDefaultStartAction("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 8350, 0);
        ex->Rethrow();
    }
}
