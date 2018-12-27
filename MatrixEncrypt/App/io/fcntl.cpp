#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "Enclave_u.h"

int ocall_open(const char* filename, int flags, mode_t mode) {
    return open(filename, flags, mode);
}

int ocall_fallocate(int fd, int mode, off_t offset, off_t len){
	return fallocate(fd, mode, offset, len);
}
int ocall_fcntl_flock(int fd, int cmd, struct flock *p){
	return fcntl(fd, cmd, p); 
}
int ocall_fcntl_void(int fd, int cmd){
	return fcntl(fd, cmd); 
}
int ocall_fcntl_int(int fd, int cmd, int pa){
	return fcntl(fd, cmd, pa); 
}
