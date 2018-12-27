#include <stdlib.h>
#include "Enclave_u.h"

char *ocall_getenv(const char *name){
	return getenv(name);
}
