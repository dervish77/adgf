#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "librcs.h"

int rcs_loadStrings(char* fname,char*** stringTable) {
  int max;
  int n;
  FILE* infile;
  char  buffer[256];
  char* pBuffer;
  max=-1;
  if ((infile=fopen(fname,"r")) == NULL) return -1;
  while (fgets(buffer,255,infile) != NULL) {
    sscanf(buffer,"%d",&n);
    pBuffer=rcs_nextWord(buffer);
    if (max == -1) {
      *stringTable=(char**)malloc(sizeof(char*) * (n+1));
      max=n;
      } else if (n > max) {
      *stringTable=(char**)realloc(*stringTable,sizeof(char*) * (n+1));
      max=n;
      }
    (*stringTable)[n]=(char*)malloc(strlen(pBuffer)+1);
    strcpy((*stringTable)[n],pBuffer);
    }
  return 0;
  }

char* rcs_nextWord(char* ptr) {
  while (*ptr > ' ') ptr++;
  while (*ptr == ' ') ptr++;
  return ptr;
  }

char* rcs_trimLineEndings(char* ptr) {
  while (*(ptr+strlen(ptr)-1)<32 && *(ptr+strlen(ptr)-1)>0)
    *(ptr+strlen(ptr)-1)=0;
  return ptr;
  }

char* rcs_trimRight(char* ptr) {
  while (*(ptr+strlen(ptr)-1)<33 && *(ptr+strlen(ptr)-1)>0)
    *(ptr+strlen(ptr)-1)=0;
  return ptr;
  }
  
char* rcs_trimLeft(char* ptr) {
  while (*ptr == ' ') ptr++;
  return ptr;
  }

char* rcs_trim(char* ptr) {
  return rcs_trimLeft(rcs_trimRight(ptr));
  }

char* rcs_getWord(char* dest,char* src) {
  while (*src > ' ') *dest++ = *src++;
  *dest=0;
  return src;
  }
