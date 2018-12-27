#ifndef __VFS_MMAN_H
#define __VFS_MMAN_H

#include "user_types.h"


#define MAP_SHARED  1
#define MAP_FAILED  -1
#define MAP_PRIVATE  2

#define PROT_READ  1
#define PROT_WRITE  2


# define MREMAP_MAYMOVE	1
# define MREMAP_FIXED	2

#ifdef __cplusplus
extern "C" {
#endif

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
void *mremap(void *old_address, size_t old_size, size_t new_size, int flags, ... /* void *new_address */);

#ifdef __cplusplus
}
#endif

#endif