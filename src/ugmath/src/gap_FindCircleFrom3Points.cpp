
#include <cmath>
#include <emmintrin.h>























namespace UGS {
namespace Math {

bool NormalizeVector(const double* const v, int n, double* const out);

void FindCircleFrom3Points(const double* const pa, const double* const pb,
                           const double* const pc, bool& ok, double* const center,
                           double* const normal, double& radius);

void FindCircleFrom3Points(const double* const pa, const double* const pb,
                           const double* const pc, bool& ok, double* const center,
                           double* const normal, double& radius)
{
    ok = false;
    center[2] = 0.0;
    center[1] = 0.0;
    center[0] = 0.0;
    normal[1] = 0.0;
    normal[0] = 0.0;
    normal[2] = 1.0;
    radius = 1.0;

    const double v9 = pb[1] - pa[1];
    const double v10 = pb[0] - pa[0];
    const double v11 = pc[2] - pa[2];
    const double v12 = pc[2] - pb[2];
    const double v13 = pb[2] - pa[2];
    const double v14 = pc[0] - pb[0];
    const double v29 = v9 * v9 + v10 * v10 + v13 * v13;
    const double v15 = pc[1] - pa[1];
    const double v16 = pc[1] - pb[1];
    const double v28 = pc[0] - pa[0];
    const double v17 = v15 * v15 + v28 * v28 + v11 * v11;

    const double v18 = v11 * v9 - v15 * v13;
    normal[0] = v18;
    const double v19 = v13 * v28 - v11 * v10;
    normal[1] = v19;
    const double v20 = v15 * v10 - v9 * v28;
    normal[2] = v20;

    const double v21 = v19 * v19 + v18 * v18 + v20 * v20;
    if (std::fabs(v21) < 1.0e-12) {
        ok = true;
        return;
    }
    const double v22 = ((v9 * v16 + v10 * v14) + v13 * v12) * v17 / (v21 * -2.0);
    const double v23 = v22 * v10 + pa[0];
    const double v24 = v22 * v9 + pa[1];
    center[0] = v23;
    center[1] = v24;
    const double v25 = ((v15 * v16 + v28 * v14) + v11 * v12) * v29 / (v21 + v21);
    center[1] = v15 * v25 + v24;
    center[0] = v25 * v28 + v23;
    center[2] = (v22 * v13 + pa[2]) + v11 * v25;
    const double r2 = (v16 * v16 + v14 * v14 + v12 * v12) * (v29 * v17) / v21;
    double sr;
    if (r2 < 0.0) {
        sr = std::sqrt(r2);
    } else {
        sr = _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), _mm_set_sd(r2)));
    }
    radius = sr * 0.5;
    NormalizeVector(normal, 3, normal);
}

}
}
