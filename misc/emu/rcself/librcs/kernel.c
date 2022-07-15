#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef UNIX
#define _XOPEN_SOURCE 500
#ifdef SOLARIS
#undef _XOPEN_SOURCE
#endif
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef WIN32
#include <direct.h>
#include <io.h>
#include <time.h>
#endif

#include "librcs.h"

int rcs_chdir(const char* path) {
  return chdir(path);
  }

int rcs_chown(const char* path,uid_t owner,gid_t group) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return chown(path,owner,group);
#endif
  }

int rcs_chroot(const char* path) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return chroot(path);
#endif
  }

int rcs_close(int filedes) {
  return close(filedes);
  }

int rcs_dup(int filedes) {
  return dup(filedes);
  }

int rcs_fchown(int filedes,uid_t owner,gid_t group) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return fchown(filedes,owner,group);
#endif
  }

int rcs_fchroot(int filedes) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return 0;
#endif
  }

gid_t rcs_getegid(void) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return getegid();
#endif
  }

uid_t rcs_geteuid(void) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return geteuid();
#endif
  }

void rcs_getFullName(char* buffer) {
#ifdef WIN32
  strcpy(buffer,"User");
#endif
#ifdef UNIX
  struct passwd *puser;
  puser=getpwuid(getuid());
  strcpy(buffer,puser->pw_gecos);
#endif
  }

void rcs_getHomeDir(char* buffer) {
#ifdef WIN32
  buffer[0]=0;
#endif
#ifdef UNIX
  struct passwd *puser;
  puser=getpwuid(getuid());
  strcpy(buffer,puser->pw_dir);
#endif
  }

gid_t rcs_getgid(void) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return getgid();
#endif
  }

uid_t rcs_getuid(void) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return getuid();
#endif
  }

int rcs_kill(pid_t pid,int sig) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return kill(pid,sig);
#endif
  }


int rcs_lchown(const char* path,uid_t owner,gid_t group) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return lchown(path,owner,group);
#endif
  }

int rcs_link(const char* existing,const char* nw) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return link(existing,nw);
#endif
  }

off_t rcs_lseek(int filedes,off_t offset,int whence) {
  return lseek(filedes,offset,whence);
  }

int rcs_nice(int incr) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return nice(incr);
#endif
  }

int rcs_open(const char* path,int oflag,mode_t mode) {
  return open(path,oflag,mode);
  }

size_t rcs_pread(int filedes,void* buf,size_t nbyte,off_t offset) {
#ifdef WIN32
  off_t orig;
  int   status;
  orig=lseek(filedes,offset,SEEK_SET);
  status=read(filedes,buf,nbyte);
  lseek(filedes,orig,SEEK_SET);
  return status;
#endif
#ifdef MSDOS
  off_t orig;
  int   status;
  orig=lseek(filedes,offset,SEEK_SET);
  status=read(filedes,buf,nbyte);
  lseek(filedes,orig,SEEK_SET);
  return status;
#endif
#ifdef UNIX
  return pread(filedes,buf,nbyte,offset);
#endif
  }

size_t rcs_pwrite(int filedes,void* buf,size_t nbyte,off_t offset) {
#ifdef WIN32
  off_t orig;
  int   status;
  orig=lseek(filedes,offset,SEEK_SET);
  status=write(filedes,buf,nbyte);
  lseek(filedes,orig,SEEK_SET);
  return status;
#endif
#ifdef MSDOS
  off_t orig;
  int   status;
  orig=lseek(filedes,offset,SEEK_SET);
  status=write(filedes,buf,nbyte);
  lseek(filedes,orig,SEEK_SET);
  return status;
#endif
#ifdef UNIX
  return pwrite(filedes,buf,nbyte,offset);
#endif
  }

size_t rcs_read(int filedes,void* buf,size_t nbyte) {
  return read(filedes,buf,nbyte);
  }

int rcs_rename(const char* old,const char* nw) {
  return rename(old,nw);
  }

int rcs_rmdir(const char* path) {
  return rmdir(path);
  }

int rcs_setegid(gid_t gid) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return setegid(gid);
#endif
  }

int rcs_seteuid(uid_t uid) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return seteuid(uid);
#endif
  }

int rcs_setgid(gid_t gid) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return setgid(gid);
#endif
  }

int rcs_setuid(uid_t uid) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return setuid(uid);
#endif
  }

void rcs_sync(void) {
#ifdef WIN32
  return;
#endif
#ifdef MSDOS
  return;
#endif
#ifdef UNIX
  sync();
#endif
  }

time_t rcs_time() {
#ifdef UNIX
  struct timeval t;
  gettimeofday(&t,NULL);
  return t.tv_sec*1000 + (t.tv_usec/1000);
#endif
#ifdef WIN32
  return time(NULL)*1000;
#endif
  }

mode_t rcs_umask(mode_t cmask) {
#ifdef WIN32
  return 0;
#endif
#ifdef MSDOS
  return 0;
#endif
#ifdef UNIX
  return umask(cmask);
#endif
  }

int rcs_unlink(const char* path) {
  return unlink(path);
  }

size_t rcs_write(int filedes,void* buf,size_t nbyte) {
  return write(filedes,buf,nbyte);
  }

