#ifndef __VFS_TIME_H
#define __VFS_TIME_H

#include "user_types.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

time_t time(time_t *t);
int utimes(const char *filename, const struct timeval times[2]);
int gettimeofday(struct timeval *tv, struct timezone *tz);

#ifdef __cplusplus
}
#endif

#endif