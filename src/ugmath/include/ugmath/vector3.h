#pragma once




namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;

    Vector3() = default;
    Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
};

}
}
