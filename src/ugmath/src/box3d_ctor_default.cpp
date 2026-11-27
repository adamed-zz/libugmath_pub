



























#pragma once

#include <cstddef>

namespace UGS {
namespace Math {

class alignas(8) Box3D {
public:


    virtual ~Box3D();

    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char dirty;
    double corners[8][3];
    unsigned long long cached;

    Box3D();
};

static_assert(sizeof(Box3D) == 0x150, "Box3D 必须为 336 字节");
static_assert(offsetof(Box3D, matrix) == 0x08);
static_assert(offsetof(Box3D, origin) == 0x50);
static_assert(offsetof(Box3D, length) == 0x68);
static_assert(offsetof(Box3D, dirty) == 0x80);
static_assert(offsetof(Box3D, corners) == 0x88);
static_assert(offsetof(Box3D, cached) == 0x148);

}
}


namespace UGS {
namespace Math {




__declspec(noinline) Box3D::~Box3D() {}

Box3D::Box3D()
{
    cached = 0;
    dirty = 0;


    matrix[0] = 1.0;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 1.0;
    matrix[5] = 0.0;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = 1.0;


    origin[2] = 0.0;
    origin[1] = 0.0;
    origin[0] = 0.0;


    length[0] = 0.0;
    length[1] = 0.0;
    length[2] = 0.0;


    corners[0][2] = 0.0; corners[0][1] = 0.0; corners[0][0] = 0.0;
    corners[1][2] = 0.0; corners[1][1] = 0.0; corners[1][0] = 0.0;
    corners[2][2] = 0.0; corners[2][1] = 0.0; corners[2][0] = 0.0;
    corners[3][2] = 0.0; corners[3][1] = 0.0; corners[3][0] = 0.0;
    corners[4][2] = 0.0; corners[4][1] = 0.0; corners[4][0] = 0.0;
    corners[5][2] = 0.0; corners[5][1] = 0.0; corners[5][0] = 0.0;
    corners[6][2] = 0.0; corners[6][1] = 0.0; corners[6][0] = 0.0;
    corners[7][2] = 0.0; corners[7][1] = 0.0; corners[7][0] = 0.0;
}

}
}
