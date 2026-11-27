




















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
struct GraphGate;

typedef std::vector<int, Memory::SMAlloc<int>> IntVector;
typedef std::vector<double, Memory::SMAlloc<double>> DoubleVector;
typedef std::vector<Point3, Memory::SMAlloc<Point3>> Point3Vector;
typedef std::vector<bool, Memory::SMAlloc<bool>> BoolVector;
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


    const double* GetVertexCoordinateBeginIterator() const;
    DoubleVector::iterator GetVertexCoordinateBeginIteratorForMutation();
    const double* GetVertexCoordinateEndIterator() const;
    DoubleVector::iterator GetVertexCoordinateEndIteratorForMutation();
    int GetVertexCount() const;
    void IdentifyInteriorFreeVertices(const Box3D& box, double tol,
                                      IntVector& out) const;
    void IdentifyMissingAdjacentConnectivity(const Box3D& box, double tol,
                                             IndexPairVector& pairs,
                                             Point3Vector& points) const;
    void IdentifyVertexToEdgeConnectivity(IntVectorVector& conn) const;
    void IdentifyVerticesCoincidentToBox(const Box3D& box, double tol,
                                         IntVector& v1, IntVector& v2,
                                         IntVector& v3, IntVector& v4,
                                         IntVector& v5, IntVector& v6,
                                         IntVector& v7) const;
    void IdentifyVerticesOutsideBoundingBox(const Box3D& box, double tol,
                                            IntVector& out) const;
    void InitializeUsingArrays(int nv, const double* verts, int ne,
                               const int* edges);
    void Insert(const Graph& other);
    bool IsSubGraphCoincidentToPoint(const IntVector& edges,
                                     const Point3& p, double tol) const;
    void PatternAlongMajorAxis(double spacing, int a2, int a3, int a4);
    void RemoveEdges(const IntVector& removed);
    void SetAllVertexCoordinates(const Point3Vector& pts);
    void SetVertexCoordinates(int vertex, const Point3& p);
    void TraceConnectedSubGraphs(IntVectorVector& out) const;


    int VertexCount() const;
    void GetAllVertices(IntVector& out) const;
    void GetFreeVertices(IntVector& out) const;
    int GetEdgeStartVertex(int edge) const;
    int GetEdgeEndVertex(int edge) const;
    void GetEdgeMidPoint(int edge, Point3& out) const;
    void AppendImmediateNeighbors(int vertex, const IntVectorVector& conn,
                                  BoolVector& visited, IntVector& out) const;
    void ComplementVertices(const Box3D& box, int axis, double tol,
                            const IntVector& listA, const IntVector& listB,
                            IndexPairVector& pairs,
                            Point3Vector& points) const;
    void CompressVertices(const IntVector& removedIndices);
    void Translate(const Vector3& offset);

    static double m_distanceTolerance;

private:
    void IdentifyOldToNewVertexMap(const IntVector& removed,
                                   IntVector& map) const;
    void IdentifyOrphanVertices(const IntVector& freeVertices,
                                const IntVector& usedVertices,
                                IntVector& out);
    void MakeInternalCopy() const;
    int MapCompressedVertices(const IndexedPoint3Vector& sorted, IntVector& a2,
                              IntVector& a3) const;
    void RemoveEdgesFromConnectivityMap(const IntVector& removed,
                                        IntVectorVector& a2,
                                        IntVectorVector& a3);
    static bool SameVertexPosition(const IndexedPoint3& a,
                                   const IndexedPoint3& b);

    friend struct GraphGate;
};

static_assert(sizeof(Graph) == 80, "Graph size ABI");
static_assert(offsetof(Graph, m_vertexCount) == 0, "Graph +0");
static_assert(offsetof(Graph, m_vertexArray) == 8, "Graph +8");
static_assert(offsetof(Graph, m_edgeCount) == 16, "Graph +16");
static_assert(offsetof(Graph, m_edgeArray) == 24, "Graph +24");
static_assert(offsetof(Graph, m_vertices) == 32, "Graph +32");
static_assert(offsetof(Graph, m_edges) == 56, "Graph +56");

class Box3D {
public:
    void* vftable;
    double matrix[9];
    double origin[3];
    double length[3];
    unsigned char dirty;
    unsigned char pad[7];
    double corners[8][3];
    unsigned long long cached;

    Box3D();
    Box3D& operator=(const Box3D& other);
    void WrapPoints(const Point3Vector& pts);
    Point3 GetOrigin() const;
    bool IsPointInside(const Point3& p, double tol) const;
    bool IsInteriorPoint(const Point3& p, double tol) const;
    bool IsPointCoincidentToBox(const Point3& p, double tol, bool& onCorner,
                                bool& onEdge, bool& onFace, int& faceA,
                                int& faceB, int& cornerIdx) const;
    static bool IsCoincidentToCorner(bool* const minFlags,
                                     bool* const maxFlags, int& faceA,
                                     int& faceB, int& corner);
    static bool IsCoincidentToEdge(bool* const minFlags, bool* const maxFlags,
                                   int& faceA, int& faceB);
    static bool IsCoincidentToFace(bool* const minFlags, bool* const maxFlags,
                                   int& faceA);
};

static_assert(sizeof(Box3D) == 336, "Box3D size ABI");
static_assert(offsetof(Box3D, matrix) == 8, "Box3D +8");
static_assert(offsetof(Box3D, origin) == 80, "Box3D +80");
static_assert(offsetof(Box3D, length) == 104, "Box3D +104");
static_assert(offsetof(Box3D, dirty) == 128, "Box3D +128");
static_assert(offsetof(Box3D, corners) == 136, "Box3D +136");
static_assert(offsetof(Box3D, cached) == 328, "Box3D +328");


struct GraphGate {
    static void IdentifyOldToNewVertexMap(const Graph* g,
                                          const IntVector& removed,
                                          IntVector& map) {
        g->IdentifyOldToNewVertexMap(removed, map);
    }
    static void IdentifyOrphanVertices(Graph* g, const IntVector& a,
                                       const IntVector& b, IntVector& out) {
        g->IdentifyOrphanVertices(a, b, out);
    }
    static void MakeInternalCopy(const Graph* g) { g->MakeInternalCopy(); }
    static int MapCompressedVertices(const Graph* g,
                                     const IndexedPoint3Vector& sorted,
                                     IntVector& a2, IntVector& a3) {
        return g->MapCompressedVertices(sorted, a2, a3);
    }
    static void RemoveEdgesFromConnectivityMap(Graph* g,
                                               const IntVector& removed,
                                               IntVectorVector& a2,
                                               IntVectorVector& a3) {
        g->RemoveEdgesFromConnectivityMap(removed, a2, a3);
    }
    static bool SameVertexPosition(const IndexedPoint3& a,
                                   const IndexedPoint3& b) {
        return Graph::SameVertexPosition(a, b);
    }
    static void AppendImmediateNeighbors(const Graph* g, int v,
                                         const IntVectorVector& conn,
                                         BoolVector& visited,
                                         IntVector& out) {
        g->AppendImmediateNeighbors(v, conn, visited, out);
    }
    static void ComplementVertices(const Graph* g, const Box3D& box, int axis,
                                   double tol, const IntVector& a,
                                   const IntVector& b, IndexPairVector& pairs,
                                   Point3Vector& pts) {
        g->ComplementVertices(box, axis, tol, a, b, pairs, pts);
    }
    static void CompressVertices(Graph* g, const IntVector& removed) {
        g->CompressVertices(removed);
    }
};

}
}



namespace UGS {
namespace Math {

static __int64 internalVertexCount(const Graph* g) {
    if (!g->m_vertexArray)
        return static_cast<__int64>(g->m_vertices.size() / 3);
    return g->m_vertexCount;
}

int Graph::GetVertexCount() const {
    return static_cast<int>(internalVertexCount(this));
}

}
}
