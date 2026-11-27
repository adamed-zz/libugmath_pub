

















#include <math.h>

namespace {
const double kTiny = 3.834e-20;
const double kBigScale = 1.304e19;
}

extern "C" double sub_18005FC00(int n, const double* v) {
    double big_acc = 0.0;
    double direct = 0.0;
    double tiny_acc = 0.0;
    double big_scale = 0.0;
    double tiny_scale = 0.0;
    const double big_thresh = kBigScale / (double)n;

    __int64 i = 0;
    const __int64 nn = n;
    if (nn >= 4) {
        const __int64 blocks = ((unsigned __int64)(nn - 4) >> 2) + 1;
        i = 4 * blocks;
        const double* p = v;
        __int64 k = blocks;
        do {
            double y;

            y = fabs(p[0]);
            if (!(y > kTiny)) {
                if (!(y > tiny_scale)) {
                    if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
                } else {
                    tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
                    tiny_scale = y;
                    tiny_acc = tiny_acc + 1.0;
                }
            } else if (!(big_thresh > y)) {
                if (!(y > big_scale)) {
                    big_acc = big_acc + y / big_scale * (y / big_scale);
                } else {
                    double t = big_acc * (big_scale / y) * (big_scale / y);
                    big_scale = y;
                    big_acc = t + 1.0;
                }
            } else {
                direct = direct + y * y;
            }

            y = fabs(p[1]);
            if (!(y > kTiny)) {
                if (!(y > tiny_scale)) {
                    if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
                } else {
                    tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
                    tiny_scale = y;
                    tiny_acc = tiny_acc + 1.0;
                }
            } else if (!(big_thresh > y)) {
                if (!(y > big_scale)) {
                    big_acc = big_acc + y / big_scale * (y / big_scale);
                } else {
                    double t = big_acc * (big_scale / y) * (big_scale / y);
                    big_scale = y;
                    big_acc = t + 1.0;
                }
            } else {
                direct = direct + y * y;
            }

            y = fabs(p[2]);
            if (!(y > kTiny)) {
                if (!(y > tiny_scale)) {
                    if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
                } else {
                    tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
                    tiny_scale = y;
                    tiny_acc = tiny_acc + 1.0;
                }
            } else if (!(big_thresh > y)) {
                if (!(y > big_scale)) {
                    big_acc = big_acc + y / big_scale * (y / big_scale);
                } else {
                    double t = big_acc * (big_scale / y) * (big_scale / y);
                    big_scale = y;
                    big_acc = t + 1.0;
                }
            } else {
                direct = direct + y * y;
            }

            y = fabs(p[3]);
            if (!(y > kTiny)) {
                if (!(y > tiny_scale)) {
                    if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
                } else {
                    tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
                    tiny_scale = y;
                    tiny_acc = tiny_acc + 1.0;
                }
            } else if (!(big_thresh > y)) {
                if (!(y > big_scale)) {
                    big_acc = big_acc + y / big_scale * (y / big_scale);
                } else {
                    double t = big_acc * (big_scale / y) * (big_scale / y);
                    big_scale = y;
                    big_acc = t + 1.0;
                }
            } else {
                direct = direct + y * y;
            }
            p += 4;
        } while (--k);
    }
    for (; i < nn; ++i) {
        double y = fabs(v[i]);
        if (!(y > kTiny)) {
            if (!(y > tiny_scale)) {
                if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
            } else {
                tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
                tiny_scale = y;
                tiny_acc = tiny_acc + 1.0;
            }
        } else if (!(big_thresh > y)) {
            if (!(y > big_scale)) {
                big_acc = big_acc + y / big_scale * (y / big_scale);
            } else {
                double t = big_acc * (big_scale / y) * (big_scale / y);
                big_scale = y;
                big_acc = t + 1.0;
            }
        } else {
            direct = direct + y * y;
        }
    }

    if (!(big_acc == 0.0)) {
        double q = direct / big_scale / big_scale + big_acc;
        return sqrt(q) * big_scale;
    } else if (!(direct == 0.0)) {
        double t = tiny_scale * tiny_acc;
        if (!(direct >= tiny_scale)) {
            direct = direct / tiny_scale + t;
        } else {
            tiny_scale = tiny_scale / direct * t + 1.0;
        }
        double r = tiny_scale * direct;
        return sqrt(r);
    } else {
        return sqrt(tiny_acc) * tiny_scale;
    }
}
