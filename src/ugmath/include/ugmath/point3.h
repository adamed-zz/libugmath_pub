#pragma once




namespace UGS {
namespace Math {

struct Point3 {
    double x;
    double y;
    double z;

    Point3() = default;
    Point3(double a, double b, double c) : x(a), y(b), z(c) {}
};

}
}
