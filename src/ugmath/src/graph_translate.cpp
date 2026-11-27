







#include <cstddef>
#include <emmintrin.h>












#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace UGS {
namespace Memory {




struct CppMemory {
    static void* __cdecl allocate(std::size_t n);
    static void __cdecl free(void* p);
};

template <class T>
class SMAlloc {
public:
    using value_type = T;

    SMAlloc() noexcept = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(CppMemory::allocate(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept { CppMemory::free(p); }

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

class Graph;
class Box3D;

typedef std::vector<int, Memory::SMAlloc<int>> IntVector;
typedef std::vector<double, Memory::SMAlloc<double>> DoubleVector;
typedef std::vector<Point3, Memory::SMAlloc<Point3>> Point3Vector;
typedef std::pair<int, Point3> IndexedPoint3;
typedef std::vector<IndexedPoint3, Memory::SMAlloc<IndexedPoint3>>
    IndexedPoint3Vector;
typedef std::pair<int, int> IndexPair;
typedef std::pair<Point3, Point3> Point3Pair;
typedef std::vector<Point3Pair, Memory::SMAlloc<Point3Pair>> Point3PairVector;
typedef std::vector<IntVector, Memory::SMAlloc<IntVector>> IntVectorVector;

static_assert(sizeof(Point3) == 24, "Point3 ABI");
static_assert(sizeof(Vector3) == 24, "Vector3 ABI");
static_assert(sizeof(IndexedPoint3) == 32, "pair<int,Point3> ABI");
static_assert(sizeof(IntVector) == 24, "vector ABI");
static_assert(sizeof(IntVectorVector) == 24, "vector<vector> ABI");

class Graph {
public:
    int m_vertexCount;
    std::int32_t m_pad0;
    double* m_vertexArray;
    int m_edgeCount;
    std::int32_t m_pad1;
    int* m_edgeArray;
    DoubleVector m_vertices;
    IntVector m_edges;

    Graph();
    Graph(const Graph&);
    ~Graph();
    Graph& operator=(const Graph&);

    void MakeInternalCopy() const;
    void IdentifyVertexToEdgeConnectivity(IntVectorVector& conn) const;
    int VertexCount() const;

    void GetOneVertexCoordinates(int vertex, Point3& out) const;
    void GetEdgeMidPoint(int edge, Point3& out) const;
    bool IsSubGraphCoincidentToPoint(const IntVector& subGraphEdges,
                                     const Point3& point, double tol) const;
    void GenerateSubGraphOneTrackingPoint(const IntVector& edges,
                                          const IntVectorVector& conn,
                                          Point3& out) const;
    void GenerateSubGraphTrackingPoints(const IntVectorVector& subGraphEdges,
                                        Point3Vector& out) const;

    void Translate(const Vector3& offset);
    void TrackSubGraphs(const IntVectorVector& subGraphs, Point3Vector& points,
                        IntVector& indices, double tolerance) const;

    static double m_distanceTolerance;

    friend struct GraphGate;

private:


    void UpdateEdgeToVertexConnectivity(const IntVector& vertexRemap);
    static bool VertexLessThan(const IndexedPoint3& a,
                               const IndexedPoint3& b);
};

static_assert(sizeof(Graph) == 80, "Graph size ABI");
static_assert(offsetof(Graph, m_vertexCount) == 0, "Graph +0");
static_assert(offsetof(Graph, m_vertexArray) == 8, "Graph +8");
static_assert(offsetof(Graph, m_edgeCount) == 16, "Graph +16");
static_assert(offsetof(Graph, m_edgeArray) == 24, "Graph +24");
static_assert(offsetof(Graph, m_vertices) == 32, "Graph +32");
static_assert(offsetof(Graph, m_edges) == 56, "Graph +56");

struct GraphGate {
    static IntVector& Edges(Graph& g) { return g.m_edges; }
    static DoubleVector& Vertices(Graph& g) { return g.m_vertices; }
    static bool Less(const IndexedPoint3& a, const IndexedPoint3& b) {
        return Graph::VertexLessThan(a, b);
    }
    static void UpdateEdges(Graph& g, const IntVector& remap) {
        g.UpdateEdgeToVertexConnectivity(remap);
    }
    static void Track(const Graph& g, const IntVectorVector& subGraphs,
                      Point3Vector& points, IntVector& indices,
                      double tolerance) {
        g.TrackSubGraphs(subGraphs, points, indices, tolerance);
    }
};

}
}


namespace UGS {
namespace Math {

void Graph::Translate(const Vector3& offset) {
    MakeInternalCopy();
    int n = 0;
    if (m_vertexArray) {
        n = m_vertexCount;
        MakeInternalCopy();
    } else {
        n = static_cast<int>(m_vertices.size() / 3u);
    }
    double* p = m_vertices.data();
    int i = 0;
    for (; i + 4 <= n; i += 4) {
        for (int k = 0; k < 4; ++k) {
            p[3 * (i + k)] += offset.x;
            p[3 * (i + k) + 1] += offset.y;
            p[3 * (i + k) + 2] += offset.z;
        }
    }

    const __m128d ox = _mm_set_sd(offset.x);
    const __m128d oy = _mm_set_sd(offset.y);
    const __m128d oz = _mm_set_sd(offset.z);
    for (; i < n; ++i) {
        _mm_store_sd(&p[3 * i], _mm_add_sd(ox, _mm_load_sd(&p[3 * i])));
        _mm_store_sd(&p[3 * i + 1], _mm_add_sd(oy, _mm_load_sd(&p[3 * i + 1])));
        _mm_store_sd(&p[3 * i + 2], _mm_add_sd(oz, _mm_load_sd(&p[3 * i + 2])));
    }
}

}
}
