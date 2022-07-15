#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "librcs.h"

XML_NODE* rcs_xmlNew(char* n) {
  XML_NODE* ret;
  ret=(XML_NODE*)malloc(sizeof(XML_NODE));
  if (ret == NULL) return ret;
  ret->name=(char*)malloc(sizeof(n)+1);
  if (ret->name == NULL) {
    free(ret);
    return NULL;
    }
  strcpy(ret->name,n);
  ret->elements=NULL;
  ret->numElements=0;
  return ret;
  }

int rcs_xmlAddNode(XML_NODE* node,char* path,char** symbols) {
  char* next;
  next=strchr(path,'.');
  if (next == NULL) {
    } else {
    }
  }

