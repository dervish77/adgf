#include <stdio.h>
#ifdef WIN32
#include <io.h>
#else
#include <stdlib.h>
#include <unistd.h>
#endif
#include <sys/stat.h>

int rcs_exist(char* filename) {
  FILE *file;
  if ((file=fopen(filename,"r"))==NULL) return 0;
  fclose(file);
  return -1;
  }

long rcs_numRecords(int fdes,int reclen) {
  struct stat data;
  fstat(fdes,&data);
  return data.st_size/reclen;
  }

void rcs_shiftFile(long offset,long shift,int fdes) {
  long fileSize;
  char buffer[4096];
  long currentPos;
  long segSize;
  fileSize=rcs_numRecords(fdes,1);
  if (shift>=0) {
    currentPos=fileSize;
    while (currentPos>offset) {
      segSize=(currentPos-offset>=4096) ? 4096 : currentPos-offset;
      if (segSize==0) return;
      currentPos-=segSize;
      lseek(fdes,currentPos,SEEK_SET);
      read(fdes,buffer,segSize);
      lseek(fdes,currentPos+shift,SEEK_SET);
      write(fdes,buffer,segSize);
      }
    } else {
    shift=-shift;
    currentPos=offset;
    while (currentPos<fileSize) {
      segSize=(fileSize-currentPos>4096) ? 4096 : fileSize-currentPos;
      if (segSize==0) return;
      lseek(fdes,currentPos+shift,SEEK_SET);
      read(fdes,buffer,segSize);
      lseek(fdes,currentPos,SEEK_SET);
      write(fdes,buffer,segSize);
      currentPos+=segSize;
      }
#ifdef UNIX
    ftruncate(fdes,fileSize-shift);
#else
    chsize(fdes,fileSize-shift);
#endif
    }
  }

