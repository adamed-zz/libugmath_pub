


















#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>


union BOX3_s;

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

class Graph;
class Box3D;
struct GraphGate;

typedef std::vector<int, Memory::SMAlloc<int>> IntVector;
typedef std::vector<double, Memory::SMAlloc<double>> DoubleVector;
typedef std::vector<Point3, Memory::SMAlloc<Point3>> Point3Vector;
typedef std::pair<int, Point3> IndexedPoint3;
typedef std::vector<IndexedPoint3, Memory::SMAlloc<IndexedPoint3>>
    IndexedPoint3Vector;
typedef std::pair<int, int> IndexPair;
typedef std::vector<IndexPair, Memory::SMAlloc<IndexPair>> IndexPairVector;
typedef std::pair<Point3, Point3> Point3Pair;
typedef std::vector<Point3Pair, Memory::SMAlloc<Point3Pair>> Point3PairVector;
typedef std::vector<IntVector, Memory::SMAlloc<IntVector>> IntVectorVector;

static_assert(sizeof(Point3) == 24, "Point3 ABI");
static_assert(sizeof(IndexedPoint3) == 32, "pair<int,Point3> ABI");
static_assert(sizeof(Point3Pair) == 48, "pair<Point3,Point3> ABI");
static_assert(sizeof(IntVector) == 24, "vector ABI");
static_assert(sizeof(IndexPair) == 8, "pair<int,int> ABI");

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

    void ComputeBoundingBox(BOX3_s& box) const;
    void ComputeSubGraphBoundingBox(const IntVector& subGraphEdges,
                                    Box3D& box) const;
    void GenerateSubGraphOneTrackingPoint(const IntVector& edges,
                                          const IntVectorVector& conn,
                                          Point3& out) const;
    void GenerateSubGraphTrackingPoints(const IntVectorVector& edges,
                                        Point3Vector& out) const;
    DoubleVector& GetAllVertexCoordinatesForMutation();
    void GetAllVertexCoordinates(Point3Vector& out) const;
    void GetAllVertices(IntVector& out) const;
    int GetEdgeCount() const;
    int GetEdgeEndVertex(int edge) const;
    void GetEdgeMidPoint(int edge, Point3& out) const;
    int GetEdgeStartVertex(int edge) const;
    IntVector& GetEdgeToVertexConnectivityForMutation();
    void GetEdgeToVertexConnectivity(IndexPairVector& out) const;
    const int* GetEdgeToVertexConnectivityBeginIterator() const;
    IntVector::iterator GetEdgeToVertexConnectivityBeginIteratorForMutation();
    const int* GetEdgeToVertexConnectivityEndIterator() const;
    IntVector::iterator GetEdgeToVertexConnectivityEndIteratorForMutation();
    void GetExpandedEdges(Point3PairVector& out) const;
    void GetFreeVertices(IntVector& out) const;
    void GetOneEdgeConnectivity(int edge, int& start, int& end) const;
    const double* GetOneVertexCoordinateBeginIterator(int vertex) const;
    DoubleVector::iterator GetOneVertexCoordinateBeginIteratorForMutation(
        int vertex);
    void GetOneVertexCoordinates(int vertex, Point3& out) const;

    static double m_distanceTolerance;

    friend struct GraphGate;

private:

    void GenerateSortedVerticesByDistance(IndexedPoint3Vector& out) const;
};

static_assert(sizeof(Graph) == 80, "Graph size ABI");
static_assert(offsetof(Graph, m_vertexCount) == 0, "Graph +0");
static_assert(offsetof(Graph, m_vertexArray) == 8, "Graph +8");
static_assert(offsetof(Graph, m_edgeCount) == 16, "Graph +16");
static_assert(offsetof(Graph, m_edgeArray) == 24, "Graph +24");
static_assert(offsetof(Graph, m_vertices) == 32, "Graph +32");
static_assert(offsetof(Graph, m_edges) == 56, "Graph +56");

struct GraphGate {
    static void GenerateSortedVerticesByDistance(const Graph* g,
                                                 IndexedPoint3Vector& out) {
        g->GenerateSortedVerticesByDistance(out);
    }
};

class Box3D {
public:
    void* m_vptr;
    double m_f[41];

    Box3D();
    Box3D& operator=(const Box3D&);
    void WrapPoints(const Point3Vector& pts);
};

static_assert(sizeof(Box3D) == 336, "Box3D size ABI");
static_assert(offsetof(Box3D, m_f) == 8, "Box3D +8");

}
}


union BOX3_s {
    double d[6];
};



namespace UGS {
namespace Math {

static __int64 internalVertexCount(const Graph* g) {
    if (!g->m_vertexArray)
        return static_cast<__int64>(g->m_vertices.size() / 3);
    return g->m_vertexCount;
}

const double* Graph::GetOneVertexCoordinateBeginIterator(int vertex) const {
    const double* v = m_vertexArray;
    const int n = static_cast<int>(internalVertexCount(this));
    if (!n)
        v = 0;
    else if (!v)
        v = m_vertices.data();
    return v + vertex * 3;
}

}
}
