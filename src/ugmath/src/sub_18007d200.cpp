








struct VecDesc {
    const double* data;
    long long count;
};

extern "C" __declspec(noinline) double sub_18007D200(const VecDesc* d, long long* out_index) {
    const long long n = d->count;
    if (n) {
        long long i = 1;
        long long idx = 0;
        double best = d->data[0];
        if (n > i) {
            for (; i < n; ++i) {
                if (d->data[i] > best) {
                    best = d->data[i];
                    idx = i;
                }
            }
        }
        *out_index = idx;
        return best;
    }
    *out_index = -1;
    return 0.0;
}
