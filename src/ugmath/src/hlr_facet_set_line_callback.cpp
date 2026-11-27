







typedef void(__cdecl *ugm_hlr_line_callback_t)(
    const double *const, const double *const, int, void *);



extern ugm_hlr_line_callback_t g_ugm_hlr_line_cb;

void HLR_FACET_set_line_callback(ugm_hlr_line_callback_t cb)
{
    g_ugm_hlr_line_cb = cb;
}
