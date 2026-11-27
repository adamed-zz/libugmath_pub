














typedef unsigned long long QWORD;
typedef unsigned short WORD;




extern "C" QWORD g_ugm_hlr_geom_desc;

extern "C" QWORD g_ugm_hlr_vloc_arr;

extern "C" double g_ugm_hlr_xform_mat[12];

extern "C" int g_ugm_hlr_vloc_norm;

extern "C" float g_ugm_hlr_min_x;
extern "C" float g_ugm_hlr_min_y;
extern "C" float g_ugm_hlr_max_x;
extern "C" float g_ugm_hlr_max_y;

extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);


__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);


struct UgmHlrVloc
{
    float x;
    float y;
    float z;
    int   pad0;
    void* link;
    WORD  flag;
    WORD  pad1[3];
};

void HLR_FACET_add_vloc(int a1, const double* const a2)
{
    if (a1 < 0 || a1 >= *reinterpret_cast<const int*>(g_ugm_hlr_geom_desc + 0x28))
    {
        char buf[20];
        STR_snprintf(buf, 0x14, "%d", a1);
        g_ugm_hlr_diag_cb(1, 1, buf);
    }
    else
    {

        float y = static_cast<float>(a2[0] * g_ugm_hlr_xform_mat[1]
                                   + a2[1] * g_ugm_hlr_xform_mat[4]
                                   + a2[2] * g_ugm_hlr_xform_mat[7]
                                   + g_ugm_hlr_xform_mat[10]);
        float z = static_cast<float>(a2[0] * g_ugm_hlr_xform_mat[2]
                                   + a2[1] * g_ugm_hlr_xform_mat[5]
                                   + a2[2] * g_ugm_hlr_xform_mat[8]
                                   + g_ugm_hlr_xform_mat[11]);
        float x = static_cast<float>(a2[0] * g_ugm_hlr_xform_mat[0]
                                   + a2[1] * g_ugm_hlr_xform_mat[3]
                                   + a2[2] * g_ugm_hlr_xform_mat[6]
                                   + g_ugm_hlr_xform_mat[9]);
        char* base = reinterpret_cast<char*>(g_ugm_hlr_vloc_arr);
        long long off = 32LL * a1;

        *(float*)(off + base + 4) = y;
        *(float*)(off + base) = x;
        *(float*)(off + base + 8) = z;
        if (g_ugm_hlr_vloc_norm != 0)
        {
            float nz = -z;
            x = x / nz;
            y = y / nz;
        }
        if (x > g_ugm_hlr_max_x)
            g_ugm_hlr_max_x = x;
        if (g_ugm_hlr_min_x > x)
            g_ugm_hlr_min_x = x;
        if (y > g_ugm_hlr_max_y)
            g_ugm_hlr_max_y = y;
        if (g_ugm_hlr_min_y > y)
            g_ugm_hlr_min_y = y;
        *(void**)(off + base + 16) = 0;
        *(WORD*)(off + base + 24) = 1;
    }
}
