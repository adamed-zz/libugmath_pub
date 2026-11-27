#pragma once

#include <array>
#include <cstddef>

#include "ugmath/vec3.h"



namespace ugmath {

struct Mat4 {

    std::array<double, 16> e{};

    constexpr Mat4() = default;

    static constexpr Mat4 identity() {
        Mat4 m;
        m.e[0] = 1.0;
        m.e[5] = 1.0;
        m.e[10] = 1.0;
        m.e[15] = 1.0;
        return m;
    }

    constexpr double& operator()(std::size_t row, std::size_t col) {
        return e[row * 4 + col];
    }

    constexpr const double& operator()(std::size_t row, std::size_t col) const {
        return e[row * 4 + col];
    }

    constexpr double* data() noexcept {
        return e.data();
    }

    constexpr const double* data() const noexcept {
        return e.data();
    }
};

Mat4 operator*(const Mat4& lhs, const Mat4& rhs);


Vec3 transformPoint(const Mat4& m, const Vec3& p);


Vec3 transformVector(const Mat4& m, const Vec3& v);


bool approxEquals(const Mat4& a, const Mat4& b, double eps = 1e-12);

}
