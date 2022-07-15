#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "librcs.h"

int rcs_getNonOption(int start,int argc,char* argv[]) {
  int i;
  i=start+1;
  while (i<argc) {
    if (argv[i][0] != '-') return i;
    i++;
    }
  return -1;
  }

int rcs_getOption(char* option,int argc,char* argv[]) {
  int i;
  i=1;
  while (i<argc) {
    if (strncmp(option,argv[i],strlen(option))==0) return i;
    i++;
    }
  return -1;
  }

