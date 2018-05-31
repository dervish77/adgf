#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "librcs.h"
#include <fcntl.h>

VMEM rcs_newVmem(char* filename,long size) {
  VMEM ret;
  byte i;
  ret.file=rcs_open(filename,O_CREAT,0);
  if (ret.file<0) ret.status=-1; else ret.status=0;
  if (ret.status<0) return ret;
  rcs_lseek(ret.file,size,SEEK_SET);
  rcs_write(ret.file,&i,1);
  return ret;
  }

VMEM rcs_openVmem(char* filename) {
  VMEM ret;
  ret.file=rcs_open(filename,O_RDWR | O_CREAT,0);
  if (ret.file<0) ret.status=-1; else ret.status=0;
  return ret;
  }

long rcs_sizeVmem(VMEM* vmem) {
  return rcs_lseek(vmem->file,0,SEEK_END);
  }

int rcs_closeVmem(VMEM* vmem) {
  vmem->status=rcs_close(vmem->file);
  return vmem->status;
  }

size_t rcs_readVmem(VMEM* vmem,void* buffer,long address,size_t length){
  off_t offset;
  offset=rcs_lseek(vmem->file,address,SEEK_SET);
  if (offset == -1) return offset;
  return rcs_read(vmem->file,buffer,length);
  }

size_t rcs_writeVmem(VMEM* vmem,void* buffer,long address,size_t length){
  off_t offset;
  offset=rcs_lseek(vmem->file,address,SEEK_SET);
  if (offset == -1) return offset;
  return rcs_write(vmem->file,buffer,length);
  }


