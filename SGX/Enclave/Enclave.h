#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#include <stdlib.h>
#include <assert.h>

#if defined(__cplusplus)
extern "C" {
#endif

int print_int(long line,int* int_array);
double print_double(long line,double* double_array);
float print_float(long line,float* float_array);
char print_char(long line,char* char_array);
long print_long(long line,long* long_array);
char print_byte(long line,char* byte_array);

int encall_table_load();
int encall_hash_readin(char* buf,long line);
int encall_read_line(char* in_buf,int buf_len,long line);
void encall_varible(int* v_array,int size);
int encall_deleteValue();
int encall_switch_type_i(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
double encall_switch_type_d(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
float encall_switch_type_f(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
char encall_switch_type_c(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
long encall_switch_type_l(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
char encall_switch_type_c(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
#if defined(__cplusplus)
}
#endif

#endif /* !_ENCLAVE_H_ */
