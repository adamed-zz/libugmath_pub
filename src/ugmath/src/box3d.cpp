#include "ugmath/box3d.h"

#include <cstring>
#include <intrin.h>







namespace UGS {
namespace Math {

double Box3D::GetXLength() const {
    return length[0];
}

double Box3D::GetYLength() const {
    return length[1];
}

double Box3D::GetZLength() const {
    return length[2];
}

void Box3D::GetLengths(double* const out) const {
    out[0] = length[0];
    out[1] = length[1];
    out[2] = length[2];
}

Vector3 Box3D::GetXVector() const {
    return Vector3(matrix[0], matrix[1], matrix[2]);
}

Vector3 Box3D::GetYVector() const {
    return Vector3(matrix[3], matrix[4], matrix[5]);
}

Vector3 Box3D::GetZVector() const {
    return Vector3(matrix[6], matrix[7], matrix[8]);
}

void Box3D::FitAroundBox(Box3D box) {



















    dirty = 0;
    _ReadWriteBarrier();
    std::memcpy(origin, box.origin, 2 * sizeof(double));
    _ReadWriteBarrier();
    std::memcpy(origin + 2, box.origin + 2, sizeof(double));
    length[0] = 0.0;
    length[1] = 0.0;
    length[2] = 0.0;
    ExpandToIncludeBox(box);
}

double Box3D::GetMaxLength() const {
    double m = (length[1] > length[0]) ? length[1] : length[0];
    if (length[2] > m) m = length[2];
    return m;
}

double Box3D::GetMinLength() const {
    double m = (length[1] < length[0]) ? length[1] : length[0];
    if (length[2] < m) m = length[2];
    return m;
}

double Box3D::GetShortestLength() const {













    if (length[1] - 1.0e-10 > length[0]) {
        double result = length[0];
        if (!(length[2] - 1.0e-10 > length[0])) {
            result = length[2];
        }
        return result;
    } else {
        double result = length[1];
        if (!(length[2] - 1.0e-10 > length[1])) {
            result = length[2];
        }
        return result;
    }
}

double Box3D::GetVolume(double min_length) const {
    double x = (length[0] > min_length) ? length[0] : min_length;
    double y = (length[1] > min_length) ? length[1] : min_length;
    double z = (length[2] > min_length) ? length[2] : min_length;
    return x * y * z;
}

void Box3D::SetLengths(double a, double b, double c) {
    length[0] = a;
    length[1] = b;
    length[2] = c;
    dirty = 0;
}

void Box3D::SetXLength(double a) {
    length[0] = a;
    dirty = 0;
}

void Box3D::SetYLength(double a) {
    length[1] = a;
    dirty = 0;
}

void Box3D::SetZLength(double a) {
    length[2] = a;
    dirty = 0;
}

Point3 Box3D::GetOrigin() const {
    Point3 p;
    std::memcpy(&p, origin, sizeof(p));
    return p;
}

void Box3D::SetOrigin(const Point3& p) {
    std::memcpy(origin, &p, sizeof(origin));
    dirty = 0;
}

Matrix3 Box3D::GetOrientation() const {
    Matrix3 out;
    std::memcpy(out.m, matrix, sizeof(out.m));
    return out;
}

void Box3D::SetOrientation(const Matrix3& orientation) {













    dirty = 0;
    std::memcpy(matrix, orientation.m, sizeof(matrix));
    sub_180068630(reinterpret_cast<Matrix3*>(matrix));
}

}
}
