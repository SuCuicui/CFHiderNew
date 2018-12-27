#include "Enclave.h"
#include "Enclave_t.h"
#include "unistd.h"
#include "stdio.h"
#include "time.h"

time_t time(time_t *t){
	time_t ret;
	if(ocall_time(&ret, t)!= SGX_SUCCESS) return ((time_t) -1);
    return ret;
}

int utimes(const char *filename, const struct timeval times[2]){
	int ret;
	if(ocall_utimes(&ret, filename, times)!= SGX_SUCCESS) return -1;
    return ret;
}

int gettimeofday(struct timeval *tv, struct timezone *tz){
	int ret;
	if ( tz !=0 ) {
		fprintf(stderr, "Error! gettimeofday : the second parameter is expected to be 0, but is not 0 now!\n"\
						"You should process this func mannally in Enclave/vfslib/time.cpp\n");
		return -1;
	}
	if(ocall_gettimeofday(&ret, tv)!= SGX_SUCCESS) return -1;
    return ret;
}