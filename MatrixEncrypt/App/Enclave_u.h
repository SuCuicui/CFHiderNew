#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "user_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_open, (const char* filename, int flags, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fallocate, (int fd, int mode, off_t offset, off_t len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl_flock, (int fd, int cmd, struct flock* p));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl_int, (int fd, int cmd, int pa));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl_void, (int fd, int cmd));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getenv, (const char* name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_stat, (const char* pathname, struct stat* buf));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fstat, (int fd, struct stat* buf));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchmod, (int fd, unsigned int mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkdir, (const char* pathname, mode_t mode));
time_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_time, (time_t* t));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_utimes, (const char* filename, const struct timeval* times));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gettimeofday, (struct timeval* tv));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read, (int file, void* buf, size_t count));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write, (int file, const void* buf, size_t count));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_close, (int fd));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchown, (int fd, uid_t owner, gid_t group));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getcwd, (char* buf, size_t size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_truncate, (const char* path, off_t length));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftruncate, (int fd, off_t length));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pread, (int fd, void* buf, size_t count, off_t offset));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pwrite, (int fd, const void* buf, size_t count, off_t offset));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_access, (const char* pathname, int mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_unlink, (const char* pathname));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rmdir, (const char* pathname));
uid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_geteuid, ());
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lseek, (int fd, off_t offset, int whence));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fsync, (int fd));
pid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpid, ());
unsigned int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sleep, (unsigned int seconds));

sgx_status_t encall_test(sgx_enclave_id_t eid, int* retval, char* a);
sgx_status_t ecall_ctr_encrypt(sgx_enclave_id_t eid, int* retval, const char* sql, const char* sgx_ctr_key, uint8_t* p_dst);
sgx_status_t ecall_ctr_decrypt(sgx_enclave_id_t eid, int* retval, uint8_t* sql, const char* sgx_ctr_key, uint8_t* p_dst, int len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
