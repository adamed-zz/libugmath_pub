











struct __declspec(align(16)) spint_s
{
    unsigned char raw[304];
};
spint_s spint;

struct __declspec(align(16)) acom_s
{
    unsigned char raw[4240];
};
acom_s acom;

struct __declspec(align(16)) gbspline_vtable_t
{
    unsigned char raw[112];
};
gbspline_vtable_t gbspline_vtable;

struct __declspec(align(16)) delaunay_vtable_s
{
    unsigned char raw[868];
};
delaunay_vtable_s delaunay_vtable;
