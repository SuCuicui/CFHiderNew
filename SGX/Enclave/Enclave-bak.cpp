#include <stdarg.h>
#include <stdio.h>	  /* vsnprintf */
# include <unistd.h>
#include <string.h>
#include <sgx_cpuid.h>
#include <stdlib.h>
#include <cstring>
#define Table_Len 100000
#define MAX 100
#include "io/fcntl.h"
#include "io/mman.h"
#include "io/stat.h"
#include "io/stdio.h"
#include "io/stdlib.h"
#include "io/time.h"
#include "io/unistd.h"
#include <sgx_tcrypto.h>

#include "Enclave.h"
#include "Enclave_t.h"  /* print_string */
//----------------struct-------------------
struct Table_attr{
  long length;
  int p2;
};
struct Table_meta{
	int type;
	int p1;
	int p2;
	int op; 
	int para_name;
};

//---------------------global------------------

int v_int[Table_Len];
double v_double[Table_Len];
float v_float[Table_Len];
char v_char[Table_Len];
long v_long[Table_Len];
char v_byte[Table_Len];
 
char file[500]="/home/xidian/CFHiderNew/MatrixEncrypt/SGXindex1";

int hash_int[Table_Len];
double hash_double[Table_Len];
float hash_float[Table_Len];
char hash_char[Table_Len];
long hash_long[Table_Len];
char hash_byte[Table_Len];

int *table=(int*)malloc(sizeof(int)*Table_Len);
Table_attr Enclave_Table={0,0};

//-------------------------global_end----------------
int itoa(int val, char* buf)  
{  
	const unsigned int radix = 10;  
	char* p;  
	unsigned int a;		//every digit  
	int len;  
	char* b;			//start of the digit char  
	char temp;  
	unsigned int u;  
	p = buf;  
	if (val < 0)  
	{  
		*p++ = '-';  
		val = 0 - val;  
	}  
	u = (unsigned int)val;  
	b = p;  
	do  
	{  
		a = u % radix;  
		u /= radix;  
		*p++ = a + '0';  
	} while (u > 0);  
	len = (int)(p - buf);  
	*p-- = 0;  
	do  
	{  
		temp = *p;  
		*p = *b;  
		*b = temp;  
		--p;  
		++b;  
	} while (b < p);  
	return len;  
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

int ecall_ctr_decrypt(uint8_t *sql, 
	const char *sgx_ctr_key, uint8_t *p_dst,int len)    //ecall_ctr_decrypt(c,key_t,ppp,64);
{
	const uint32_t src_len = len;
	uint8_t p_ctr[16]= {'0'};
	const uint32_t ctr_inc_bits = 128;
	uint8_t *sgx_ctr_keys = (uint8_t *)malloc(16*sizeof(char));
	memcpy(sgx_ctr_keys,sgx_ctr_key,16);

	//ocall_print_int(len);
	//ocall_print_string((const char*)sgx_ctr_key);
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



int encall_hash_readin(char* buf,long line)
{
	char buffer[50];
	//return -10;
	char c=*buf;
	switch(c)
	{
		case 'i':strncpy(buffer,buf+4,44);//int_
			int int_data;
			int_data=atoi(buffer);
			hash_int[line]=int_data;
			break;
		case 'd':strncpy(buffer,buf+7,44);//double_
			double double_data;
			double_data=atof(buffer);
			hash_double[line]=double_data;
			break;
		case 'f':strncpy(buffer,buf+6,44);//float_
			float float_data;
			float_data=atof(buffer);
			hash_float[line]=(float)float_data;
			break;
		case 'c':strncpy(buffer,buf+5,44);//char_
			char char_data;
			char_data=*buffer;
			hash_char[line]=char_data;
			//hash_char[line]=double_data;
			break;
		case 'l':strncpy(buffer,buf+5,44);//long_
			long long_data;
			long_data=atol(buffer);
			hash_long[line]=long_data;
			break;
		case '\0':
			break;
		default:
			hash_int[line]=0;
			hash_double[line]=0;
			hash_float[line]=0;
			hash_char[line]=0;
			hash_long[line]=0;
			return -6;
	}
	return 1;
}
Table_meta get_table_meta(long Line)
{
	Table_meta meta;
	//meta.type=*(table+Line*4);
	meta.p1=*(table+Line*5+1);
	meta.p2=*(table+Line*5+2);
	meta.op=*(table+Line*5+3);
	meta.para_name=*(table+Line*5+4);
	return meta;
}
char ret[10000000];
long ret_len=0;
long g_line_num=0;
int split_file()
{
	char line[50]={0};
	int k=0;
	long line_num=0;
	ocall_print_string("splitting\n");
	//ocall_print_long(ret_len);
	for(long i=0;i<ret_len;i++){
		//printf("%c",ret[i]);
		if(ret[i]=='\n'){
			line[k]=0;
			if(k==0){
				continue;
			}
			encall_read_line(line,k,line_num);
			line_num++;
			k=0;
		}else{
			line[k]=ret[i];
			k++;
		}
	}
	g_line_num=line_num;
	
	//ocall_print_long(line_num);
	return 0;
}


int read_table(char* file)
{
	memset(ret,0,10000000);
	char* key_t="1234567812345678";

	int reout=open(file,O_RDONLY,S_IRUSR);

//------------read out
	long l=0;
	unsigned char sss[MAX];

	memset(sss,0,MAX);
	unsigned char c[100];
	//while(!reout.eof()){
	long loop2=0;
	long loop=0;
	while(1){
		loop++;
		if(loop%1000==0){
			sleep(0);
		}
		//reout.get(c);
		l=read(reout,c,64);                                                //????????
		//ocall_print_long(l);
		if(l<64){
			break;
		}
		
		//sss[l]=(unsigned char)c;
		//l++;
		if(64==l){
			c[64]=0;
			unsigned char ppp[MAX];
			memset(ppp,0,MAX);
			//ocall_print_string((const char*)c);
			ecall_ctr_decrypt(c,key_t,ppp,64);
			//ocall_print_string((const char*)ppp);
			for(int i=0;i<l;i++){
				//ocall_print_string("s");
				strncat(ret,(const char*)&ppp[i],1);
				//ocall_print_string("e");
			}
			ret_len=ret_len+l;
			l=0;
			//ocall_print_long(ret_len);
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
		ret_len=ret_len+l;
		l=0;
		//ocall_print_long(ret_len);
	}
	//ocall_print_string("read ok\n");
	split_file();
	//printf("%d\n",table[18]);
	return 0;
}

int encall_table_load(void)
{
	long s=0;
	int* msgs=(int*)malloc(sizeof(int)*Table_Len);
	memset(msgs,'\0',sizeof(int)*Table_Len);
	read_table(file);

	if(Enclave_Table.length==0){
	Enclave_Table.length=g_line_num;
	}
	return 1;
}


int encall_read_line(char* in_buf,int buf_len,long line)
{
	int read_num=0;
	if(*in_buf>=48 && *in_buf<=57){// number
		read_num=atoi(in_buf);
	}else if(*in_buf == 45){
		read_num=atoi(in_buf);
	}else{
		int in_flag=999;
		read_num=0-line;
		int load_flagh=-998;
		encall_hash_readin(in_buf,line);
	}
	//printf("%d\n",read_num);
	table[line]=read_num;
	Enclave_Table.length++;
	return 0;
}

// void print_IntArray(){
// 	for(int i=0;i<7;i++){
// 		printf("v_int[%d]=%d\n",i,v_int[i]);
// 	}
// }
void encall_varible(int* v_array,int size) {
		//ocall_print_int(size);
		//ocall_print_int(v_array[1]);
		int i;
		int i1=0,f1=0,d1=0,c1=0,l1=0,b1 = 0;
		for (int j = 1;j <= size;j++) {
			if (v_array[j-1] != 0) {
				for (int j1 = 0;j1 < v_array[j-1];j1++) {
					switch (j)
					{
					case 1:
						v_int[i1++] = 0;
						break;
					case 2:
						v_double[d1++] = 0.0;
						break;
					case 3:
						v_float[f1++] = 0.0;
						break;
					case 4:
						v_char[c1++] = NULL;
						break;
					case 5:
						v_long[l1++] = 0;
						break;
					case 6:
						v_byte[b1++] = NULL;
						break;
					default:
						break;
					}
				}
			}
		}

	printf("init value in encalve:\n");
	for(int i=0;i<i1;i++){
		printf("v_int[%d]=%d ",i,v_int[i]);
	}
	printf("\n");


	for(int i=0;i<f1;i++){
		printf("v_float[%d]=%f ",i,v_float[i]);
	}
	printf("\n");

	for(int i=0;i<d1;i++){
		printf("v_double[%d]=%f ",i,v_double[i]);
	}
	printf("\n");

	for(int i=0;i<l1;i++){
		printf("v_long[%d]=%ld ",i,v_long[i]);
	}
	printf("\n");
//printf("int_array_len=%d\n",i1);
//printf("double_array_len=%d\n",d1);
//printf("float_array_len=%d\n",f1);
//printf("char_array_len=%d\n",c1);
//printf("long_array_len=%d\n",l1);
//printf("byte_array_len=%d\n",b1);
}

int encall_switch_type_i(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
// ocall_print_string("go in encall_switch_type_i\n");
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	int return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

double encall_switch_type_d(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	double return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

float encall_switch_type_f(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	float return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

char encall_switch_type_c(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	char return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

long encall_switch_type_l(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
//ocall_print_string("go in encall_switch_type_l\n");
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	long return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

char encall_switch_type_b(long Line, int* int_array, int lenint,double* double_array, int lendouble,float* float_array, int lenfloat,char* char_array, int lenchar,long* long_array, int lenlong,char* byte_array, int lenbyte) {
	int type=*(table+Line*5);
	if (type == 10) {
		return 0;
	}
	char return_flag = -1;
	switch (type) {
		case 1:return_flag = print_int(Line, int_array);break;
		case 2:return_flag = print_double(Line, double_array);break;
		case 3:return_flag = print_float(Line, float_array);break;
		case 4:return_flag = print_char(Line, char_array);break;
		case 5:return_flag = print_long(Line, long_array);break;
		case 6:return_flag = print_byte(Line, byte_array);break;
		default:return_flag = -5;
		}
	return return_flag;
}

//----------------------------------------------------------------------------------------------------------

int print_int(long Line, int* int_array)//---------------------------int
{
//ocall_print_string("go in print_int\n");
		Table_meta meta=get_table_meta(Line);
//printf("Line=%ld\n",Line);
//printf("op1=%d\n",meta.p1);
//printf("op2=%d\n",meta.p2);
//printf("op=%d\n",meta.op);
//printf("re=%d\n",meta.para_name);

		int return_flag = -999;
		int para1,para2;
		if (meta.p1 < 0){  //consants
			para1 = hash_int[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = int_array[meta.p1];
		}else{ //encalve
			para1 = v_int[meta.p1 % 10];
		}
		if (meta.p2 < 0){  //consants
			para2 = hash_int[0-meta.p2];
		}else if(meta.p2<10 && meta.p2>=0){ //list
			para2 = int_array[meta.p2];
		}else{ //encalve
			para2 = v_int[meta.p2 % 10];
		}
		switch (meta.op) {
			case -1:return_flag = para1;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		if (meta.para_name>0) {  //update
			v_int[meta.para_name % 10] = return_flag;
			//printf("Update v_int[%d]=%d\n",meta.para_name % 10,return_flag);
			return_flag = 1000;
		}
//ocall_print_string("i success\n");
		// print_array();

	// printf("after update int:\n");
	// for(int i=0;i<10;i++){
	// 	printf("v_int[%d]=%d ",i,v_int[i]);
	// }
	// printf("\n");
		
	return return_flag;

}

double print_double(long Line, double* double_array)//---------------------------double
{
		Table_meta meta=get_table_meta(Line);
		double return_flag = -999;
		double para1,para2;
		if (meta.p1 < 0){  //consants
			para1 = hash_double[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = double_array[meta.p1];
		}else{ //encalve
			para1 = v_double[meta.p1 % 10];
		}
		
		if (meta.p2 < 0){  //consants
			para2 = hash_double[0-meta.p2];
		}else if(meta.p2<10 && meta.p2>=0){ //list
			para2 = double_array[meta.p2];
		}else{ //encalve
			para2 = v_double[meta.p2 % 10];
		}
		printf("pa1=%lf,pa2=%lf\n",para1,para2);
		switch (meta.op) {
			case -1:return_flag = para1;   //x=2; or x=y;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			//case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		if (meta.para_name>0) { 
			v_double[meta.para_name % 10] = return_flag;
			return_flag = 1000;
		}
		ocall_print_string("d success\n");

	for(int i=0;i<10;i++){
		printf("v_double[%d]=%f ",i,v_double[i]);
	}
	// printf("\n");
		return return_flag;
}

float print_float(long Line, float* float_array)//---------------------------float
{
		Table_meta meta=get_table_meta(Line);
		float return_flag = -999;
		float para1,para2;
		if (meta.p1 < 0){  //consants
			para1 = hash_float[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = float_array[meta.p1];
		}else{ //encalve
			para1 = v_float[meta.p1 % 10];
		}
		
		if (meta.p2 < 0){  //consants
			para2 = hash_float[0-meta.p2];
		}else if(meta.p2<10 && meta.p2>=0){ //list
			para2 = float_array[meta.p2];
		}else{ //encalve
			para2 = v_float[meta.p2 % 10];
		}
		switch (meta.op) {
			case -1:return_flag = para1;   //x=2; or x=y;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			//case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		if (meta.para_name>0) { 
			v_float[meta.para_name % 10] = return_flag;
			return_flag = 1000;
		}
ocall_print_string("f success\n");
		

	for(int i=0;i<10;i++){
		printf("v_float[%d]=%f ",i,v_float[i]);
	}
	printf("\n");

		return return_flag;
}

char print_char(long Line, char* char_array)//---------------------------char
{
		
		Table_meta meta=get_table_meta(Line);
		char return_flag = NULL;
		char para1,para2;

		if (meta.p1 < 0){  //consants
			para1 = hash_char[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = char_array[meta.p1];
		}else{ //encalve
			para1 = v_char[meta.p1 % 10];
		}
		
		if (meta.p2 < 0){  //consants
			para2 = hash_char[0-meta.p2];
		}else if(meta.p2<10 && meta.p2>=0){ //list
			para2 = char_array[meta.p2];
		}else{ //encalve
			para2 = v_char[meta.p2 % 10];
		}
		switch (meta.op) {
			case -1:return_flag = para1;   //x=2; or x=y;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			//case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		if (meta.para_name>0) { 
			v_char[meta.para_name % 10] = return_flag;
			return_flag = '?';
		}
ocall_print_string("c success\n");
		return return_flag;
}

long print_long(long Line, long* long_array)//---------------------------long
{
ocall_print_string("go in print_long\n");
		Table_meta meta=get_table_meta(Line);
		long return_flag = -999;
		long para1,para2;
		if (meta.p1 < 0){  //consants
			para1 = hash_long[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = long_array[meta.p1];
		}else{ //encalve
			para1 = v_long[meta.p1 % 10];
		}
		
		if (meta.p2 < 0){  //consants
			para2 = hash_long[0-meta.p2];
		}else if(meta.p2<10 && meta.p2>=0){ //list
			para2 = long_array[meta.p2];
		}else{ //encalve
			para2 = v_long[meta.p2 % 10];
		}
		
		switch (meta.op) {
			case -1:return_flag = para1;   //x=2; or x=y;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		//printf("Line is:%ld\n",Line);
		//printf("return is:%ld\n",return_flag);
		//printf("op is:%d\n",meta.op);
		//printf("meta.para_name is:%d\n",meta.para_name);
		if (meta.para_name>0) { 
			v_long[meta.para_name % 10] = return_flag;
			return_flag = 1000;
		}
ocall_print_string("l success\n");

	for(int i=0;i<10;i++){
		printf("v_long[%d]=%ld ",i,v_long[i]);
	}
	printf("\n");
		return return_flag;
}

char print_byte(long Line, char* byte_array)//---------------------------byte
{
		Table_meta meta=get_table_meta(Line);
		char return_flag = NULL;
		char para1,para2;
		if (meta.p1 < 0){  //consants
			para1 = hash_byte[0-meta.p1];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para1 = byte_array[meta.p1];
		}else{ //encalve
			para1 = v_byte[meta.p1 % 10];
		}
		if (meta.p2 < 0){  //consants
			para2 = hash_byte[0-meta.p2];
		}else if(meta.p1<10 && meta.p1>=0){ //list
			para2 = byte_array[meta.p2];
		}else{ //encalve
			para2 = v_byte[meta.p2 % 10];
		}
		switch (meta.op) {
			case -1:return_flag = para1;   //x=2; or x=y;
			case 1:return_flag = para1 + para2;break; //+
			case 2:return_flag = para1 - para2;break; //-
			case 3:return_flag = para1 * para2;break; //*
			case 4:return_flag = para1 / para2;break; // /
			case 5:return_flag = para1 % para2;break; // %
			case 6:return_flag=( para1==para2?1:0);break;
	 		case 7:return_flag=( para1!=para2?1:0);break;
	  		case 8:return_flag=( para1>para2?1:0);break;
	  		case 9:return_flag=( para1<para2?1:0);break;
	  		case 10:return_flag=( para1>=para2?1:0);break;
	  		case 11:return_flag=( para1<=para2?1:0);break;
			default:return_flag = -11;
		}
		if (meta.para_name>0) { 
			v_byte[meta.para_name % 10] = return_flag;
			return_flag = '?';
		}
ocall_print_string("b success\n");
		return return_flag;
}
