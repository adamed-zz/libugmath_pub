









namespace UGS { namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
} }

using UGS::Math::Point3;
using UGS::Math::Vector3;

__declspec(dllimport) void* SM_alloc(unsigned __int64 n);
__declspec(dllimport) void SM_free(void* p);
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);
__declspec(dllimport) int MACH__checking_level;

double VEC3_angle_between(const Vector3* a, const Vector3* b, const Vector3* c);
char sub_1800259C0(int n, int* indices, Point3* points, Vector3* normals,
                   int i1, int i2, int i3);

void FACET_ask_triangles_of_polygon(int a1, Point3* a2, Vector3* a3, int* a4)
{
    unsigned __int64 v4;
    int v5;
    int v56;
    Point3* v6;
    __int64 v7;
    int v9;
    int* v10;
    char v18;
    int v19;
    char* v20;
    __int64 v21;
    __int64 v22;
    int v23;
    int v24;
    __int64 v25;
    char v26;
    __int64 v27;
    __int64 v28;
    __int64 v29;
    __int64 v30;
    __int64 v31;
    double v32, v33, v34, v35, v36, v37;
    char v38;
    int v39;
    int v40;
    __int64 v41, v42;
    int v43;
    __int64 v44;
    int v45;
    int v46;
    char v47;
    int v48;
    int* v49;
    int v50;
    int v51;
    int* v52;
    __int64 v53;
    int* v54;
    char v55;
    int v57;
    int v58;
    int v59;
    __int64 v60;
    char* v62;
    __int64 v63;
    int* v64;
    int v65;
    __int64 v66;
    double v67[3];
    double v68[3];
    int v69;

    v4 = a1;
    v5 = 0;
    v56 = 0;
    v6 = a2;
    if ( a1 == 3 )
    {
        *a4 = 0;
        a4[1] = 1;
        a4[2] = 2;
        return;
    }
    v7 = a1;
    v10 = (int*)SM_alloc(4LL * a1);
    for ( v9 = 0; v9 < a1; v9++ )
        v10[v9] = v9;
    v62 = (char*)SM_alloc(a1);
    v20 = v62;
    v18 = 0;
    v19 = -1;
    v55 = 0;
    v65 = -1;
    if ( (int)v4 > 2 )
    {
        v21 = -1;
        v64 = a4 + 2;
        v66 = -1;
        v69 = 0;
        do
        {
            v63 = v7;
            v22 = v7;
            if ( !v18 )
            {
                v23 = 0;
                v18 = 1;
                v55 = 1;
                v59 = 0;
                if ( v7 > 0 )
                {
                    v24 = (int)v4 - 1;
                    v25 = 0;
                    v26 = 1;
                    v57 = v24;
                    do
                    {
                        v27 = v25 + 1;
                        v28 = 0;
                        if ( v23 != v24 )
                            v28 = v25 + 1;
                        v29 = 3LL * v10[v28];
                        v30 = v7;
                        if ( v25 )
                            v30 = v25;
                        v31 = v10[v30 - 1];
                        v32 = ((double*)v6)[3 * v31 + 1] - ((double*)v6)[3 * v10[v25] + 1];
                        v33 = ((double*)v6)[3 * v31] - ((double*)v6)[v29];
                        v34 = ((double*)v6)[3 * v31 + 1] - ((double*)v6)[v29 + 1];
                        v35 = ((double*)v6)[3 * v31 + 2] - ((double*)v6)[3 * v10[v25] + 2];
                        v36 = ((double*)v6)[3 * v31 + 2] - ((double*)v6)[v29 + 2];
                        v68[0] = ((double*)v6)[3 * v31] - ((double*)v6)[3 * v10[v25]];
                        v68[1] = v32;
                        v67[0] = v33;
                        v68[2] = v35;
                        v67[1] = v34;
                        v67[2] = v36;
                        v37 = VEC3_angle_between((const Vector3*)v68, (const Vector3*)v67, a3);
                        v20 = v62;
                        v38 = 0;
                        v62[v25++] = v37 <= 3.141592653589793;
                        if ( v37 <= 3.141592653589793 )
                            v38 = v26;
                        v23 = ++v59;
                        v26 = v38;
                        v24 = v57;
                    }
                    while ( v27 < v7 );
                    v19 = v65;
                    v22 = v7;
                    v21 = v66;
                    v55 = v26;
                    v18 = v26;
                }
            }
            v39 = (int)v4 - 1;
            v60 = v7 - 1;
            v40 = (int)v4;
            v69 = (int)v4 - 1;
        L26:
            v41 = 0;
            v42 = v22;
            if ( v19 + 1 < (int)v4 )
                v41 = v21 + 1;
            v43 = 0;
            if ( v19 + 1 < (int)v4 )
                v43 = v19 + 1;
            if ( v43 )
                v42 = v41;
            v44 = 0;
            if ( v43 != v39 )
                v44 = v41 + 1;
            v58 = --v40;
            if ( !v40 || v18 )
                goto Lbreak;
            v19 = v43;
            v21 = v41;
            if ( !v20[v41] )
                goto L26;
            v45 = 0;
            if ( v43 != v39 )
                v45 = v43 + 1;
            v46 = (int)v4;
            if ( v43 )
                v46 = v43;
            v47 = sub_1800259C0((int)v4, v10, a2, a3, v46 - 1, v43, v45);
            v18 = v55;
            v39 = (int)v4 - 1;
            v40 = v58;
            v22 = v63;
            v20 = v62;
            if ( v47 )
                goto L26;
        Lbreak:
            v48 = v10[v41];
            v49 = &v10[v41];
            v50 = v10[v42 - 1];
            if ( v50 != v48 )
            {
                v51 = v10[v44];
                if ( v50 != v51 && v48 != v51 )
                {
                    if ( MACH__checking_level && v56 >= a1 - 2 )
                    {
                        ERROR_assertion_failed(
                            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\facet_util_math.c",
                            1196,
                            "%s",
                            "n_triangles < n_original_vertices - 2");
                        v50 = v10[v42 - 1];
                    }
                    ++v56;
                    *(v64 - 2) = v50;
                    *(v64 - 1) = *v49;
                    *v64 = v10[v44];
                    v64 += 3;
                }
            }
            v4 = (unsigned __int64)(unsigned int)(v4 - 1);
            if ( v41 < v60 )
            {
                v52 = v49 + 1;
                v53 = v60 - v41;
                v54 = &v10[v41];
                while ( v53 )
                {
                    *v54++ = *v52++;
                    --v53;
                }
            }
            v18 = v55;
            v19 = v43;
            v7 = v60;
            v21 = v41;
            v20 = v62;
            v66 = v41;
            v6 = a2;
            v65 = v19;
        }
        while ( v69 > 2 );
        v5 = v56;
    }
    SM_free(v20);
    SM_free(v10);
    if ( MACH__checking_level )
    {
        if ( v5 != a1 - 2 )
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\facet_util_math.c",
                1214,
                "%s",
                "n_triangles == n_original_vertices - 2");
    }
}
