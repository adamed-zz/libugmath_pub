








#include <intrin.h>

typedef unsigned long long u64;
typedef unsigned __int64 QWORD;





#define UGM_HLR_MADD3(OUT, M0, M1, M2, I0, I1, I2)                          \
  do {                                                                      \
    __m128d a = _mm_mul_sd(_mm_load_sd(&(M0)), _mm_load_sd(&p[I0]));        \
    a = _mm_add_sd(a, _mm_mul_sd(_mm_load_sd(&(M1)), _mm_load_sd(&p[I1]))); \
    a = _mm_add_sd(a, _mm_mul_sd(_mm_load_sd(&(M2)), _mm_load_sd(&p[I2]))); \
    _mm_store_sd(&(OUT), a);                                                \
  } while (0)

#define UGM_HLR_MADD3T(OUT, M0, M1, M2, I0, I1, I2, T)                      \
  do {                                                                      \
    __m128d a = _mm_mul_sd(_mm_load_sd(&(M0)), _mm_load_sd(&p[I0]));        \
    a = _mm_add_sd(a, _mm_mul_sd(_mm_load_sd(&(M1)), _mm_load_sd(&p[I1]))); \
    a = _mm_add_sd(a, _mm_mul_sd(_mm_load_sd(&(M2)), _mm_load_sd(&p[I2]))); \
    a = _mm_add_sd(a, _mm_load_sd(&(T)));                                   \
    _mm_store_sd(&(OUT), a);                                                \
  } while (0)


__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void  SM_free(void* p);


extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);
extern "C" const char g_ugm_hlr_msg_BAD62[];


struct ugm_hlr_group
{
  void*  facets;
  void*  verts;
  ugm_hlr_group* prev;
  void*  unk18;
  void*  obj;
  int    n1;
  int    n2;
  void*  unk30;
};


extern "C" u64 g_ugm_hlr_geom_desc;
extern "C" u64 g_ugm_hlr_vloc_arr;
extern "C" u64 g_ugm_hlr_vnrm_arr;


extern "C" double g_ugm_hlr_E05A0;
extern "C" double g_ugm_hlr_E05A8;
extern "C" double g_ugm_hlr_E05B0;
extern "C" double g_ugm_hlr_E05B8;
extern "C" double g_ugm_hlr_E05C0;
extern "C" double g_ugm_hlr_E05C8;
extern "C" double g_ugm_hlr_E05D0;
extern "C" double g_ugm_hlr_E05D8;
extern "C" double g_ugm_hlr_E05E0;
extern "C" double g_ugm_hlr_E05E8;
extern "C" double g_ugm_hlr_E05F0;
extern "C" double g_ugm_hlr_E05F8;


extern "C" double g_ugm_hlr_E0600;
extern "C" double g_ugm_hlr_E0608;
extern "C" double g_ugm_hlr_E0610;
extern "C" double g_ugm_hlr_E0618;
extern "C" double g_ugm_hlr_E0620;
extern "C" double g_ugm_hlr_E0628;
extern "C" double g_ugm_hlr_E0630;
extern "C" double g_ugm_hlr_E0638;
extern "C" double g_ugm_hlr_E0640;
extern "C" double g_ugm_hlr_E0648;
extern "C" double g_ugm_hlr_E0650;
extern "C" double g_ugm_hlr_E0658;

void __cdecl HLR_FACET_group(int a1, int a2, const double (* const a3)[3], void* a4)
{
  if ( g_ugm_hlr_geom_desc && *(int *)(g_ugm_hlr_geom_desc + 44) > 0 )
  {
    SM_free(*(void **)(g_ugm_hlr_geom_desc + 8));
    *(int *)(g_ugm_hlr_geom_desc + 44) = 0;
  }
  ugm_hlr_group* v8 = (ugm_hlr_group *)SM_alloc(0x38u);
  if ( !v8 )
    g_ugm_hlr_diag_cb(2, 3, g_ugm_hlr_msg_BAD62);
  char* v9 = (char *)g_ugm_hlr_geom_desc;
  v8->obj = a4;
  v8->prev = (ugm_hlr_group *)v9;
  __int64 sz1 = (__int64)32 * a1;
  g_ugm_hlr_geom_desc = (u64)v8;
  v8->n1 = a1;
  v8->n2 = a2;
  char* v10 = (char *)SM_alloc(sz1);
  if ( !v10 && sz1 )
    g_ugm_hlr_diag_cb(2, 3, g_ugm_hlr_msg_BAD62);
  v8->facets = v10;
  g_ugm_hlr_vloc_arr = (u64)v10;
  char* v11 = (char *)SM_alloc((__int64)16 * a2);
  if ( !v11 && (__int64)16 * a2 )
    g_ugm_hlr_diag_cb(2, 3, g_ugm_hlr_msg_BAD62);
  char* v12 = (char *)v8->facets;
  v8->verts = v11;
  g_ugm_hlr_vnrm_arr = (u64)v11;
  if ( a1 > 0 )
  {
    unsigned short* q = (unsigned short *)(v12 + 24);
    int n = a1;
    do
    {
      --n;
      *q = 0;
      q += 16;
    }
    while ( n > 0 );
    v11 = (char *)v8->verts;
  }
  if ( a2 > 0 )
    *(unsigned short *)(v11 + 12) = 0;



  const double* p = &(*a3)[0];
  UGM_HLR_MADD3(g_ugm_hlr_E0600, g_ugm_hlr_E05A0, g_ugm_hlr_E05B8, g_ugm_hlr_E05D0, 0, 1, 2);
  UGM_HLR_MADD3(g_ugm_hlr_E0608, g_ugm_hlr_E05A8, g_ugm_hlr_E05C0, g_ugm_hlr_E05D8, 0, 1, 2);
  UGM_HLR_MADD3(g_ugm_hlr_E0610, g_ugm_hlr_E05B0, g_ugm_hlr_E05C8, g_ugm_hlr_E05E0, 0, 1, 2);
  UGM_HLR_MADD3(g_ugm_hlr_E0618, g_ugm_hlr_E05A0, g_ugm_hlr_E05B8, g_ugm_hlr_E05D0, 3, 4, 5);
  UGM_HLR_MADD3(g_ugm_hlr_E0620, g_ugm_hlr_E05A8, g_ugm_hlr_E05C0, g_ugm_hlr_E05D8, 3, 4, 5);
  UGM_HLR_MADD3(g_ugm_hlr_E0628, g_ugm_hlr_E05B0, g_ugm_hlr_E05C8, g_ugm_hlr_E05E0, 3, 4, 5);
  UGM_HLR_MADD3(g_ugm_hlr_E0630, g_ugm_hlr_E05A0, g_ugm_hlr_E05B8, g_ugm_hlr_E05D0, 6, 7, 8);
  UGM_HLR_MADD3(g_ugm_hlr_E0638, g_ugm_hlr_E05A8, g_ugm_hlr_E05C0, g_ugm_hlr_E05D8, 6, 7, 8);
  UGM_HLR_MADD3(g_ugm_hlr_E0640, g_ugm_hlr_E05B0, g_ugm_hlr_E05C8, g_ugm_hlr_E05E0, 6, 7, 8);
  UGM_HLR_MADD3T(g_ugm_hlr_E0648, g_ugm_hlr_E05B8, g_ugm_hlr_E05A0, g_ugm_hlr_E05D0, 10, 9, 11, g_ugm_hlr_E05E8);
  UGM_HLR_MADD3T(g_ugm_hlr_E0650, g_ugm_hlr_E05C0, g_ugm_hlr_E05A8, g_ugm_hlr_E05D8, 10, 9, 11, g_ugm_hlr_E05F0);
  UGM_HLR_MADD3T(g_ugm_hlr_E0658, g_ugm_hlr_E05C8, g_ugm_hlr_E05B0, g_ugm_hlr_E05E0, 10, 9, 11, g_ugm_hlr_E05F8);
}
