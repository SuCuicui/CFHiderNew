#ifndef __VFS_STAT_H
#define __VFS_STAT_H

#include "user_types.h"

//typedef long long syscall_slong_t ;
//typedef long long time_t;

/*----------------#include <bits/stat.h>------------------------*/
/* Encoding of the file mode.  */
#define __S_IFMT    0170000 /* These bits determine file type.  */

/* File types.  */
#define __S_IFDIR   0040000 /* Directory.  */
#define __S_IFCHR   0020000 /* Character device.  */
#define __S_IFBLK   0060000 /* Block device.  */
#define __S_IFREG   0100000 /* Regular file.  */
#define __S_IFIFO   0010000 /* FIFO.  */
#define __S_IFLNK   0120000 /* Symbolic link.  */
#define __S_IFSOCK  0140000 /* Socket.  */


/* Protection bits.  */

#define	__S_ISUID	04000	/* Set user ID on execution.  */
#define	__S_ISGID	02000	/* Set group ID on execution.  */
#define	__S_ISVTX	01000	/* Save swapped text after use (sticky).  */
#define	__S_IREAD	0400	/* Read by owner.  */
#define	__S_IWRITE	0200	/* Write by owner.  */
#define	__S_IEXEC	0100	/* Execute by owner.  */


/*----------------#include <sys/stat.h>------------------------*/
#define __S_ISTYPE(mode, mask)  (((mode) & __S_IFMT) == (mask))

#define S_ISDIR(mode)    __S_ISTYPE((mode), __S_IFDIR)

#define	S_IRUSR	__S_IREAD	/* Read by owner.  */
#define	S_IWUSR	__S_IWRITE	/* Write by owner.  */
#define	S_IXUSR	__S_IEXEC	/* Execute by owner.  */
/* Read, write, and execute by owner.  */
#define	S_IRWXU	(__S_IREAD|__S_IWRITE|__S_IEXEC)

#define	S_IRGRP	(S_IRUSR >> 3)	/* Read by group.  */
#define	S_IWGRP	(S_IWUSR >> 3)	/* Write by group.  */
#define	S_IXGRP	(S_IXUSR >> 3)	/* Execute by group.  */
/* Read, write, and execute by group.  */
#define	S_IRWXG	(S_IRWXU >> 3)

#define	S_IROTH	(S_IRGRP >> 3)	/* Read by others.  */
#define	S_IWOTH	(S_IWGRP >> 3)	/* Write by others.  */
#define	S_IXOTH	(S_IXGRP >> 3)	/* Execute by others.  */
/* Read, write, and execute by others.  */
#define	S_IRWXO	(S_IRWXG >> 3)

#ifdef __cplusplus
extern "C" {
#endif

//some global variables used in fcntl.h
//some functions' declaration used in fcntl.h
int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
int fchmod(int fd, mode_t mode);
int mkdir(const char *pathname, mode_t mode);
#ifdef __cplusplus
}
#endif

#endif