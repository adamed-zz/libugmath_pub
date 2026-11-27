








typedef unsigned long long u64;


__declspec(dllimport) void* SM_alloc(unsigned __int64 size);


extern "C" double cos(double);


extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);





extern "C" u64    g_ugm_hlr_geom_desc;
extern "C" u64    g_ugm_hlr_geom_list;
extern "C" int    g_ugm_hlr_bucket_count;
extern "C" u64    g_ugm_hlr_bucket_ptr;
extern "C" double g_ugm_hlr_E0888;
extern "C" double g_ugm_hlr_E0880;
extern "C" double g_ugm_hlr_E0890;
extern "C" float  g_ugm_hlr_min_y;
extern "C" float  g_ugm_hlr_min_x;
extern "C" float  g_ugm_hlr_max_y;
extern "C" float  g_ugm_hlr_max_x;
extern "C" double g_ugm_hlr_E0898;
extern "C" float  g_ugm_hlr_E0048;
extern "C" int    g_ugm_hlr_E0580;
extern "C" int    g_ugm_hlr_E08A8;
extern "C" int    g_ugm_hlr_E0560;
extern int        g_ugm_hlr_debug_level;
extern "C" double g_ugm_hlr_E08A0;
extern "C" int    g_ugm_hlr_E06B8;

void HLR_FACET_init()
{
  g_ugm_hlr_geom_desc = 0;
  g_ugm_hlr_geom_list = 0;
  g_ugm_hlr_bucket_count = 36;
  void* v0 = SM_alloc(0x120);
  if (!v0)
    g_ugm_hlr_diag_cb(2, 3, "");
  g_ugm_hlr_E0880 = 0.0;
  g_ugm_hlr_E0888 = -0.0;
  g_ugm_hlr_E0890 = 1.0;
  g_ugm_hlr_bucket_ptr = (u64)v0;
  g_ugm_hlr_min_y = 1.0e9f;
  g_ugm_hlr_min_x = 1.0e9f;
  g_ugm_hlr_max_y = -1.0e9f;
  g_ugm_hlr_max_x = -1.0e9f;
  g_ugm_hlr_E0898 = cos(0.026179938779914924);
  g_ugm_hlr_E0048 = (float)cos(1.6580627893946118);
  g_ugm_hlr_E0580 = 0;
  g_ugm_hlr_E08A8 = 0;
  g_ugm_hlr_E0560 = 0;
  g_ugm_hlr_debug_level = 0;
  g_ugm_hlr_E08A0 = 0.0;
  g_ugm_hlr_E06B8 = 0;
}
