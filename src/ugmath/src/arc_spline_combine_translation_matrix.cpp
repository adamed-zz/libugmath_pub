







namespace UGS {
namespace Math {
struct TransformMatrix
{
    double m[16];
};
}
}

void ARC_SPLINE_combine_translation_matrix(UGS::Math::TransformMatrix* a1,
                                           UGS::Math::TransformMatrix* a2,
                                           UGS::Math::TransformMatrix* a3)
{
    char* dst = (char*)a3;
    const char* src = (const char*)a1;
    for (int i = 0; i < 128; i += 64)
    {
        *(__int64*)(dst + i + 0) = *(const __int64*)(src + i + 0);
        *(__int64*)(dst + i + 8) = *(const __int64*)(src + i + 8);
        *(__int64*)(dst + i + 16) = *(const __int64*)(src + i + 16);
        *(__int64*)(dst + i + 24) = *(const __int64*)(src + i + 24);
        *(__int64*)(dst + i + 32) = *(const __int64*)(src + i + 32);
        *(__int64*)(dst + i + 40) = *(const __int64*)(src + i + 40);
        *(__int64*)(dst + i + 48) = *(const __int64*)(src + i + 48);
        *(__int64*)(dst + i + 56) = *(const __int64*)(src + i + 56);
    }
    a3->m[12] += a2->m[12];
    a3->m[13] += a2->m[13];
    a3->m[14] += a2->m[14];
}
