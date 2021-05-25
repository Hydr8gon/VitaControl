#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <psp2kern/kernel/sysmem.h>

namespace Mempool
{

extern SceUID uid;

inline void init()
{
    // Prepare a memory pool for dynamic allocation
    SceKernelHeapCreateOpt opt;
    opt.size     = 0x1C;
    opt.uselock  = 0x100;
    opt.field_8  = 0x10000;
    opt.field_C  = 0;
    opt.memtype  = 0;
    opt.field_14 = 0;
    opt.field_18 = 0;
    uid = ksceKernelCreateHeap("vitacontrol_mempool", 0x100, &opt);
}

inline void deinit()
{
    // Clean up the memory pool
    if (uid > 0)
    {
        ksceKernelDeleteHeap(uid);
        uid = -1;
    }
}

inline void *alloc(size_t size)
{
    return ksceKernelAllocHeapMemory(uid, size);
}

inline void free(void *ptr)
{
    ksceKernelFreeHeapMemory(uid, ptr);
}

};

#endif // MEMPOOL_H
