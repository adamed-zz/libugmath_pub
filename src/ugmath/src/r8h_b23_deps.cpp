



#include <windows.h>

namespace {

thread_local int g_tls_epoch = 0;
int g_init_lock = 0;
int g_gen_counter = (-2147483647 - 1);
void* g_err_table[8] = {(void*)0x428740, 0, 0, 0, 0, 0, 0, 0};

}

namespace b23dev {

int TlsEpoch() { return g_tls_epoch; }
int* InitLock() { return &g_init_lock; }
void* ErrorTable() { return g_err_table; }


void LockAcquire(int* lock) {
    for (;;) {
        const int v = *lock;
        if (v == 0) {
            *lock = -1;
            return;
        }
        if (v == -1) {
            ::Sleep(100);
            continue;
        }
        g_tls_epoch = g_gen_counter;
        return;
    }
}


void LockRelease(int* lock) {
    ++g_gen_counter;
    *lock = g_gen_counter;
    g_tls_epoch = g_gen_counter;
}

}
