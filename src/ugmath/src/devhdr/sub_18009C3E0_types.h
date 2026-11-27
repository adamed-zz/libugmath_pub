#pragma once


namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};


struct Matrix3
{
    double m[9];
};
}
}


extern "C"
{
    __declspec(dllimport) extern bool RDEBUG__enabled;
    __declspec(dllimport) int RDEBUG_ask_flag(const char *, bool);
}
__declspec(dllimport) int lprintf(const char *, ...);




bool MTX3_is_ortho_normal(const UGS::Math::Matrix3 *m, double tolerance);

int MTX3_init_y_z(const UGS::Math::Vector3 *y, const UGS::Math::Vector3 *z,
                  UGS::Math::Matrix3 *m);

void MTX3_lprintf(int indent, const char *label, const UGS::Math::Matrix3 *m);

extern "C" int sub_18009C880(double *before, double *after);
