


















#pragma once







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

struct Matrix3 {
    double m[9];
};


inline Point3 operator-(const Point3& a, const Point3& b) {
    Point3 r;
    r.z = a.z - b.z;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

}
}




void MTX3_rot_about_axis(double angle_rad,
                         const UGS::Math::Vector3* axis,
                         UGS::Math::Matrix3* matrix);

void ARC_SPLINE_rotate_point_around_axis(UGS::Math::Point3* point,
                                         UGS::Math::Point3* axis_point,
                                         UGS::Math::Vector3* axis,
                                         double angle_deg,
                                         UGS::Math::Point3* out) {
    UGS::Math::Point3 d;
    d.x = point->x - axis_point->x;
    d.y = point->y - axis_point->y;
    d.z = point->z - axis_point->z;

    UGS::Math::Matrix3 m = {{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
    MTX3_rot_about_axis(angle_deg * 0.01745329251994328, axis, &m);

    UGS::Math::Point3 rotated;
    rotated.y = d.y * m.m[4] + d.x * m.m[3] + d.z * m.m[5] + axis_point->y;
    rotated.z = d.y * m.m[7] + d.x * m.m[6] + d.z * m.m[8] + axis_point->z;
    rotated.x = d.y * m.m[1] + d.x * m.m[0] + d.z * m.m[2] + axis_point->x;
    *out = rotated;
}
