








#include <cmath>
#include <cstddef>
#include <cstring>
#include <new>
#include <vector>

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
}
}


struct FACET_facet_normal_s {
    UGS::Math::Point3 pts[3];
    int               ids[3];
    UGS::Math::Vector3 normal;
};
static_assert(sizeof(FACET_facet_normal_s) == 0x70, "FACET_facet_normal_s 必须为 112 字节");

enum FACET_weight_t {
    FACET_WEIGHT_AREA  = 0,
    FACET_WEIGHT_ANGLE = 1
};

namespace UGS {
namespace Memory {


struct CppMemory {
    __declspec(dllimport) static void* __cdecl allocate(std::size_t bytes);
    __declspec(dllimport) static void __cdecl free(void* p);
};


template <class T>
struct SMAlloc {
    using value_type = T;

    SMAlloc() noexcept = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(CppMemory::allocate(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept {
        CppMemory::free(p);
    }

    template <class U>
    bool operator==(const SMAlloc<U>&) const noexcept {
        return true;
    }
    template <class U>
    bool operator!=(const SMAlloc<U>&) const noexcept {
        return false;
    }
};

}
}



__declspec(dllimport) __declspec(noreturn) void __cdecl ERROR_internal(const char* file, int line,
                                                                       const char* message, ...);


double __cdecl FACET_ask_triangle_area(UGS::Math::Point3* p0, UGS::Math::Point3* p1, UGS::Math::Point3* p2);
void __cdecl FACET_shepards_weights(int count, double* const weights, double d2, double power, double* const out);
double __cdecl VEC3_angle_between(const UGS::Math::Vector3* a, const UGS::Math::Vector3* b,
                                  const UGS::Math::Vector3* normal);
int __cdecl VEC3_unitize(const UGS::Math::Vector3* v, double tolerance, double* magnitude,
                         UGS::Math::Vector3* out);

namespace {
const char* const FACET_SRC_FILE = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\facet_util_math.c";
}

void FACET_interp_normal_at_vertex(
    UGS::Math::Point3* common_vertex,
    int vertex_index,
    int num_facets,
    FACET_facet_normal_s* const facets,
    FACET_weight_t weight_type,
    double* const params,
    UGS::Math::Vector3* out_normal) {
    UGS::Math::Vector3 acc       = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 next_edge = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 prev_edge = {0.0, 0.0, 0.0};
    double d2 = *params * 0.5 * *params;
    if (weight_type == FACET_WEIGHT_ANGLE && common_vertex == nullptr) {
        ERROR_internal(FACET_SRC_FILE, 964, "The common vertex is not input as expected.");
    }
    std::vector<double, UGS::Memory::SMAlloc<double>>out_weights(num_facets);
    std::vector<double, UGS::Memory::SMAlloc<double>>in_weights(num_facets);
    for (int face = 0; face < num_facets; ++face) {
        double w;
        if (weight_type == FACET_WEIGHT_AREA) {
            double area = FACET_ask_triangle_area(&facets[face].pts[0], &facets[face].pts[1], &facets[face].pts[2]);
            if (d2 > area) {
                ERROR_internal(FACET_SRC_FILE, 988, "Zero area facet occurred.");
            }
            w = 1.0 / area;
        } else {
            if (weight_type != FACET_WEIGHT_ANGLE) {
                ERROR_internal(FACET_SRC_FILE, 1041, "The requested type of weights is not recognizable.");
            }
            int found = -1;
            int i     = 0;
            int next  = 0;
            for (int j = 0; j < 3; ++j) {
                next = i + 1;
                if (facets[face].ids[i] == vertex_index) {
                    found = j;
                    break;
                }
                i = next;
            }
            int nxt = next % 3;
            int prv = (i + 2) % 3;
            if (found == -1) {
                ERROR_internal(FACET_SRC_FILE, 1013, "The facet is not incident at the given vertex.");
            }
            const UGS::Math::Point3& vm = facets[face].pts[found];
            next_edge.x = facets[face].pts[nxt].x - vm.x;
            next_edge.y = facets[face].pts[nxt].y - vm.y;
            next_edge.z = facets[face].pts[nxt].z - vm.z;
            prev_edge.x = facets[face].pts[prv].x - vm.x;
            prev_edge.y = facets[face].pts[prv].y - vm.y;
            prev_edge.z = facets[face].pts[prv].z - vm.z;
            double angle = VEC3_angle_between(&prev_edge, &next_edge, &facets[face].normal);
            double degrees = fabs(angle) * 57.29577951308235;
            if (degrees < params[1])
                degrees = params[1];
            w = 1.0 / degrees;
        }
        in_weights[face] = w;
    }
    FACET_shepards_weights(num_facets, in_weights.data(), d2, 1.0, out_weights.data());
    acc.x = 0.0;
    acc.y = 0.0;
    acc.z = 0.0;
    for (int i = 0; i < num_facets; ++i) {
        acc.x += out_weights[i] * facets[i].normal.x;
        acc.y += out_weights[i] * facets[i].normal.y;
        acc.z += out_weights[i] * facets[i].normal.z;
    }
    double magnitude;
    VEC3_unitize(&acc, 1.0e-10, &magnitude, out_normal);
}
