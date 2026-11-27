




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" __int64 sub_180087AF0(void* a1, void* a2, int a3);

extern "C" void* sub_180081F40(double* out, const double* p, const double* q)
{
    double px = p[0], py = p[1], pz = p[2];
    double n2 = pz * pz + (px * px + py * py);
    if (n2 > 0.0)
    {
        double s = sqrt(n2);
        px = px / s;
        py = py / s;
        pz = pz / s;
    }
    double qx = q[0], qy = q[1], qz = q[2];
    double m2 = qz * qz + (qx * qx + qy * qy);
    if (m2 > 0.0)
    {
        double s = sqrt(m2);
        qx = qx / s;
        qy = qy / s;
        qz = qz / s;
    }
    double dot = pz * qz + (px * qx + py * qy);
    if (!(dot < -0.999999999999))
    {
        double cx = py * qz - pz * qy;
        double cy = qx * pz - px * qz;
        double cz = px * qy - qx * py;
        double two = (dot + 1.0) + (dot + 1.0);
        double s = sqrt(two);
        double inv = 1.0 / s;
        out[0] = cx * inv;
        out[1] = cy * inv;
        out[2] = cz * inv;
        out[3] = s * 0.5;
        return out;
    }
    double v18 = _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(-1.0), _mm_set_sd(dot)));
    double v23 = (v18 + 1.0) * 0.5;
    double v24 = sqrt(v23);
    double oneMinus = 1.0 - v23;
    double v25x = sqrt(oneMinus);
    unsigned char S[0x260];
    double arr[6];
    arr[0] = px; arr[1] = qx;
    arr[2] = py; arr[3] = qy;
    arr[4] = pz; arr[5] = qz;
    *(long long*)(S + 0x80) = 0;
    *(unsigned short*)(S + 0x88) = 0;
    S[0x8A] = 0;
    *(int*)(S + 0x8C) = 0;
    *(long long*)(S + 0x98) = -1;
    *(long long*)(S + 0xA0) = -1;
    *(long long*)(S + 0xA8) = 0;
    *(unsigned short*)(S + 0x170) = 0;
    sub_180087AF0(S, arr, 16);
    out[0] = *(double*)(S + 0x50) * v25x;
    out[1] = *(double*)(S + 0x58) * v25x;
    out[2] = *(double*)(S + 0x60) * v25x;
    out[3] = v24;
    return out;
}
