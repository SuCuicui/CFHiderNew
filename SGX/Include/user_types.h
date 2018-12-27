/* User defined types */


#ifndef __SGX_USER_TYPES_H
#define __SGX_USER_TYPES_H

#include <sys/types.h>
#include <time.h>
/*##################Before Coding... (VERY IMPORTANT)###################
-----This is just a TRADEOFF to solve the proble of using some definitions only in Enclave environment facing EDL file.
-----In file /opt/intel/sgxsdk/include/tlibc/sys/types.h 
-----after
#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_
-----add a newline
#define __VIVI_SGX_IN_ENCLAVE__
##################Before Coding... (VERY IMPORTANT)###################*/
#ifdef __VIVI_SGX_IN_ENCLAVE__
//Very Important:  Here, we use those definitions below only in Enclave environment. Please Refer to info.txt.
struct timeval{
	long tv_sec;
	long tv_usec;
};
 struct timezone
 {
 	int tz_minuteswest;
 	int tz_dsttime;
 };

//for fcntl.h
struct flock{
	short	l_type;
	short	l_whence;
	long	l_start;
	long	l_len;
	int		l_pid;
	//__ARCH_FLOCK_PAD
};


//for stat.h

typedef unsigned int mode_t;

typedef unsigned int uid_t;
typedef unsigned int gid_t;

typedef unsigned long dev_t;
typedef unsigned long ino_t;
typedef unsigned long nlink_t;

typedef long blksize_t;
typedef long blkcnt_t;
typedef long long syscall_slong_t ;
//typedef long long __syscall_slong_t ;

struct timespec {
    time_t tv_sec;
    syscall_slong_t tv_nsec;
};

struct stat {
    dev_t st_dev;
    ino_t st_ino;
    nlink_t st_nlink;
    mode_t st_mode;
    uid_t st_uid;
    gid_t st_gid;
    int __pad0;
    dev_t st_rdev;
    off_t st_size;
    blksize_t st_blksize;
    blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    syscall_slong_t __glibc_reserved[3];
};

typedef int pid_t;

#else
//#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#endif /*  _SGX_EDGER8R_H_  */

#endif

