
#include <cmath>













namespace UGS {
namespace Math {

enum MathIntersectType_e {
    kIsNone = 0,
    kIsDegenerate = 1,
    kIsOverlap = 2,
    kIsSingle = 3,
    kIsEndPoint = 4,
    kIsMulti = 5
};

namespace {



inline void Upd(double& m, double v) {

    const double x = (v < 0.0 || !(v == v)) ? -v : v;
    if (!(m > x)) m = x;
}

}

void Intersect2DSegments(const double* const a, const double* const b, double& t1,
                         double& t2, double* const out1, double* const out2,
                         MathIntersectType_e& type);

void Intersect2DSegments(const double* const a, const double* const b, double& t1,
                         double& t2, double* const out1, double* const out2,
                         MathIntersectType_e& type)
{
    const double a0 = a[0];
    const double a1 = a[1];
    const double a2 = a[2];
    const double a3 = a[3];
    const double b0 = b[0];
    const double b1 = b[1];
    const double b2 = b[2];
    const double b3 = b[3];

    t2 = 0.0;
    t1 = 0.0;
    out1[1] = 0.0;
    out1[0] = 0.0;
    out2[1] = 0.0;
    out2[0] = 0.0;
    type = kIsNone;



    double m = 1.0;
    Upd(m, a0);
    Upd(m, a2);
    Upd(m, b0);
    Upd(m, b2);
    Upd(m, a1);
    Upd(m, a3);
    Upd(m, b1);
    Upd(m, b3);

    const double tol = m * 5.0e-13;
    const double dxa = a0 - a2;
    const double dya = a3 - a1;
    const double c80 = a1 * a2 - a3 * a0;
    const double la = std::fabs(dxa) + std::fabs(dya);
    if (tol * 9.0 > la) {
        type = kIsDegenerate;
        return;
    }
    const double ea = la * tol;
    const double q0 = b1 * dxa + b0 * dya + c80;
    const double q1 = b3 * dxa + b2 * dya + c80;
    if (q0 > ea && q1 > ea) return;
    const double negea = -ea;
    if (negea > q0 && negea > q1) return;

    const double dyb = b3 - b1;
    const double dxb = b0 - b2;
    const double c87 = b1 * b2 - b3 * b0;
    const double lb = std::fabs(b0 - b2) + std::fabs(b3 - b1);
    const double absdyb = std::fabs(b3 - b1);
    if (tol * 9.0 > lb) {
        type = kIsDegenerate;
        return;
    }
    const double eb = lb * tol;
    const double p0 = a0 * dyb + a1 * dxb + c87;
    const double p1 = a3 * dxb + a2 * dyb + c87;
    if (p0 > eb && p1 > eb) return;
    const double negeb = -eb;
    if (negeb > p0 && negeb > p1) return;

    const double v79 = a2 - a0;
    const double v82 = b2 - b0;
    const double ab = std::fabs(a3 - a1);
    double v83 = ab;
    double v42 = std::fabs(a2 - a0);
    if (v42 > ab) v83 = v42;
    if (!(ab > v42)) v42 = ab;
    const double v43 = std::fabs(v82);
    const double v44 = v42 * 0.5 + v83;
    double v70 = absdyb;
    double v84 = v43;
    if (v43 > v70) v70 = v43;
    if (!(absdyb > v43)) v84 = absdyb;

    if (!(0.085 > std::fabs((dyb * v79 - v82 * dya) / ((v84 * 0.5 + v70) * v44)))) {

        unsigned c65 = 0;
        const double den = dxb * dya - dyb * dxa;
        t1 = -(a0 * dyb + c87 + a1 * dxb) / den;
        t2 = (dya * b0 + c80 + dxa * b1) / den;
        type = kIsSingle;
        if (eb > std::fabs(p0)) {
            t1 = 0.0;
            c65 = 1;
        }
        if (eb > std::fabs(p1)) {
            t1 = 1.0;
            ++c65;
        }
        if (ea > std::fabs(q0)) {
            t2 = 0.0;
            ++c65;
        }
        if (ea > std::fabs(q1)) {
            t2 = 1.0;
            ++c65;
        }
        if (c65 == 1) {
            type = kIsEndPoint;
        } else if (c65 > 1) {
            type = kIsMulti;
        }
        return;
    }


    const double v85 = (a1 - b1) * dya + (a0 - b0) * v79;
    const double v74 = a0 - b2;
    const double v88 = v74 * v79 + (a1 - b3) * dya;
    if (v85 > 0.0 && v88 > 0.0) return;
    const double v72 = b1 - a3;
    const double v69 = (b0 - a2) * v79 + v72 * dya;
    const double v81 = (b3 - a3) * dya + (b2 - a2) * v79;
    if (v69 > 0.0 && v81 > 0.0) return;
    const double v48 = (b1 - a1) * dyb + (b0 - a0) * v82;
    const double v49 = (b0 - a2) * v82 + v72 * dyb;
    if (v48 > 0.0 && v49 > 0.0) return;
    const double v50 = v74 * v82 + (a1 - b3) * dyb;
    const double v51 = (a3 - b3) * dyb + (a2 - b2) * v82;
    if (v50 > 0.0 && v51 > 0.0) return;

    if (v85 == 0.0 && v88 >= 0.0) {
        if (std::fabs(q0) > ea) return;
        t1 = 0.0;
        t2 = 0.0;
        type = kIsMulti;
        return;
    }
    if (v88 == 0.0 && v85 >= 0.0) {
        if (std::fabs(q1) > ea) return;
        t1 = 0.0;
        t2 = 1.0;
        type = kIsMulti;
        return;
    }
    if (v69 == 0.0 && v81 >= 0.0) {
        if (std::fabs(q0) > ea) return;
        t1 = 1.0;
        t2 = 0.0;
        type = kIsMulti;
        return;
    }
    if (v81 == 0.0 && v69 >= 0.0) {
        if (std::fabs(q1) > ea) return;
        t1 = 1.0;
        t2 = 1.0;
        type = kIsMulti;
        return;
    }
    if (v48 == 0.0 && v49 >= 0.0) {
        if (std::fabs(p0) > eb) return;
        t1 = 0.0;
        t2 = 0.0;
        type = kIsMulti;
        return;
    }
    if (v49 == 0.0 && v48 >= 0.0) {
        if (std::fabs(p1) > eb) return;
        t1 = 1.0;
        t2 = 0.0;
        type = kIsMulti;
        return;
    }
    if (v50 == 0.0 && v51 >= 0.0) {
        if (std::fabs(p0) > eb) return;
        t1 = 0.0;
        t2 = 1.0;
        type = kIsMulti;
        return;
    }
    if (v51 == 0.0 && v50 >= 0.0) {
        if (std::fabs(p1) > eb) return;
        t1 = 1.0;
        t2 = 1.0;
        type = kIsMulti;
        return;
    }

    double v53 = 0.0;
    double v52 = 1.0;
    if (v48 > 0.0) v53 = v48 / (v48 - v49);
    if (v50 > 0.0) v53 = v50 / (v50 - v51);
    if (v49 > 0.0) v52 = v48 / (v48 - v49);
    if (v51 > 0.0) v52 = v50 / (v50 - v51);

    const double v54 = eb * 9.0;
    const double v55 = p0 - p1;
    if (negeb > p0 && !(v53 > (v54 + p0) / v55)) v53 = (v54 + p0) / v55;
    if (p0 > eb && !(v53 > (p0 - v54) / v55)) v53 = (p0 - v54) / v55;
    if (negeb > p1 && !((v54 + p0) / v55 > v52)) v52 = (v54 + p0) / v55;
    if (p1 > eb) {
        const double v56 = (p0 - v54) / v55;
        if (!(v56 > v52)) v52 = v56;
    }

    double v57 = 0.0;
    double v58;
    if (v85 > 0.0) v57 = v85 / (v85 - v88);
    if (v69 > 0.0) v57 = v69 / (v69 - v81);
    if (!(v88 > 0.0)) {
        v58 = 1.0;
    } else {
        v58 = v85 / (v85 - v88);
    }
    if (v81 > 0.0) v58 = v69 / (v69 - v81);

    const double v59 = ea * 9.0;
    const double v60 = q0 - q1;
    if (negea > q0 && !(v57 > (v59 + q0) / v60)) v57 = (v59 + q0) / v60;
    if (q0 > ea && !(v57 > (q0 - v59) / v60)) v57 = (q0 - v59) / v60;
    if (negea > q1 && !((v59 + q0) / v60 > v58)) v58 = (v59 + q0) / v60;
    if (q1 > ea) {
        const double v61 = (q0 - v59) / v60;
        if (!(v61 > v58)) v58 = v61;
    }

    out1[0] = v53;
    out1[1] = v52;
    double v62;
    double v63;
    if (!(dyb * dya + v82 * v79 > 0.0)) {
        v62 = v57;
        v63 = v58;
    } else {
        v62 = v58;
        v63 = v57;
    }
    out2[0] = v63;
    out2[1] = v62;
    type = kIsOverlap;
    if (v53 >= v52) type = kIsNone;
    if (v57 >= v58) type = kIsNone;
}

}
}
