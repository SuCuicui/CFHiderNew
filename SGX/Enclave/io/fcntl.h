/* fcntl.h */
#ifndef __VFS_FCNTL_H
#define __VFS_FCNTL_H

#include "user_types.h"

#ifndef _INC_FCNTL
#	define _INC_FCNTL

/* open/fcntl.  */
#	define O_ACCMODE	   0003
#	define O_RDONLY	     00
#	define O_WRONLY	     01
#	define O_RDWR		     02
#	ifndef O_CREAT
# 		define O_CREAT	   0100	/* Not fcntl.  */
#	endif
#	ifndef O_EXCL
#		define O_EXCL		   0200	/* Not fcntl.  */
#	endif
#	ifndef O_NOCTTY
# 		define O_NOCTTY	   0400	/* Not fcntl.  */
#	endif
#	ifndef O_TRUNC
# 		define O_TRUNC	  01000	/* Not fcntl.  */
#	endif
#	ifndef O_APPEND
# 		define O_APPEND	  02000
#	endif
#	ifndef O_NONBLOCK
# 		define O_NONBLOCK	  04000
#	endif
#	ifndef O_NDELAY
# 		define O_NDELAY	O_NONBLOCK
#	endif
#	ifndef O_SYNC
# 		define O_SYNC	       04010000
#	endif
#	define O_FSYNC		O_SYNC
#	ifndef O_ASYNC
# 		define O_ASYNC	 020000
#	endif
#	ifndef __O_LARGEFILE
# 		define __O_LARGEFILE	0100000
#	endif

#	ifndef __O_DIRECTORY
# 		define __O_DIRECTORY  0200000
#	endif
#	ifndef __O_NOFOLLOW
# 		define __O_NOFOLLOW	0400000
#	endif
#	ifndef __O_CLOEXEC
# 		define __O_CLOEXEC   02000000
#	endif
#	ifndef __O_DIRECT
# 		define __O_DIRECT	 040000
#	endif
#	ifndef __O_NOATIME
# 		define __O_NOATIME   01000000
#	endif
#	ifndef __O_PATH
# 		define __O_PATH     010000000
#	endif
#	ifndef __O_DSYNC
# 		define __O_DSYNC	 010000
#	endif
#	ifndef __O_TMPFILE
# 		define __O_TMPFILE   020200000
#	endif

#endif

#define 	F_GETFD  1
#define 	F_SETFD  2
#define 	F_GETLK  5
#define 	F_SETLK  6


#define F_WRLCK  1
#define F_UNLCK  2
#define F_RDLCK  0
#define F_OK  0
#define R_OK  4
#define W_OK  2

#ifdef __cplusplus
extern "C" {
#endif

int open(const char *pathname, int flags, mode_t mode);

int fallocate(int fd, int mode, off_t offset, off_t len);
int fcntl(int fd, int cmd, ... /* arg */ );

#ifdef __cplusplus
}
#endif

#endif