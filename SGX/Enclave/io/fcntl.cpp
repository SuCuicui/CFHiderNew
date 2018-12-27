#include <stdarg.h>
#include <string.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "fcntl.h"
#include "unistd.h"

int open(const char* filename, int flags, mode_t mode) {
    int ret;
    if (ocall_open(&ret, filename, flags, mode) != SGX_SUCCESS) return -1;
    return ret;
}

int fallocate(int fd, int mode, off_t offset, off_t len){

	int ret;
	if (ocall_fallocate(&ret, fd, mode, offset, len)!= SGX_SUCCESS) return -1;
    return ret;

}

int fcntl(int fd, int cmd, ... /* arg */ ){
	int ret;
    int pa;
    flock* pFlock;
	va_list ap;
    va_start(ap, cmd);
 //    flock* p=va_arg(ap,flock*);
 //    va_end(ap);
	///if (ocall_fcntl(&ret, fd, cmd, (void *)p, sizeof(struct flock)) != SGX_SUCCESS) return -1;
    //return ret;
    switch (cmd) {
    	case F_GETFD:
    		if (ocall_fcntl_void(&ret, fd, cmd) != SGX_SUCCESS) return -1;
    		break;
    	case F_SETFD:
		    pa=va_arg(ap,int);
		    va_end(ap);
    		if (ocall_fcntl_int(&ret, fd, cmd, pa) != SGX_SUCCESS) return -1;
    		break;
    	case F_GETLK:
    	case F_SETLK:
    		pFlock=va_arg(ap,flock*);
    		va_end(ap);
    		if (ocall_fcntl_flock(&ret, fd, cmd, pFlock ) != SGX_SUCCESS) return -1;
    		break;
    	//case F_FULLFSYNC:
    	//case op: lockTrace
    	default:
            va_end(ap);
    		ret = -1;
    }
    return ret;
}

