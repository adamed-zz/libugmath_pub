











typedef unsigned long long u64;


typedef void (*ugm_hlr_diag_fn)(int, int, const char*);


typedef void (__cdecl *ugm_hlr_line_callback_t)(
    const double* const, const double* const, int, void*);




extern "C" float  g_ugm_hlr_E0048 = 0.0f;
extern "C" int    g_ugm_hlr_E004C = 0;
extern "C" float  g_ugm_hlr_E0050 = 0.0f;
extern "C" float  g_ugm_hlr_E0054 = 0.0f;
extern "C" float  g_ugm_hlr_E0058 = 0.0f;
extern "C" float  g_ugm_hlr_E005C = 0.0f;
extern "C" float  g_ugm_hlr_E0060 = 0.0f;
extern "C" float  g_ugm_hlr_E0064 = 0.0f;
extern "C" float  g_ugm_hlr_E0068 = 0.0f;
extern "C" float  g_ugm_hlr_E006C = 0.0f;
extern "C" float  g_ugm_hlr_E0070 = 0.0f;
extern "C" float  g_ugm_hlr_E0074 = 0.0f;
extern "C" float  g_ugm_hlr_E0078 = 0.0f;
extern "C" float  g_ugm_hlr_E007C = 0.0f;




extern "C" int    g_ugm_hlr_E0560 = 0;
extern "C" int    g_ugm_hlr_bucket_count = 0;
extern "C" u64    g_ugm_hlr_vloc_arr = 0;
extern "C" u64    g_ugm_hlr_vnrm_arr = 0;
extern "C" u64    g_ugm_hlr_bucket_ptr = 0;
extern "C" int    g_ugm_hlr_E0580 = 0;
extern "C" int    g_ugm_hlr_E0584 = 0;







extern "C" double g_ugm_hlr_eye[3] = {0.0};
extern "C" double g_ugm_hlr_col[4][3] = {{0.0}};
extern "C" double g_ugm_hlr_E05A0 = 0.0;
extern "C" double g_ugm_hlr_E05A8 = 0.0;
extern "C" double g_ugm_hlr_E05B0 = 0.0;
extern "C" double g_ugm_hlr_E05B8 = 0.0;
extern "C" double g_ugm_hlr_E05C0 = 0.0;
extern "C" double g_ugm_hlr_E05C8 = 0.0;
extern "C" double g_ugm_hlr_E05D0 = 0.0;
extern "C" double g_ugm_hlr_E05D8 = 0.0;
extern "C" double g_ugm_hlr_E05E0 = 0.0;
extern "C" double g_ugm_hlr_E05E8 = 0.0;
extern "C" double g_ugm_hlr_E05F0 = 0.0;
extern "C" double g_ugm_hlr_E05F8 = 0.0;

extern "C" double g_ugm_hlr_mat[4][3] = {{0.0}};
extern "C" double g_ugm_hlr_xform_mat[12] = {0};
extern "C" double g_ugm_hlr_E0600 = 0.0;
extern "C" double g_ugm_hlr_E0608 = 0.0;
extern "C" double g_ugm_hlr_E0610 = 0.0;
extern "C" double g_ugm_hlr_E0618 = 0.0;
extern "C" double g_ugm_hlr_E0620 = 0.0;
extern "C" double g_ugm_hlr_E0628 = 0.0;
extern "C" double g_ugm_hlr_E0630 = 0.0;
extern "C" double g_ugm_hlr_E0638 = 0.0;
extern "C" double g_ugm_hlr_E0640 = 0.0;
extern "C" double g_ugm_hlr_E0648 = 0.0;
extern "C" double g_ugm_hlr_E0650 = 0.0;
extern "C" double g_ugm_hlr_E0658 = 0.0;

extern "C" double g_ugm_hlr_axis[3][3] = {{0.0}};
extern "C" double g_ugm_hlr_E06A8 = 0.0;
extern "C" double g_ugm_hlr_E06B0 = 0.0;
extern "C" int    g_ugm_hlr_E06B8 = 0;
extern "C" double g_ugm_hlr_E06C0 = 0.0;
extern "C" double g_ugm_hlr_E06C8 = 0.0;
extern "C" double g_ugm_hlr_E06D0 = 0.0;
extern "C" double g_ugm_hlr_E06D8 = 0.0;




extern "C" u64    g_ugm_hlr_E0778 = 0;
extern "C" u64    g_ugm_hlr_E0780 = 0;
extern "C" u64    g_ugm_hlr_E0788 = 0;
extern "C" u64    g_ugm_hlr_E0790 = 0;
extern "C" u64    g_ugm_hlr_scratch_ptr = 0;
extern "C" int    g_ugm_hlr_scratch_len = 0;
extern "C" int    g_ugm_hlr_vloc_norm = 0;
extern "C" double g_ugm_hlr_E07C8 = 0.0;




extern "C" u64    g_ugm_hlr_E0848 = 0;
extern "C" u64    g_ugm_hlr_E0850 = 0;
extern "C" u64    g_ugm_hlr_geom_desc = 0;
extern "C" u64    g_ugm_hlr_geom_list = 0;




extern "C" float  g_ugm_hlr_min_x = 0.0f;
extern "C" float  g_ugm_hlr_min_y = 0.0f;
extern "C" float  g_ugm_hlr_max_x = 0.0f;
extern "C" float  g_ugm_hlr_max_y = 0.0f;
extern "C" double g_ugm_hlr_E0880 = 0.0;
extern "C" double g_ugm_hlr_E0888 = 0.0;
extern "C" double g_ugm_hlr_E0890 = 0.0;
extern "C" double g_ugm_hlr_E0898 = 0.0;




extern "C" double g_ugm_hlr_E08A0 = 0.0;
extern "C" int    g_ugm_hlr_E08A8 = 0;
extern "C" int    g_ugm_hlr_E08B0 = 0;
extern "C" int    g_ugm_hlr_E08B4 = 0;
extern "C" int    g_ugm_hlr_E08B8 = 0;
extern "C" int    g_ugm_hlr_E08BC = 0;
extern "C" int    g_ugm_hlr_E08C0 = 0;
extern "C" int    g_ugm_hlr_E08C4 = 0;
extern "C" int    g_ugm_hlr_E08C8 = 0;




int g_ugm_hlr_debug_level = 0;





ugm_hlr_line_callback_t g_ugm_hlr_line_cb;

extern "C" ugm_hlr_diag_fn g_ugm_hlr_diag_cb = nullptr;




extern "C" const char g_ugm_hlr_msg_BAD62[] = "";
