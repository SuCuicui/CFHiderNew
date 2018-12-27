#ifndef _APP_H_
#define _APP_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */

#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
using namespace std;

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

# define TOKEN_FILENAME   "enclave.token"
# define ENCLAVE_FILENAME "enclave.signed.so"

#define READ_MAX 100000
extern sgx_enclave_id_t global_eid;    /* global enclave id */
extern int hash_int[10000];
extern double hash_double[10000];
extern float hash_float[10000];
extern char hash_char[10000];
extern long hash_long[10000];
#if defined(__cplusplus)
extern "C" {
#endif
//void ocall_load_hash(void);
void ocall_file_write(char* file,char* buf,int len);
void ocall_file_add(char* file,char* buf,int len);
void ocall_file_read(char* file,int* buf,long* start);
void ocall_file_getline(char* file,char* buf,long* line_num);
void ocall_print_string(const char *str);

vector<string> splitEx(const string& src, string separate_character);
void print_error_message(sgx_status_t ret);
int initialize_enclave(void);
//void encall_print(char *fmt);
#if defined(__cplusplus)
}
#endif

#endif /* !_APP_H_ */
