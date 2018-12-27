/* stdio.cpp */
#include <stdarg.h>
#include <string.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "stdlib.h"

char *getenv(const char *name){
	char *ret;
	if (ocall_getenv(&ret, name) != SGX_SUCCESS) return NULL;
    return ret;
}