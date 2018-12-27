#include <stdarg.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "stdio.h"
#include "unistd.h"
#include "mman.h"
//TODO   need modify ! 
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset){
    fprintf(stderr, "mmap is not supported using SGX!\n");
    return (void *)-1;
    // void * ret;
    // if (ocall_mmap(&ret, addr, length, prot, flags, fd, offset) != SGX_SUCCESS) return (void *)-1;
    // return ret;
}
int munmap(void *addr, size_t length){
    fprintf(stderr, "munmap is not supported using SGX!\n");
    return -1;
    // int ret;
    // if (ocall_munmap(&ret, addr, length) != SGX_SUCCESS) return -1;
    // return ret;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags, ... /* void *new_address */){
    fprintf(stderr, "mremap is not supported using SGX!\n");
    return (void *)-1;
    // void *ret;
    // void *new_address;
    // va_list ap;
    // va_start(ap, flags);

    // if(flags == 0) {
    // 	va_end(ap);
    // 	if (mremap_noaddress(&ret, old_address, old_size, new_size, flags) != SGX_SUCCESS) return (void *)-1;
    // }else {
    // 	new_address = va_arg(ap, void *);
    // 	va_end(ap);
    // 	if (mremap_address(&ret, old_address, old_size, new_size, flags, new_address) != SGX_SUCCESS) return (void *)-1;
    // }

    // return ret;
}