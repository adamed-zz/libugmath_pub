

#pragma once

#include <windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cmath>


#define B18_RAW_PATH L"C:/Users/codexvm/Desktop/ws/raw/nx2412/NXBin/libugmath.dll"
#define B18_DEP_DIR  L"C:/Program Files/Siemens/NX2412/NXBin"



#define B18_RVA_ACOM_COUNT   0xE1058u
#define B18_RVA_ACOM_ARR     0xE105Cu
#define B18_RVA_ACOM_CB      0xE1AA0u
#define B18_RVA_INGRIP       0xE1A74u
#define B18_RVA_CUVAL        0xE1A50u
#define B18_RVA_B120         0xE0F20u
#define B18_RVA_ACOM_SINGLETON 0xE1B40u

inline HMODULE b18_load_raw()
{
    AddDllDirectory(B18_DEP_DIR);
    return LoadLibraryExW(B18_RAW_PATH, nullptr,
                          LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR |
                          LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
}

inline unsigned char *b18_base(HMODULE h) { return reinterpret_cast<unsigned char *>(h); }


struct B18Rng
{
    uint64_t s;
    explicit B18Rng(uint64_t seed = 0x9E3779B97F4A7C15ull) : s(seed ? seed : 1) {}
    uint64_t next()
    {
        s ^= s >> 12;
        s ^= s << 25;
        s ^= s >> 27;
        return s * 0x2545F4914F6CDD1Dull;
    }

    double unit() { return static_cast<double>(next() >> 11) * (1.0 / 9007199254740992.0); }

    double sym(double amp) { return (unit() * 2.0 - 1.0) * amp; }
};

inline uint64_t b18_bits(double d)
{
    uint64_t u;
    memcpy(&u, &d, 8);
    return u;
}
inline double b18_from_bits(uint64_t u)
{
    double d;
    memcpy(&d, &u, 8);
    return d;
}
inline uint32_t b18_u32(uint64_t u) { return static_cast<uint32_t>(u); }



inline double b18_special(int k)
{
    switch (k & 7)
    {
    case 0: return 0.0;
    case 1: return -0.0;
    case 2: return b18_from_bits(0x7FF8000000000001ull);
    case 3: return b18_from_bits(0x7FF0000000000000ull);
    case 4: return b18_from_bits(0xFFF0000000000000ull);
    case 5: return b18_from_bits(0x0000000000000001ull);
    case 6: return b18_from_bits(0x7FEFFFFFFFFFFFFFull);
    default: return b18_from_bits(0xFFEFFFFFFFFFFFFFull);
    }
}




struct B18StubState
{
    alignas(16) double mtx[9];
    alignas(16) double pt[3];
    double tol;
    int n8;
    int n20;
    int n140;
    int n158;
    int ntrap;
    double rec[3];
    int rec_valid;
};

extern B18StubState g_b18_stub;
void *b18_stub_object();
void b18_stub_reset();
void b18_install_raw_stub(HMODULE h);


extern int g_b18_cb_calls;
extern "C" void b18_cb_stub();


struct B18JsonWriter
{
    FILE *f;
    int first;

    bool open(const char *path) { f = fopen(path, "wb"); first = 1; return f != nullptr; }
    void puts_raw(const char *s) { fputs(s, f); }
    void record(const unsigned char *p, int n)
    {
        static const char *hex = "0123456789abcdef";
        fputs(first ? "\"" : ",\"", f);
        first = 0;
        for (int i = 0; i < n; ++i)
        {
            char b[3] = {hex[p[i] >> 4], hex[p[i] & 15], 0};
            fputs(b, f);
        }
        fputs("\"", f);
    }
    void close() { fclose(f); f = nullptr; }
};




inline int b18_map_record_size() { return 128; }
inline int b18_glob_record_size() { return 2209; }


uint64_t b18_file_fnv64(const char *path);


const char *b18_env_string();


struct B18GlobPtrs
{
    int *count;
    unsigned int *arr;
    void **cb;
    unsigned char *ingrip;
    int *cuval;
    unsigned char *b120;
};

B18GlobPtrs b18_raw_globals(HMODULE h);





inline void b18_store_u32(unsigned char *p, uint32_t v) { memcpy(p, &v, 4); }
inline void b18_store_i32(unsigned char *p, int32_t v) { memcpy(p, &v, 4); }
inline uint32_t b18_load_u32(const unsigned char *p) { uint32_t v; memcpy(&v, p, 4); return v; }


#define B18_TOOLSET "MSVC " B18_STR(MSC_FULL_VER)
#define B18_STR2(x) #x
#define B18_STR(x) B18_STR2(x)
