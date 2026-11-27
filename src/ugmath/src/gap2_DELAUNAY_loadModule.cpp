


















#include "b37_math.h"

extern "C" {
#ifdef B37_GATE_BUILD
void* b37_delaunay_slots[72];
#endif
int b37_delaunay_loaded = 0;
}

#ifndef B37_GATE_BUILD


#pragma comment(linker, "/alternatename:b37_delaunay_slots=?delaunay_vtable@@3Udelaunay_vtable_s@@A")
#endif

namespace {






const char* const kNames[72] = {
    "Wm5_DelaunayGetVertexQuantity",
    "Wm5_DelaunayGetSimplexQuantity",
    "Wm5_DelaunayIsSliver",
    "Wm5_DelaunayGetIndices",
    "Wm5_DelaunayGetAdjacencies",
    "Wm5_DelaunayGetSliverAdjacencies",
    "Wm5_DelaunayGetSliverFlags",
    "Wm5_DelaunayGetTolerance",
    "Wm5_DelaunayGetQueryType",
    "Wm5_CreateDelaunay1dp",
    "Wm5_Delaunay1dGetVertices",
    "Wm5_Delaunay1dGetContainingSegment",
    "Wm5_Delaunay1dGetContainingSegmentThreadSafe",
    "Wm5_Delaunay1dGetLastSegment",
    "Wm5_Delaunay1dGetHull",
    "Wm5_Delaunay1dGetVertexSet",
    "Wm5_Delaunay1dGetBarycentricSet",
    "Wm5_Delaunay1dGetIndexSet",
    "Wm5_Delaunay1dDelete",
    "Wm5_CreateDelaunay2d",
    "Wm5_CreateDelaunay2dp",
    "Wm5_Delaunay2dGetSuperVertices",
    "Wm5_Delaunay2dGetPathLast",
    "Wm5_Delaunay2dGetPath",
    "Wm5_Delaunay2dGetLastEdge",
    "Wm5_Delaunay2dGetMin",
    "Wm5_Delaunay2dGetScale",
    "Wm5_Delaunay2dGetVertices",
    "Wm5_Delaunay2dGetScaledVertices",
    "Wm5_DelaunayGetDimension",
    "Wm5_Delaunay2dGetUniqueVertexQuantity",
    "Wm5_Delaunay2dGetDelaunay1",
    "Wm5_Delaunay2dGetLineOrigin",
    "Wm5_Delaunay2dGetLineDirection",
    "Wm5_Delaunay2dGetContainingTriangle",
    "Wm5_Delaunay2dGetContainingTriangleThreadSafe",
    "Wm5_Delaunay2dGetNearestTriangle",
    "Wm5_Delaunay2dSetStartingIndex",
    "Wm5_Delaunay2dGetMidIndex",
    "Wm5_Delaunay2dGetBarycentricSet",
    "Wm5_Delaunay2dGetIndexSet",
    "Wm5_Delaunay2dGetNumHullEdges",
    "Wm5_Delaunay2dGetHull",
    "Wm5_Delaunay2dDelete",
    "Wm5_CreateDelaunay3d",
    "Wm5_CreateDelaunay3dp",
    "Wm5_Delaunay3dGetSuperVertices",
    "Wm5_Delaunay3dGetPathLast",
    "Wm5_Delaunay3dGetPath",
    "Wm5_Delaunay3dGetLastFace",
    "Wm5_Delaunay3dGetMin",
    "Wm5_Delaunay3dGetScale",
    "Wm5_Delaunay3dGetVertices",
    "Wm5_Delaunay3dGetScaledVertices",
    "Wm5_Delaunay3dGetUniqueVertexQuantity",
    "Wm5_Delaunay3dGetDelaunay1",
    "Wm5_Delaunay3dGetLineOrigin",
    "Wm5_Delaunay3dGetLineDirection",
    "Wm5_Delaunay3dGetDelaunay2",
    "Wm5_Delaunay3dGetPlaneOrigin",
    "Wm5_Delaunay3dGetPlaneDirection",
    "Wm5_Delaunay3dGetContainingTetrahedron",
    "Wm5_Delaunay3dGetContainingTetrahedronThreadSafe",
    "Wm5_Delaunay3dGetNearestTetrahedron",
    "Wm5_Delaunay3dSetStartingIndex",
    "Wm5_Delaunay3dGetMidIndex",
    "Wm5_Delaunay3dGetBarycentricSet",
    "Wm5_Delaunay3dGetIndexSet",
    "Wm5_Delaunay3dGetNumHullTriangles",
    "Wm5_Delaunay3dGetHull",
    "Wm5_Delaunay3dDelete",
    "Wm5_Delaunay3dRecalculateValues",
};


const int kSlots[72] = {
    0, 6, 9, 1, 2, 3, 4, 8, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 24, 25, 26, 27, 28, 29, 32, 33, 5, 22, 23, 30, 31, 34, 35, 36, 37,
    38, 39, 40, 67, 68, 41, 42, 43, 46, 47, 48, 49, 50, 51, 57, 58, 44, 45,
    52, 53, 54, 55, 56, 59, 60, 61, 62, 63, 64, 65, 69, 70, 66, 71,
};

}

void DELAUNAY_loadModule() {
    if (b37_delaunay_loaded)
        return;




    try {
        UGS::System::Loader::Module* image = UGS::System::Loader::LDR_load_image("libwm5", 0);
        for (int i = 0; i < 72; ++i)
            b37_delaunay_slots[kSlots[i]] = (void*)UGS::System::Loader::LDR_find_symbol(image, kNames[i]);
        b37_delaunay_loaded = 1;
#ifndef B37_GATE_BUILD

        *(int*)((char*)b37_delaunay_slots + 0x240) = 1;
#endif
    } catch (...) {
        b37_delaunay_loaded = 0;
    }
}



