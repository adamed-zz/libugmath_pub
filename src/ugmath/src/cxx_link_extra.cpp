


























#include <cstdlib>
#include <bit>





namespace UGS {
namespace Math {


class Graph
{
    static double m_distanceTolerance;
};

double Graph::m_distanceTolerance = std::bit_cast<double>(0x3E45798EE2308C3Aull);



double m_distanceTolerance_public = std::bit_cast<double>(0x3E45798EE2308C3Aull);

}
}

#pragma comment(linker, "/alternatename:?m_distanceTolerance@Graph@Math@UGS@@2NA=?m_distanceTolerance_public@Math@UGS@@3NA")

namespace UGS {



class StlPoint3Less
{
    static double m_disTol;
};

double StlPoint3Less::m_disTol = std::bit_cast<double>(0x3EB0C6F7A0B5ED8Dull);

}



struct __declspec(align(16)) B18AcomBlock
{
    unsigned char raw[4096];
};
B18AcomBlock g_acom;


struct __declspec(align(16)) B18B120Block
{
    unsigned char raw[1024];
};
B18B120Block g_b120;





extern "C"
{
    __declspec(align(16)) unsigned char b05_glob[0x138];
}

#pragma comment(linker, "/alternatename:?b05_glob@@3PAEA=b05_glob")


unsigned char g_ingrip = 0;


int g_cuval = 0;


int g_b8_mode0 = 0;


double g_b8_zero = 0.0;


extern const double g_zero = 0.0;


extern const int g_mode = 0;


void (*g_cb)() = nullptr;


extern "C" unsigned int dword_1800E1B34 = 0;


extern const double g_h0602_axis0 = 0.0;
extern const double g_h0602_axis1 = 0.0;
extern const double g_h0602_axis2 = -1.0;








#pragma comment(linker, "/alternatename:__imp_SM_alloc=__imp_?SM_alloc@@YAPEAX_K@Z")
#pragma comment(linker, "/alternatename:__imp_SM_free=__imp_?SM_free@@YAXPEAX@Z")
#pragma comment(linker, "/alternatename:__imp_b24_alloc=__imp_?allocate@CppMemory@Memory@UGS@@SAPEAX_K@Z")
#pragma comment(linker, "/alternatename:__imp_b24_free=__imp_?free@CppMemory@Memory@UGS@@SAXPEAX@Z")
#pragma comment(linker, "/alternatename:__imp_ERROR_raise=__imp_?ERROR_raise@@YAXPEBDHH0ZZ")



namespace b23dev
{
void* RawNew(unsigned long long n)
{
    return std::malloc(n);
}

void RawFree(void* p)
{
    std::free(p);
}
}




extern "C" void ERROR_internal_import(const char* file, int line, const char* msg, ...);
#pragma comment(linker, "/alternatename:ERROR_internal_import=?ERROR_internal@@YAXPEBDH0ZZ")

void ERROR_internal(const char* file, int line, const char* msg)
{
    ERROR_internal_import(file, line, msg);
}
