















#include <emmintrin.h>

typedef unsigned long long u64;
typedef unsigned short u16;


__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void  SM_free(void* p);
__declspec(dllimport) int STR_snprintf(char* buf, size_t n, const char* fmt, ...);



extern "C" float  g_ugm_hlr_E0048;
extern "C" int    g_ugm_hlr_E0560;
extern "C" int    g_ugm_hlr_bucket_count;
extern "C" u64    g_ugm_hlr_vloc_arr;
extern "C" u64    g_ugm_hlr_vnrm_arr;
extern "C" u64    g_ugm_hlr_bucket_ptr;
extern "C" int    g_ugm_hlr_E0580;
extern "C" int    g_ugm_hlr_E0584;
extern "C" double g_ugm_hlr_E0600;
extern "C" double g_ugm_hlr_E0608;
extern "C" double g_ugm_hlr_E0610;
extern "C" double g_ugm_hlr_E0618;
extern "C" double g_ugm_hlr_E0620;
extern "C" double g_ugm_hlr_E0628;
extern "C" double g_ugm_hlr_E0630;
extern "C" double g_ugm_hlr_E0638;
extern "C" double g_ugm_hlr_E0640;
extern "C" int    g_ugm_hlr_E06B8;
extern "C" double g_ugm_hlr_E06C0;
extern "C" double g_ugm_hlr_E06C8;
extern "C" double g_ugm_hlr_E06D0;
extern "C" double g_ugm_hlr_E06D8;
extern "C" int    g_ugm_hlr_vloc_norm;
extern "C" u64    g_ugm_hlr_geom_desc;
extern "C" void (*g_ugm_hlr_diag_cb)(int, int, const char*);


extern "C" void sub_18004A020(u64 a, u64 b, u64 c, u64 d, bool e);
extern "C" void sub_180049A30(const double* t, int n, u64 bucket);

void __cdecl HLR_FACET_add_facet(const double* const a1, int n, int* const a3,
                                 const int* const a4, const bool* const a5)
{
  char buf[20];
  double tvec[3];
  const bool* pa5 = a5;
  if (n > 0)
  {
    const char* desc = (const char*)g_ugm_hlr_geom_desc;
    int i = 0;
    do
    {
      int idx = a3[i];
      if (idx < 0 || idx >= *(const int*)(desc + 40)
          || *(const u16*)(g_ugm_hlr_vloc_arr + 32ull * idx + 24) != 1)
      {
        STR_snprintf(buf, 0x14, "%d", idx);
        g_ugm_hlr_diag_cb(2, 4, buf);
        return;
      }
      int idx2 = a4[i];
      if (idx2 < 0 || idx2 >= *(const int*)(desc + 44)
          || *(const u16*)(g_ugm_hlr_vnrm_arr + 16ull * idx2 + 12) != 1)
      {
        STR_snprintf(buf, 0x14, "%d", idx2);
        g_ugm_hlr_diag_cb(2, 5, buf);
        return;
      }
      ++i;
    } while (i < n);
  }

  {
    double x = a1[0];
    double y = a1[1];
    double z = a1[2];
    tvec[0] = x * g_ugm_hlr_E0600 + y * g_ugm_hlr_E0618 + z * g_ugm_hlr_E0630;
    tvec[1] = x * g_ugm_hlr_E0608 + y * g_ugm_hlr_E0620 + z * g_ugm_hlr_E0638;
    tvec[2] = x * g_ugm_hlr_E0610 + y * g_ugm_hlr_E0628 + z * g_ugm_hlr_E0640;
  }

  double dot;
  if (g_ugm_hlr_vloc_norm)
  {
    int vi = a3[0];
    dot = (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi + 4) * tvec[1]
        + (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi) * tvec[0]
        + (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi + 8) * tvec[2];
  }
  else
  {
    dot = -tvec[2];
  }

  int flag = 1;
  if (dot >= 0.0)
  {
    if (!g_ugm_hlr_E0580)
      return;
    float thr = g_ugm_hlr_E0048;
    for (int i = 0; i < n; ++i)
    {
      int vi = a4[i];
      double px = (double)*(const float*)(g_ugm_hlr_vnrm_arr + 16ull * vi);
      double py = (double)*(const float*)(g_ugm_hlr_vnrm_arr + 16ull * vi + 4);
      double pz = (double)*(const float*)(g_ugm_hlr_vnrm_arr + 16ull * vi + 8);
      double qx = py * g_ugm_hlr_E0618 + px * g_ugm_hlr_E0600 + pz * g_ugm_hlr_E0630;
      double qy = py * g_ugm_hlr_E0620 + px * g_ugm_hlr_E0608 + pz * g_ugm_hlr_E0638;
      double qz = g_ugm_hlr_E0610 * px + g_ugm_hlr_E0628 * py + g_ugm_hlr_E0640 * pz;
      double e;
      if (g_ugm_hlr_vloc_norm)
      {
        int vi2 = a3[i];
        e = (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi2 + 4) * qy
          + (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi2) * qx
          + (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi2 + 8) * qz;
      }
      else
      {
        e = -qz;
      }
      if (e >= (double)thr)
        return;
    }
    flag = 0;
  }

  if (g_ugm_hlr_E0584)
  {
    const __m128 sign = _mm_set1_ps(-0.0f);
    __m128d minx = _mm_set_sd(1.0e19);
    __m128d maxx = _mm_set_sd(-1.0e19);
    __m128d miny = _mm_set_sd(1.0e19);
    __m128d maxy = _mm_set_sd(-1.0e19);
    if (n > 0)
    {
      const int* p3 = a3;
      int rem = n;
      do
      {
        int vi = *p3;
        double vv[2];
        vv[0] = (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi);
        vv[1] = (double)*(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi + 4);
        if (g_ugm_hlr_vloc_norm)
        {
          float fz = *(const float*)(g_ugm_hlr_vloc_arr + 32ull * vi + 8);
          __m128d q = _mm_div_pd(_mm_loadu_pd(vv),
                                 _mm_cvtps_pd(_mm_xor_ps(_mm_set1_ps(fz), sign)));
          _mm_storeu_pd(vv, q);
        }
        minx = _mm_min_sd(minx, _mm_load_sd(&vv[0]));
        maxx = _mm_max_sd(maxx, _mm_load_sd(&vv[0]));
        miny = _mm_min_sd(miny, _mm_load_sd(&vv[1]));
        maxy = _mm_max_sd(maxy, _mm_load_sd(&vv[1]));
        ++p3;
      } while (--rem);
    }
    if (_mm_cvtsd_f64(minx) > g_ugm_hlr_E06D0 || g_ugm_hlr_E06C0 > _mm_cvtsd_f64(maxx)
        || _mm_cvtsd_f64(miny) > g_ugm_hlr_E06D8 || g_ugm_hlr_E06C8 > _mm_cvtsd_f64(maxy))
    {
      ++g_ugm_hlr_E06B8;
      return;
    }
  }

  ++g_ugm_hlr_E0560;
  if (g_ugm_hlr_bucket_count < n)
  {
    g_ugm_hlr_bucket_count = n + (n >> 2);
    SM_free((void*)g_ugm_hlr_bucket_ptr);
    u64 bytes = 32ull * g_ugm_hlr_bucket_count;
    void* p = SM_alloc(bytes);
    if (!p && bytes)
      g_ugm_hlr_diag_cb(2, 3, "");
    g_ugm_hlr_bucket_ptr = (u64)p;
  }
  if (n > 0)
  {
    const int* p3 = a3;
    u64 out = 0;
    int k = 0;
    do
    {
      int k1 = k + 1;
      int m = k1 % n;
      int idxB = a3[m];
      if (idxB >= 0)
      {
        int ia = *p3;
        if (ia >= idxB)
          sub_18004A020(g_ugm_hlr_vloc_arr + 32ull * idxB,
                        g_ugm_hlr_vnrm_arr + 16ull * a4[m],
                        g_ugm_hlr_vloc_arr + 32ull * ia,
                        g_ugm_hlr_vnrm_arr + 16ull * a4[k],
                        *pa5);
        else
          sub_18004A020(g_ugm_hlr_vloc_arr + 32ull * ia,
                        g_ugm_hlr_vnrm_arr + 16ull * a4[k],
                        g_ugm_hlr_vloc_arr + 32ull * idxB,
                        g_ugm_hlr_vnrm_arr + 16ull * a4[m],
                        *pa5);
      }
      else
      {
        a3[m] = -idxB;
      }
      int vi = *p3;
      ++pa5;
      ++p3;
      k = k1;
      *(u64*)(g_ugm_hlr_bucket_ptr + out) = g_ugm_hlr_vloc_arr + 32ull * vi;
      out += 8;
    } while (k < n);
  }
  if (flag)
    sub_180049A30(tvec, n, g_ugm_hlr_bucket_ptr);
}
