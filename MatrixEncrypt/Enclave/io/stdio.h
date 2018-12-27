/* stdio.h */
#ifndef __VFS_STDIO_H
#define __VFS_STDIO_H

#include "user_types.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUF_SIZE
#undef BUF_SIZE
#define BUF_SIZE 1024
#endif

void fprintf(int file, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif