











typedef unsigned long long QWORD;
typedef unsigned short WORD;




extern "C" QWORD g_ugm_hlr_geom_desc;

extern "C" QWORD g_ugm_hlr_vnrm_arr;

extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);


__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);


struct UgmHlrVnrm
{
    float x;
    float y;
    float z;
    WORD  flag;
    WORD  pad;
};

void HLR_FACET_add_vnrm(int a1, const double* const a2)
{
    if (a1 < 0 || a1 >= *reinterpret_cast<const int*>(g_ugm_hlr_geom_desc + 0x2C))
    {
        char buf[20];
        STR_snprintf(buf, 0x14, "%d", a1);
        g_ugm_hlr_diag_cb(1, 2, buf);
    }
    else
    {
        UgmHlrVnrm* arr = reinterpret_cast<UgmHlrVnrm*>(g_ugm_hlr_vnrm_arr);
        arr[a1].x = static_cast<float>(a2[0]);
        arr[a1].y = static_cast<float>(a2[1]);
        arr[a1].z = static_cast<float>(a2[2]);
        arr[a1].flag = 1;
    }
}
