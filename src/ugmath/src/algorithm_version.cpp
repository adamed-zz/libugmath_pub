#include "ugmath/algorithm_version.h"












namespace UGS {
namespace Math {




int g_algorithmVersion = 0;

void __cdecl SetAlgorithmVersion(int version)
{
    g_algorithmVersion = version;
}

AlgorithmVersion __cdecl GetAlgorithmVersion()
{
    return static_cast<AlgorithmVersion>(g_algorithmVersion);
}

}
}
