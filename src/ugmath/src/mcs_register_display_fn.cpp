




typedef void (*DISPLAY_FN)();

DISPLAY_FN g_ugmath_display_fn;

DISPLAY_FN MCS_register_display_fn(DISPLAY_FN fn)
{
    DISPLAY_FN old = g_ugmath_display_fn;
    g_ugmath_display_fn = fn;
    return old;
}
