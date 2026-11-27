


















#include <cstddef>
#include <cstdint>
#include <new>
#include <vector>

namespace UGS {
namespace Memory {


template <class T>
struct SMAlloc {
    using value_type = T;
    SMAlloc() = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T), std::align_val_t(8)));
    }
    void deallocate(T* p, std::size_t) {
        ::operator delete(p, std::align_val_t(8));
    }
    template <class U>
    bool operator==(const SMAlloc<U>&) const {
        return true;
    }
    template <class U>
    bool operator!=(const SMAlloc<U>&) const {
        return false;
    }
};

}

namespace Math {

struct Point2 {
    double x;
    double y;
};

struct Point3 {
    double x;
    double y;
    double z;
};


struct Matrix3 {
    double m[9];
};

struct Vector3 {
    double x;
    double y;
    double z;
};


class alignas(8) Box3D {
public:
    void* vftable;
    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char derived;
    unsigned char pad[7];
    double corners[8][3];
    double radius;


    Box3D(const Matrix3& orientation, const Point3& origin, const double* const lengths);
    bool DoesBoxIntersect(Box3D& other);
    bool DoesBoxIntersectPercent(Box3D& other, double percent);
    bool DoesBoxSurround(Box3D& other);
    bool DoesBoxSurroundPercent(Box3D& other, double percent);
    bool ExpandToIncludePoint(const Point3& p);
    bool ExpandToIncludePoints(
        const std::vector<Point3, Memory::SMAlloc<Point3>>& pts);
    void Get2DMinMax(void (*map)(const Point3&, void*, Point2&), void* ctx,
                     double percent, Point2& min_pt, Point2& max_pt) const;
    Point3 GetCentroid() const;
    double GetMaxPoint(int index) const;


    void deriveData();
    double GetRadius() const;
    Point3 GetXYZCorner() const;
    Point3 GetXYCorner() const;
    Point3 GetXZCorner() const;
    Point3 GetYZCorner() const;
    double GetMinPoint(int index) const;
    bool IsBoxInside(Box3D& box, double tolerance);
    bool IsBoxInsidePercent(Box3D& box, double percent);
    bool IsBoxAligned(const Box3D& box) const;
    bool getIntersectStatus(const Box3D& box, double tolerance) const;
};

static_assert(sizeof(Point2) == 16, "Point2 ABI");
static_assert(sizeof(Point3) == 24, "Point3 ABI");
static_assert(sizeof(Matrix3) == 72, "Matrix3 ABI");
static_assert(sizeof(Box3D) == 336, "Box3D ABI");
static_assert(offsetof(Box3D, vftable) == 0, "Box3D vftable");
static_assert(offsetof(Box3D, matrix) == 8, "Box3D matrix");
static_assert(offsetof(Box3D, origin) == 80, "Box3D origin");
static_assert(offsetof(Box3D, length) == 104, "Box3D length");
static_assert(offsetof(Box3D, derived) == 128, "Box3D derived");
static_assert(offsetof(Box3D, corners) == 136, "Box3D corners");
static_assert(offsetof(Box3D, radius) == 328, "Box3D radius");


int eqz(const double* a, const double* b, const int* code);
void h600a(const double* p, const double* q, const double* r,
           const double* s, int* code, double* out);
double EQ_ask_number_tolerance();
bool MTX3_is_identity(const Matrix3* m, double tol);
int MTX3_init_x_y_z(const Vector3* x, const Vector3* y, const Vector3* z,
                    Matrix3* out);
int sub_180068630(Matrix3* m);

}
}


__declspec(dllimport) double __cdecl EQ_ask_number_tolerance();

void __cdecl m4053(double* a, double* b, int* status) {
    *status = 2;
    if (EQ_ask_number_tolerance() + b[2] > a[0] &&
        EQ_ask_number_tolerance() + b[3] > a[1] &&
        a[2] > b[0] - EQ_ask_number_tolerance() &&
        a[3] > b[1] - EQ_ask_number_tolerance()) {
        *status = 1;
    }
}
