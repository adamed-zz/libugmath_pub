






#include <cstdlib>
#include <cstring>

extern "C" long long* sub_180079B50(long long* out, const long long* range) {
    const long long begin = range[0];
    const long long end = range[1];
    const long long n = (end - begin) >> 4;
    double* data = nullptr;
    if (n > 0) {
        data = static_cast<double*>(std::malloc(static_cast<size_t>(2 * n) * sizeof(double)));
        std::memcpy(data, reinterpret_cast<const void*>(begin),
                    static_cast<size_t>(n) * 16);
    }
    out[0] = reinterpret_cast<long long>(data);
    out[1] = 2;
    out[2] = n;
    return out;
}
