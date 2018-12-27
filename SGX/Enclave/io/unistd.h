/* unisted.h */
#ifndef __VFS_UNISTED_H
#define __VFS_UNISTED_H

#include "user_types.h"

#define SEEK_SET  	0
#define SEEK_CUR  	1
#define SEEK_END	2	
#ifdef __cplusplus
extern "C" {
#endif

extern int stdin, stdout, stderr;

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

int close(int fd);

int fchown(int fd, uid_t owner, gid_t group);
char *getcwd(char *buf, size_t size);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
int access(const char* pathname, int mode) ;
int unlink(const char *pathname);
int rmdir(const char *pathname);
uid_t geteuid(void);
//uid_t getuid(void);
off_t lseek(int fd, off_t offset, int whence);
int fsync(int fd);
pid_t getpid(void);
unsigned int sleep(unsigned int seconds);


#ifdef __cplusplus
}
#endif

#endif