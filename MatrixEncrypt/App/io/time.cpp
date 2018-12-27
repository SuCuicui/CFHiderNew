#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>
#include "Enclave_u.h"

time_t ocall_time(time_t *t){
	return time(t);
}

int ocall_utimes(const char *filename, const struct timeval times[2]){
	return utimes(filename,times);
}

int ocall_gettimeofday(struct timeval *tv){
	return gettimeofday(tv, 0);
}