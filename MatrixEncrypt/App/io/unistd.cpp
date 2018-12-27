#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "Enclave_u.h"
#include <stdio.h>

ssize_t ocall_read(int file, void *buf, size_t count) {
    return read(file, buf, count);
}
ssize_t ocall_write(int file, const void *buf, size_t count) {
    return write(file, buf, count);
}

int ocall_close(int fd) {
    return close(fd);
}

int ocall_fchown(int fd, uid_t owner, gid_t group) {
    return fchown(fd, owner, group);
}
char *ocall_getcwd(char *buf, size_t size){
	return getcwd(buf,size);
}
int ocall_truncate(const char *path, off_t length){
	return truncate(path, length);
}

int ocall_ftruncate(int fd, off_t length){
	return ftruncate(fd, length);
}
ssize_t ocall_pread(int fd, void *buf, size_t count, off_t offset){
	return pread(fd, buf, count, offset);
}
ssize_t ocall_pwrite(int fd, const void *buf, size_t count, off_t offset){
	return pwrite(fd, buf, count, offset);
}
int ocall_access(const char* pathname, int mode) {
    return access(pathname,  mode);
}
int ocall_unlink(const char *pathname){
	return unlink(pathname);
}
int ocall_rmdir(const char *pathname){
	return rmdir(pathname);
}
uid_t ocall_geteuid(void){
	return geteuid();
}
//uid_t ocall_getuid(void){
//	return getuid();
//}
off_t ocall_lseek(int fd, off_t offset, int whence){
	return lseek(fd, offset, whence);
}
int ocall_fsync(int fd){
	return fsync(fd);
}
pid_t ocall_getpid(void){
	return getpid();
}
unsigned int ocall_sleep(unsigned int seconds){
	return sleep(seconds);
}




