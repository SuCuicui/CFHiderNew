#include <stdarg.h>
#include <stdio.h>	  /* vsnprintf */
#include <stdlib.h>
#include <string.h>
#include "Enclave.h"
#include "Enclave_t.h"  /* print_string */
#include <sgx_tcrypto.h>
#include "io/fcntl.h"
#include "io/mman.h"
#include "io/stat.h"
#include "io/stdio.h"
#include "io/stdlib.h"
#include "io/time.h"
#include "io/unistd.h"
#define MAX 100000
/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */

char ret[100000];

int encall_test(char* file)
{

	// int src=open(file,O_RDONLY,S_IRUSR);
	// unsigned char s[64];
	// int ret = read(src,s,64);
	// unsigned char ppp[64];
	// ecall_ctr_decrypt(s,"1234567812345678",ppp,64);
	// printf((char*)ppp);
	// return 0;

	memset(ret,0,100000);
	char* key_t="1234567812345678";

	int reout=open(file,O_RDONLY,S_IRUSR);
	ocall_print_string("hahahah\n");
//------------read out
	long l=0;
	unsigned char sss[MAX];
	memset(sss,0,MAX);
	unsigned char c[65];
	//while(!reout.eof()){
	while(1){
		//reout.get(c);
		l=read(reout,c,64);
		if(l<64){
			break;
		}
		
		//sss[l]=(unsigned char)c;
		//l++;
		if(64==l){
			c[64]=0;
			unsigned char ppp[MAX];
			memset(ppp,0,MAX);
			ecall_ctr_decrypt(c,key_t,ppp,64);
			for(int i=0;i<l;i++){
				strncat(ret,(const char*)&ppp[i],1);
			}
			l=0;
			memset(c,0,65);
		}
	}
	if(l<64){
		c[l]=0;
		unsigned char ppp[MAX];
		memset(ppp,0,MAX);
		ecall_ctr_decrypt(c,key_t,ppp,l);
		for(int i=0;i<l;i++){
		strncat(ret,(const char*)&ppp[i],1);
		}
		l=0;
	}
	printf(ret);
	return 0;
}

int ecall_ctr_encrypt(const char *sql, 
	const char *sgx_ctr_key, uint8_t *p_dst)
{
	sgx_status_t rc;
	char *zErrMsg = 0;
	//ocall_print_string("im encrypting\n");
	//const sgx_aes_ctr_128bit_key_t *p_key = "1234567812345678";

	const uint8_t *p_src = (const uint8_t *)sql;
	const uint32_t src_len = strlen(sql);

	uint8_t p_ctr[16]= {'0'};
	const uint32_t ctr_inc_bits = 128;
	uint8_t *sgx_ctr_keys = (uint8_t *)malloc(16*sizeof(char));
	memcpy(sgx_ctr_keys,sgx_ctr_key,16);
/*
	fprintf(stdout,"sgx_ctr_keys = %s\n",sgx_ctr_key);

	ocall_print_string(stdout,"memcpy ok\n");
	//uint8_t *p_dst;
	ocall_print_string(stdout,"sgx_ctr_keys = %s\n",sgx_ctr_keys);*/

	uint8_t *p_dsts = (uint8_t *)malloc(src_len*sizeof(char));

	rc =sgx_aes_ctr_encrypt((sgx_aes_ctr_128bit_key_t *)sgx_ctr_keys, p_src, src_len, p_ctr, ctr_inc_bits, p_dsts);

	sgx_status_t rc2;

	uint8_t *p_dsts2 = (uint8_t *)malloc(src_len*sizeof(char));
	uint8_t p_ctr2[16]= {'0'};

	rc2 = sgx_aes_ctr_decrypt((sgx_aes_gcm_128bit_key_t *)sgx_ctr_keys, p_dsts, src_len, p_ctr2, ctr_inc_bits, p_dsts2);

/*
	for(int i=0; i<src_len; i++){
		ocall_print_string(stdout, "%02x ", p_dsts[i]);
	}*/
	*((char*)p_dsts+src_len)='\0';
	//ocall_print_string((char*)p_dsts);


	for(int i=0; i<src_len; i++){
		p_dst[i] = p_dsts[i];
		//ocall_print_string(stdout,"%c", p_dsts2[i]);
	}
	//ocall_print_string("\n");
	*((char*)p_dsts2+src_len)='\0';
	//ocall_print_string((char*)p_dsts2);



	if( rc!=SGX_SUCCESS ){
	  ocall_print_string("SQL error");
	}
	return 0;
}

int ecall_ctr_decrypt(uint8_t *sql, 
	const char *sgx_ctr_key, uint8_t *p_dst,int len)
{
	const uint32_t src_len = len;
	uint8_t p_ctr[16]= {'0'};
	const uint32_t ctr_inc_bits = 128;
	uint8_t *sgx_ctr_keys = (uint8_t *)malloc(16*sizeof(char));
	memcpy(sgx_ctr_keys,sgx_ctr_key,16);
	sgx_status_t rc;
	uint8_t *p_dsts2 = (uint8_t *)malloc(src_len*sizeof(char));
	//uint8_t *p_dsts=
	rc = sgx_aes_ctr_decrypt((sgx_aes_gcm_128bit_key_t *)sgx_ctr_keys, sql, src_len, p_ctr, ctr_inc_bits, p_dsts2);

	for(int i=0; i<src_len; i++){
		p_dst[i] = p_dsts2[i];
		//ocall_print_string(stdout,"%c", p_dsts2[i]);
	}
	return 0;
}

void printf(const char *fmt, ...)
{
	char buf[BUFSIZ] = {'\0'};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}
