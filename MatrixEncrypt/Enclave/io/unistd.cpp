#include <stdarg.h>
#include <string.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "stdio.h"
#include "unistd.h"

int stdin = 0, stdout = 1, stderr = 2;

ssize_t read(int fd, void *buf, size_t count) {
    ssize_t ret;
    if (ocall_read(&ret, fd, buf, count) != SGX_SUCCESS) return -1;
    return ret;
}

ssize_t write(int fd, const void *buf, size_t count) {
    ssize_t ret;
    if (ocall_write(&ret, fd, buf, count) != SGX_SUCCESS) return -1;
    return ret;
}


int close(int fd) {
	int ret;
    if (ocall_close(&ret, fd) != SGX_SUCCESS) return -1;
    return ret;
}

int fchown(int fd, uid_t owner, gid_t group) {
    int ret;
    if (ocall_fchown(&ret, fd, owner, group) != SGX_SUCCESS) return -1;
    return ret;
}
char *getcwd(char *buf, size_t size){
	char *ret;
	if (ocall_getcwd(&ret, buf, size) != SGX_SUCCESS) return NULL;
	return ret;
}

int truncate(const char *path, off_t length){
	int ret;
	if (ocall_truncate(&ret, path, length) != SGX_SUCCESS) return -1;
	return ret;
}
int ftruncate(int fd, off_t length){
	int ret;
	if (ocall_ftruncate(&ret, fd, length) != SGX_SUCCESS) return -1;
	return ret;
}

ssize_t pread(int fd, void *buf, size_t count, off_t offset){
	ssize_t ret;
	if(ocall_pread(&ret, fd, buf, count, offset) != SGX_SUCCESS) return -1;
	return ret;
}

ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset){
	ssize_t ret;
	if (ocall_pwrite(&ret, fd, buf, count, offset) != SGX_SUCCESS) return -1;
	return ret;
}
int access(const char* pathname, int mode) {
    int ret;
    if (ocall_access(&ret, pathname, mode) != SGX_SUCCESS) return -1;
    return ret;
}
int unlink(const char *pathname){
	int ret;
	if (ocall_unlink(&ret, pathname) != SGX_SUCCESS) return -1;
	return ret;
}
int rmdir(const char *pathname){
	int ret;
	if (ocall_rmdir(&ret, pathname) != SGX_SUCCESS) return -1;
	return ret;
}

uid_t geteuid(void){
	uid_t ret;
	if (ocall_geteuid(&ret) != SGX_SUCCESS) return -1;
	return ret;
}
//uid_t getuid(void){
//	uid_t ret;
//	if (ocall_getuid(&ret) != SGX_SUCCESS) return -1;
//	return ret;
//}
off_t lseek(int fd, off_t offset, int whence){
	off_t ret;
	if (ocall_lseek(&ret, fd, offset, whence) != SGX_SUCCESS) return -1;
	return ret;
}

int fsync(int fd){
	int ret;
	if (ocall_fsync(&ret, fd) != SGX_SUCCESS) return -1;
	return ret;
}
pid_t getpid(void){
	pid_t ret;
	if (ocall_getpid(&ret) != SGX_SUCCESS) return -1;
	return ret;
}
unsigned int sleep(unsigned int seconds){
	unsigned int ret;
	if (ocall_sleep(&ret, seconds) != SGX_SUCCESS) return -1;
	return ret;
}