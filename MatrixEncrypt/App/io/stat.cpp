#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Enclave_u.h"
//int ocall_stat([in, string]const char *pathname, [in, size=size]void *buf, unsigned int size)
//ocall_stat, (const char* pathname, void* buf, unsigned int size)


int ocall_stat(const char *pathname, struct stat *buf){
	return stat(pathname, buf);
}

int ocall_fstat(int fd, struct stat *buf){
	return fstat(fd, buf);
}

int ocall_fchmod(int fd, mode_t mode){
	return fchmod(fd, mode);
}

int ocall_mkdir(const char* pathname, mode_t mode){
	return mkdir(pathname, mode);
}

