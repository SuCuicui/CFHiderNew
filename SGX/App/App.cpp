#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
# include <unistd.h>
# include <pwd.h>

#define MAX_PATH FILENAME_MAX

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"
#include<fstream>
#include<iomanip>
#include <iostream>
#include <vector>
using namespace std;
#include <cstdarg>
#include "invoker_sgx_invoker.h"

typedef unsigned char byte;
#define ArrayLen 10000
//-------------------------------------------------
int hash_int[10000];
double hash_double[10000];
float hash_float[10000];
char hash_char[10000];
long hash_long[10000];
int sgx_use_flag=0;
/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 1;


//--------------------------------------------


int itoa(int val, char* buf)  
{  
    const unsigned int radix = 10;  
    char* p;  
    unsigned int a;        //every digit  
    int len;  
    char* b;            //start of the digit char  
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

int destroy_enclave(void)
{
    //------------------------------destroy------------
    if(SGX_SUCCESS==sgx_destroy_enclave(global_eid)){
	sgx_use_flag=0;
    	printf("Enclave destroy success\n");
	return 0;
    }else{
	printf("Enclave destroy failure\n");
	return -1;
    }

}

JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_init(JNIEnv *env, jclass obj)
//int init_enclave(void)
{
	if(sgx_use_flag){
		return 0;
	}
    if(initialize_enclave() < 0){
        printf("init Failed ...\n");
        getchar();
        return -1; 
    }
	//------------load-----------------------
	int load_flag=-111;
	encall_table_load(global_eid,&load_flag);
	sgx_use_flag=1;
	printf("load ok\n");
	return load_flag;
}

JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_destroy(JNIEnv *env, jclass obj)
{

    //------------------------------destroy------------
    if(SGX_SUCCESS==sgx_destroy_enclave(global_eid)){
	sgx_use_flag=0;
    	printf("Enclave destroy success\n");
	return 0;
    }else{
	printf("Enclave destroy failure\n");
	return -1;
    }
}
/**
	commitInt
*/
JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_commitInt
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	int rei=999;
	//printf("++++++++++++++++++++++++++++++\n");
	sgx_status_t ret=encall_switch_type_i(global_eid,&rei,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return rei;
}
/**
	commitDouble
*/
JNIEXPORT jdouble JNICALL Java_invoker_sgx_1invoker_commitDouble
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	double red=999;
	sgx_status_t ret=encall_switch_type_d(global_eid,&red,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return red;
}
/**
	commitFloat
*/
JNIEXPORT jfloat JNICALL Java_invoker_sgx_1invoker_commitFloat
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	float ref=999;
	sgx_status_t ret=encall_switch_type_f(global_eid,&ref,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return ref;
}
/**
	commitChar
*/
JNIEXPORT jchar JNICALL Java_invoker_sgx_1invoker_commitChar
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	char rec=NULL;
	sgx_status_t ret=encall_switch_type_c(global_eid,&rec,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return rec;
}

/**
	commitByte
*/
JNIEXPORT jbyte JNICALL Java_invoker_sgx_1invoker_commitByte
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	char reb=NULL;
	sgx_status_t ret=encall_switch_type_b(global_eid,&reb,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return reb;
}
/**
	commitLong
*/
JNIEXPORT jlong JNICALL Java_invoker_sgx_1invoker_commitLong
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	long rel=999;
	sgx_status_t ret=encall_switch_type_l(global_eid,&rel,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}
	return rel;
}

JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_commitBranch
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	int rei=999;
	sgx_status_t ret=encall_switch_type_i(global_eid,&rei,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}else{
		return 1;
	}
	return 0;

}

JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_commitUpdate
  (JNIEnv *env, jclass obj, jlong counter, jintArray jintArray, jint intTail, jdoubleArray jdoubleArray, jint doubleTail, jfloatArray jfloatArray, jint floatTail,jlongArray jlongArray, jint longTail, jcharArray jcharArray, jint charTail,jbyteArray jbyteArray, jint byteTail){
	int intArray[ArrayLen];
	double doubleArray[ArrayLen];
	float floatArray[ArrayLen];
	char charArray[ArrayLen];
	long longArray[ArrayLen];
	char byteArray[ArrayLen];
	
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);

	jdouble *body_d = env->GetDoubleArrayElements(jdoubleArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		doubleArray[i] = body_d[i];
	}
	env->ReleaseDoubleArrayElements(jdoubleArray, body_d, 0);

	jfloat *body_f = env->GetFloatArrayElements(jfloatArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		floatArray[i] = body_f[i];
	}
	env->ReleaseFloatArrayElements(jfloatArray, body_f, 0);

	jlong *body_l = env->GetLongArrayElements(jlongArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		longArray[i] = body_l[i];
	}
	env->ReleaseLongArrayElements(jlongArray, body_l, 0);
	
	jchar *body_c = env->GetCharArrayElements(jcharArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		charArray[i] = body_c[i];
	}
	env->ReleaseCharArrayElements(jcharArray, body_c, 0);
	
	jbyte *body_b = env->GetByteArrayElements(jbyteArray, 0);
	for (int i=0; i<ArrayLen; i++)
	{
		byteArray[i] = body_b[i];
	}
	env->ReleaseByteArrayElements(jbyteArray, body_b, 0);	

	if(sgx_use_flag!=1){printf("not init yet");return -12;}

	int rei=999;
	sgx_status_t ret=encall_switch_type_i(global_eid,&rei,counter,intArray,intTail,
			doubleArray,doubleTail,
			floatArray,floatTail,
			charArray,charTail,
			longArray,longTail,
			byteArray,byteTail);
	if(ret != SGX_SUCCESS){
		print_error_message(ret);
	}else{
		return 1;
	}
	return 0;
}

JNIEXPORT jint JNICALL Java_invoker_sgx_1invoker_initValue
  (JNIEnv *env, jclass obj, jintArray jintArray, jint intTail){
	
	int intArray[ArrayLen];
	jint *body_i = env->GetIntArrayElements(jintArray, 0);
	for (int i=0; i<intTail; i++)
	{
		intArray[i] = body_i[i];
	}
	env->ReleaseIntArrayElements(jintArray, body_i, 0);
	encall_varible(global_eid,intArray,intTail);
	return 1;
}




int SGX_CDECL main(int argc, char *argv[])
{

initialize_enclave();

    int int_array[100] = {0,1,2,3,4,5,6,7,8};
    long long_array[100] = {0,1,2,3,4,5,6,7,8};
    double double_array[100] = { 0.1,1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1 };
    float float_array[100] = { 0.1,1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1 };
    char char_array[100] = {'a','a','c','d','e','f','g','h','i','j'};
    char byte_array[100] = {'0','1','2','3','4','5','6','7','8','9'}; 

int k[] = {10,10,10,10,10,10,10};
int re;
encall_table_load(global_eid,&re);
printf("encall_table_load is ok!!!\n");
encall_varible(global_eid,k,7);
int re_i=999;
double re_d=0.0;
char re_c=' ';

encall_switch_type_c(global_eid,&re_c,0,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_c=%c\n",re_c);
encall_switch_type_i(global_eid,&re_i,1,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i1=%d\n",re_i);
encall_switch_type_i(global_eid,&re_i,2,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i2=%d\n",re_i);
encall_switch_type_i(global_eid,&re_i,3,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i3=%d\n",re_i);
encall_switch_type_i(global_eid,&re_i,4,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i4=%d\n",re_i);
encall_switch_type_i(global_eid,&re_i,5,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i5=%d\n",re_i);
encall_switch_type_i(global_eid,&re_i,6,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
//printf("re_i6=%d\n",re_i);

for(int i=1;i<10;i++){
	encall_switch_type_i(global_eid,&re_i,i,int_array,10,double_array,10,float_array,10,char_array,10,long_array,10,byte_array,10);
}

destroy_enclave();

return 0;
}
