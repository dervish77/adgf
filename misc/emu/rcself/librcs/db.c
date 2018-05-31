#include <stdio.h>
#ifdef WIN32
#include <io.h>
#else
#include <stdlib.h>
#include <unistd.h>
#endif
#include "librcs.h"

int rcs_compareKey(int keyfile,long keylen,long pos,rcs_key sKey,char typ) {
  rcs_key  key;
  lseek(keyfile,pos*keylen,SEEK_SET); read(keyfile,&key,keylen);
  if (typ!='N' && strcmp(key.data.skey,sKey.data.skey)==0) return 0;
  if (typ!='N' && strcmp(key.data.skey,sKey.data.skey)>=0) return 1;
  if (typ=='N' && key.data.lkey==sKey.data.lkey) return 0;
  if (typ=='N' && key.data.lkey>=sKey.data.lkey) return 1;
  return -1;
  }

long rcs_findKey(int keyfile,long keylen,rcs_key sKey,char typ) {
  long pos;
  long records;
/*  rcs_key  key; */
  long lo,hi,next;
  int  loc,hic,nextc;
  char found;
  records=rcs_numRecords(keyfile,keylen);
  lo=0; hi=records-1;
  loc=rcs_compareKey(keyfile,keylen,lo,sKey,typ);
  if (loc>=0) return 0;
  hic=rcs_compareKey(keyfile,keylen,hi,sKey,typ);
  if (hic<0) return hi+1;
  pos=0; found='N';
  next=lo+(hi-lo)/2;
  while (found!='Y') {
    nextc=rcs_compareKey(keyfile,keylen,next,sKey,typ);
    if (nextc>=0) {
      hic=nextc;
      hi=next;
      next=lo+(hi-lo)/2;
      }
    else if (nextc<0) {
      loc=nextc;
      lo=next;
      next=lo+(hi-lo)/2;
      }
    if (lo==hi || lo==hi-1) found='Y';
    }
  if (loc<0) next=lo+1; else next=lo;
  if (next>records) next=records;
  return next;
  }

void rcs_deleteKey(int fdes,long recnum,long keylen) {
  rcs_key key;
  long offset;
  while (read(fdes,&key,keylen) != 0) {
    if (key.recNum == recnum) {
      offset=lseek(fdes,0,SEEK_CUR)-keylen;
      rcs_shiftFile(offset,-keylen,fdes);
      return;
      }
    }
  return;
  }

void rcs_insertKey(int fdes,rcs_key key,long keylen,char typ) {
  long records;
/*  long pos,i; */
  long pos;
/*  char found; */
/*  rcs_key  fileKey; */
  records=rcs_numRecords(fdes,keylen);
  if (records==0) pos=0;
    else {
      pos=rcs_findKey(fdes,keylen,key,typ);
      }
  rcs_shiftFile(pos*keylen,keylen,fdes);
  lseek(fdes,pos*keylen,SEEK_SET);
  write(fdes,&key,keylen);
  }

void rcs_adjustKeys(int fdes,long record,long keylen) {
  rcs_key key;
  long records;
  long pos;
  records=rcs_numRecords(fdes,keylen);
  for (pos=0;pos<records;pos++) {
    lseek(fdes,pos*keylen,SEEK_SET);
    read(fdes,&key,keylen);
    if (key.recNum>=record) {
      key.recNum--;
      lseek(fdes,pos*keylen,SEEK_SET);
      write(fdes,&key,keylen);
      }
    }
  }

