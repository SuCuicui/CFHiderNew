/* stdio.cpp */
#include <stdarg.h>
#include <string.h>
#include "Enclave.h"
#include "Enclave_t.h"
#include "unistd.h"
#include "stdio.h"

void fprintf(int file, const char* fmt, ...) {
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    size_t len = strlen(buf);
    write(file, (void *)buf, (unsigned int)len);
}
