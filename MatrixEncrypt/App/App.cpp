#include <stdio.h>
#include <string.h>
#include <assert.h>

# include <unistd.h>
# include <pwd.h>
# define MAX_PATH FILENAME_MAX

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"

#include<fstream>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<fcntl.h>
#define MAX 1000000

#define FILEPATH2 "/home/bob/Desktop/controlflow.3/func_call_va/func_call_v3.14/App/matrix/myfile"

#define FILEPATH "/home/bob/Desktop/SGXindex"
using namespace std;
/* OCall functions */
void ocall_print_string(const char *str)
{
	/* Proxy/Bridge will check the length and null-terminate 
	 * the input string to prevent buffer overflow. 
	 */
	printf("out==%s\n", str);
}

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
	if(argc!=4){
	printf("input error\n");
	exit(0);	
	}

	char* filepath=argv[1];
	char* key_src=argv[2];
	char* output=argv[3];
//standerlize key size as 16
	char key_t[16]={'0'};
	strncpy(key_t,key_src,strlen(key_src));
	for(int i=strlen(key_src);i<=16;i++){
		key_t[i]='0';
	}

	/* Initialize the enclave */
	unsigned char us[MAX];
	memset(us,0,MAX);
	if(initialize_enclave() < 0){
		printf("Enter a character before exit ...\n");
		getchar();
		return -1; 
	}

	int r=0;
	using namespace std;
	// int len_in=strlen(input);
	// ecall_ctr_encrypt(global_eid,&r,input,key_t,&ret[0]);
	
	FILE *fp;
	FILE *fp2;
/*
	if((fp=fopen(output,"ab+"))==NULL){
		printf("2 f open error");
		exit(0);	
	}
	if((fp2=fopen(filepath,"rb"))==NULL){
		printf("3 f open error");
		exit(0);	
	}
*/
	ifstream fin(filepath,ios::in|ios::binary);
	ofstream fout(output,ios::trunc|ios::out|ios::binary);
	
	if(fin.peek()==EOF){
		cout<<"empty path"<<endl;
	}

	unsigned char cr=10;
	long loop=1;
	long k=0;
	while(!fin.eof()){

		if(loop%1000==0){
		sgx_destroy_enclave(global_eid);
		if(initialize_enclave() < 0){
		printf("Enter a character before exit ...\n");
		getchar();
		return -1; 
		}
		}
		loop++;
		char c;
		fin.get(c);
		//cout<<c;
		us[k]=(unsigned char)c;
		k++;
		if(k%64==0){
			//printf();
			us[k]=0;
			k=0;
			unsigned char out[MAX];
			memset(out,0,MAX);
			ecall_ctr_encrypt(global_eid,&r,(const char*)us,key_t,&out[0]);
			printf("\nencryption response loop:%ld\n",k/64);
			for(int i=0;i<64;i++){
				fout<<out[i];
				printf("%02x",out[i]);
			}
			memset(us,0,MAX);
		}
	}
	if(k%64!=0){
		us[k]=0;
		unsigned char out[MAX];
		memset(out,0,MAX);
		ecall_ctr_encrypt(global_eid,&r,(const char*)us,key_t,&out[0]);
		printf("\nencryption response:%d\n",r);
		for(int i=0;i<k;i++){
			fout<<out[i];
			printf("%02x",out[i]);
		}
		memset(us,0,MAX);
	}

//--------encrypt
//	ecall_ctr_encrypt(global_eid,&r,(const char*)us,key_t,&out[0]);
//	printf("\nencryption response:%d\n",r);
//	for(int i=0;i<k;i++){
//	//write
//		fout<<out[i];
//		printf("%02x",out[i]);
//	}


	fout.close();
	//ifstream reout(output,ios::in|ios::binary);
	int reout=open(output,O_RDONLY);
//------------read out
	long l=0;
	unsigned char sss[MAX];
	memset(sss,0,MAX);
	//while(!reout.eof()){
	long loop2=1;
	while(1){
		char c;
		loop2++;
		if(loop2%1000==0){
/*
		sgx_destroy_enclave(global_eid);
		if(initialize_enclave() < 0){
		printf("Enter a character before exit ...\n");
		getchar();
		return -1; 
		}*/
		//sleep(0);
		}
		//reout.get(c);
		if(read(reout,&c,1)==0){
			break;
		}
		
		sss[l]=(unsigned char)c;
		l++;
		if(l%64==0){
			sss[l]=0;
			
			unsigned char ppp[MAX];
			memset(ppp,0,MAX);
			printf("\ndecryption response loop:%ld\n",l/64);
			ecall_ctr_decrypt(global_eid,&r,sss,key_t,ppp,64);
			for(int i=0;i<l;i++){
				printf("%c",ppp[i]);
			}
			l=0;
		}
	}
	if(l%64!=0){
		sss[l]=0;
		unsigned char ppp[MAX];
		memset(ppp,0,MAX);
		printf("\ndecryption response loop:%ld\n",l/64);
		ecall_ctr_decrypt(global_eid,&r,sss,key_t,ppp,l);
		for(int i=0;i<l;i++){
		printf("%c",ppp[i]);
		}
		l=0;
	}


//--------------
/*
	unsigned char ppp[MAX];
	memset(ppp,0,MAX);
	printf("\ndecryption response:%d\n",r);
	ecall_ctr_decrypt(global_eid,&r,sss,key_t,ppp,k);
	for(int i=0;i<k;i++){
		printf("%02x",ppp[i]);
	}
*/

	printf("destroy\n");
	char *ss="ss";
	r=999;
	//encall_test(global_eid,&r,output);
	printf("loop=%ld\n",loop);
	sgx_destroy_enclave(global_eid);
	return 0;
}

