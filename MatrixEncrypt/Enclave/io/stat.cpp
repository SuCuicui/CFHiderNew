//#include <sys/types.h>
//#include <unistd.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "stat.h"


int stat(const char *pathname, struct stat *buf){
    int ret;
    if (ocall_stat(&ret, pathname, buf) != SGX_SUCCESS) return -1;
    return ret;
}

int fstat(int fd, struct stat *buf){
    int ret;
    if (ocall_fstat(&ret, fd, buf) != SGX_SUCCESS) return -1;
    return ret;
}

 int fchmod(int fd, mode_t mode){
	int ret;
    if (ocall_fchmod(&ret, fd, mode) != SGX_SUCCESS)return -1;
    return ret;
}

int mkdir(const char *pathname, mode_t mode){
	int ret;
    if (ocall_mkdir(&ret, pathname, mode) != SGX_SUCCESS)return -1;
    return ret;
}

