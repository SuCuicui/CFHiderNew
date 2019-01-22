#include "../App.h"
#include "Enclave_u.h"

#include<fstream>
#include<iomanip>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>



using namespace std;

/* OCall functions */
int in_flag=0;
void ocall_file_write(char* file,char* buf,int len)
{
    ofstream ofile;
    ofile.open(file);
	if(! ofile.is_open()){
	cout<<"open failure in writing"<<endl;
	}
    ofile<<buf<<endl;
    ofile.close();
}
//     ocall_file_add
void ocall_file_add(char* file,char* buf,int len)
{
    ofstream ofile;
    ofile.open(file,ios::app);
	if(! ofile.is_open()){
	cout<<"open failure in writing"<<endl;
	}
    ofile<<buf<<endl;
    ofile.close();
}
//error -6 unrecognised matrix meta;


void ocall_file_getline(char* file,char* buf,long* line_num)
{
		char* buffer=(char*)malloc(sizeof(char)*50);  
		ifstream ifile(file);  
		if (! ifile.is_open())  
		{
			cout << "Error opening file"<<endl;
			exit (1);
		} 
		long line=0;
		int count=0;
		while (!ifile.eof() )  
		{
			
			if(line<*line_num){
				ifile.getline (buffer,50);
				line++;
				continue;
			}
			ifile.getline(buffer,50);
			memcpy(buf,buffer,50);
			break;
		}
		ifile.close();
}


void ocall_file_read(char* file,int* buf,long* start)
{
		char* buffer=(char*)malloc(sizeof(char)*50);  
		memset(buffer,0,50);
		FILE* fp=fopen(file,"r");
		if (fp==NULL)  
		{
			cout << file <<endl;
			cout << "Error opening file in read"<<endl;
			exit (1);
		} 
		long line=0;
		int count=0;
		int eof_flag=0;
		while (!feof(fp))  
		{
			
			if(line<*start){
				//ifile.getline (buffer,100);
				//======get line===========
				for(int k=0;k<50;k++){
					if(fread(&buffer[k],sizeof(char),1,fp)<=0){
						eof_flag=1;
						break;
					}

					if(buffer[k]=='\n'){
						buffer[k]='\0';
						break;
					}
				}
				//==========end============
				line++;
				continue;
			}
			if(line==*start+READ_MAX){
				*start=line;
				break;
			}
			memset(buffer,'\0',50);
			//ifile.getline (buffer,100);
			//=========get line=========
			for(int k=0;k<50;k++){
				if(fread(&buffer[k],sizeof(char),1,fp)<=0){
					eof_flag=1;
					break;
				}
				//printf("TT:%c\n",buffer[k]);
				if(buffer[k]=='\n'){
					buffer[k]='\0';
					break;
				}
			}
			//==========================
			int read_num=0;
			//----------new version----
			int load_flagh=-998;
			int buffer_len=strlen(buffer);
			//printf("");
			encall_read_line(global_eid,&load_flagh,buffer,buffer_len,line);
			if(load_flagh!=0){printf("readline error");}
			//----------old version--------
			// if(*buffer<48||*buffer>57){//not number
			// 	int in_flag=999;
			// 	read_num=0-line;
			// 	int load_flagh=-998;
			// 	encall_hash_readin(global_eid,&load_flagh,buffer,line);
			// 	printf("readin_flag=%d\n",load_flagh);
			// }else{
			// read_num=atoi(buffer);
			// }
			// *(buf+count)=read_num;

			//----------end----------
			count++;
			line++;
		}
		fclose(fp);
		*start=line;
}

void ocall_print_string(const char *str)
{
    printf("%s", str);
}
void ocall_print_int(int str)
{
    printf("%d\n", str);
}
void ocall_print_long(long str)
{
    printf("%ld\n", str);
}
