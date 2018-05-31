#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"

byte boot[256] = { 0x90,0xb3,0xf8,0x06,0xa3,0xd3,0xf8,0xff,
                   0xb4,0xf8,0xe0,0xa4,0xf8,0xff,0xb5,0xf8,
                   0xf1,0xa5,0xf8,0x00,0xb2,0xf8,0xf0,0xa2,
                   0xf8,0x01,0xa7,0xf8,0x03,0xbf,0xf8,0x00,
                   0xaf,0xe2,0x87,0x52,0x64,0x22,0x73,0xf8,
                   0x00,0xb7,0xa8,0xf8,0xe0,0xb8,0xd4,0xff,
                   0x3c,0x60,0x72,0xa7,0x17,0x87,0xff,0x0f,
                   0x3a,0x22,0xf8,0x03,0xb0,0xf8,0x00,0xa0,
                   0xd0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


void uc(char* buffer) {
  int i;
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i]>='a' && buffer[i]<='z') buffer[i]-=32;
  }

word exchg(word x) {
  return ((x & 0xff) << 8) | ((x >> 8) & 0xff);
  }

void read_sector(SECTOR* sector,long secnum) {
  lseek(disk_file,secnum*512,SEEK_SET);
  read(disk_file,sector,512);
  }

void write_sector(SECTOR* sector,long secnum) {
  lseek(disk_file,secnum*512,SEEK_SET);
  write(disk_file,sector,512);
  }

word read_lump(word lump) {
  long sec;
  word off;
  sec = (lump / 256) + 17;
  off = (lump % 256) * 2;
  read_sector(&sector,sec);
  return sector.data[off]*256 + sector.data[off+1];
  }

void write_lump(word lump,word value) {
  long sec;
  word off;
  sec = (lump / 256) + 17;
  off = (lump % 256) * 2;
  read_sector(&sector,sec);
  sector.data[off] = value / 256;
  sector.data[off+1] = value % 256;
  write_sector(&sector,sec);
  }

void dirent_to_sector(SECTOR* sector,DIR_ENT* dirent,word offset) {
  int i;
  sector->data[offset++] = dirent->lump_hi / 256;
  sector->data[offset++] = dirent->lump_hi % 256;
  sector->data[offset++] = dirent->lump_lo / 256;
  sector->data[offset++] = dirent->lump_lo % 256;
  sector->data[offset++] = dirent->eof / 256;
  sector->data[offset++] = dirent->eof % 256;
  sector->data[offset++] = dirent->flags;
  sector->data[offset++] = dirent->flags2;
  sector->data[offset++] = dirent->date / 256;
  sector->data[offset++] = dirent->date % 256;
  sector->data[offset++] = dirent->time / 256;
  sector->data[offset++] = dirent->time % 256;
  for (i=0; i<21; i++) sector->data[offset++] = dirent->filename[i];
  }

void sector_to_dirent(SECTOR* sector,DIR_ENT* dirent,word offset) {
  int i;
  dirent->lump_hi = sector->data[offset++] << 8;
  dirent->lump_hi |= sector->data[offset++];
  dirent->lump_lo = sector->data[offset++] << 8;
  dirent->lump_lo |= sector->data[offset++];
  dirent->eof = sector->data[offset++] << 8;
  dirent->eof |= sector->data[offset++];
  dirent->flags = sector->data[offset++];
  dirent->flags2 = sector->data[offset++];
  dirent->date = sector->data[offset++] << 8;
  dirent->date |= sector->data[offset++];
  dirent->time = sector->data[offset++] << 8;
  dirent->time |= sector->data[offset++];
  for (i=0; i<21; i++) dirent->filename[i] = sector->data[offset++];
  }

FILDES open_master_dir() {
  word   lump;
  FILDES ret;
  read_sector(&sector,0);
  ret.current_sector = (sector.data[300] << 24) +
                       (sector.data[301] << 16) +
                       (sector.data[302] << 8) +
                        sector.data[303];
  ret.current_sector *= 8;
  ret.offset = 0;
  ret.eof = sector.data[304]*256 + sector.data[305];
  ret.dir_sector = 0;
  ret.dir_offset = 300;
  read_sector(&(ret.dta),ret.current_sector);
  lump = read_lump(ret.current_sector / 8);
  if (lump == 0xfefe) ret.flags = 4; else ret.flags = 0;
  return ret;
  }

long fs_seek(FILDES* fildes,long pos,int whence) {
  SECTOR sec;
  long relsec;
  long rellmp;
  long sector;
  long ret;
  word lump;
  ret = fildes->offset;
  if (whence == 0) {
    fildes->offset = pos;
    }
  if (whence == 1) {
    fildes->offset += pos;
    }
  relsec = fildes->offset >> 9;
  rellmp = relsec / 8;
  relsec = relsec % 8;
  read_sector(&sec,fildes->dir_sector);
  lump = ((sec.data[fildes->dir_offset+2]<<8) +
          sec.data[fildes->dir_offset+3]);
  while (rellmp > 0) {
    lump = read_lump(lump);
    rellmp--;
    }
  sector = lump * 8;
  sector += relsec;
  read_sector(&(fildes->dta),sector);
  fildes->current_sector = sector;
  lump = read_lump(lump);
  if (lump == 0xfefe) fildes->flags |= 4;
  return ret;
  }

word fs_read(byte* buffer,word len,FILDES* fildes) {
  word ret;
  word lump;
  ret = 0;
  while (len > 0) {
    if ((fildes->flags & 4) && ((fildes->offset & 0xfff) >= fildes->eof))
      return ret;
    *buffer++ = fildes->dta.data[fildes->offset & 0x1ff];
    fildes->offset += 1;
    len--;
    ret++;
    if ((fildes->offset & 0x1ff) == 0) {
      if (fildes->flags & 1)
        write_sector(&(fildes->dta),fildes->current_sector);
      if ((fildes->offset >> 9) % 8 != 0) {
        fildes->current_sector++;
        read_sector((&fildes->dta),fildes->current_sector);
        fildes->flags &= 0xfe;
        } else {
        lump = (fildes->current_sector/8);
        lump = read_lump(lump);
        fildes->current_sector = lump * 8;
        read_sector(&(fildes->dta),fildes->current_sector);
        lump = read_lump(lump);
        if (lump == 0xfefe) fildes->flags = 4; else fildes->flags = 0;
        }
      }
    }
  return ret;
  }

word allocate_lump() {
  long sec;
  word lump;
  int  i;
  lump = 0;
  sec = 17;
  lump = 0;
  while (1) {
    read_sector(&sector,sec);
    for (i=0; i<256; i++) {
      if (sector.data[i*2] == 0 && sector.data[i*2+1] == 0) return lump;
      lump++;
      }
    sec++;
    }
  return 0xffff;
  }

word append_lump(lump) {
  word lump2;
  lump2 = read_lump(lump);
  while (lump2 != 0xfefe) {
    lump = lump2;
    lump2 = read_lump(lump);
    }
  lump2 = allocate_lump();
  write_lump(lump,lump2);
  write_lump(lump2,0xfefe);
  return lump2;
  }

void fs_delete_chain(word lump) {
  word lump2;
  while (lump != 0xfefe) {
    lump2 = read_lump(lump);
    write_lump(lump,0);
    lump = lump2;
    }
  }

void fs_delete(DIR_ENT dirent,long dir_sec,word dir_ofs) {
  word lump;
  lump = dirent.lump_lo;
  fs_delete_chain(lump);
  dirent.lump_hi = 0;
  dirent.lump_lo = 0;
  read_sector(&sector,dir_sec);
  dirent_to_sector(&sector,&dirent,dir_ofs);
/*   sector.dir[dir_ofs/32] = dirent;  */
  write_sector(&sector,dir_sec);
  }

word fs_write(byte* buffer,word len,FILDES* fildes) {
  word ret;
  word lump;
  ret = 0;
  while (len > 0) {
    fildes->dta.data[fildes->offset & 0x1ff] = *buffer++;
    fildes->flags |= 1;
    ret++;
    len--;
    if ((fildes->flags & 4) && ((fildes->offset & 0xfff) == fildes->eof))
      fildes->eof++;
    fildes->offset++;
    if ((fildes->offset & 0x1ff) == 0) {
      fildes->offset--;
      if (fildes->flags & 1)
        write_sector(&(fildes->dta),fildes->current_sector);
      fildes->offset++;
      if ((fildes->offset >> 9) % 8 != 0) {
        fildes->current_sector++;
        read_sector((&fildes->dta),fildes->current_sector);
        fildes->flags &= 0xfe;
        } else {
        lump = ((fildes->current_sector - 1) /8);
        if (fildes->flags & 4) lump = append_lump(lump);
          else lump = read_lump(lump);
        fildes->current_sector = lump * 8;
        read_sector(&(fildes->dta),fildes->current_sector);
        lump = read_lump(lump);
        if (lump == 0xfefe) fildes->flags = 4; else fildes->flags = 0;
        fildes->eof = 0;
        }
      }
    }
  return ret;
  }

DIR_ENT dir_search(char* fname,FILDES* fildes,long* dir_sec,word* dir_ofs) {
  int i;
  int j;
  DIR_ENT ret;
  byte    buffer[32];
  fs_seek(fildes,0,0);
  *dir_sec = fildes->current_sector;
  *dir_ofs = fildes->offset & 0x1ff;
  while (fs_read(buffer,32,fildes) > 0) {
    i=0;
    ret.lump_hi = buffer[i++] << 8;
    ret.lump_hi |= buffer[i++];
    ret.lump_lo = buffer[i++] << 8;
    ret.lump_lo |= buffer[i++];
    ret.eof = buffer[i++] << 8;
    ret.eof |= buffer[i++];
    ret.flags = buffer[i++];
    ret.flags2 = buffer[i++];
    ret.date = buffer[i++] << 8;
    ret.date |= buffer[i++];
    ret.time = buffer[i++] << 8;
    ret.time |= buffer[i++];
    for (j=0; j<21; j++) ret.filename[j] = buffer[i++];

    if (ret.lump_hi != 0 || ret.lump_lo != 0) {
      if (strcasecmp(ret.filename,fname) == 0) return ret;
      }
    *dir_sec = fildes->current_sector;
    *dir_ofs = fildes->offset & 0x1ff;
    }
  ret.lump_hi = 0;
  ret.lump_lo = 0;
  return ret;
  }

FILDES fs_open_dir(char* pathname,int* err) {
  char    dirname[256];
  char    *pName;
  char    *pDest;
  FILDES  ret;
  FILDES  tmp;
  DIR_ENT entry;
  SECTOR  sec;
  long    dir_sec;
  word    dir_ofs;
  if (*pathname == '/') pathname++;
  if (pathname[strlen(pathname)-1] != '/') strcat(pathname,"/");
  ret = open_master_dir();
  pName = strchr(pathname,'/');
  while (pName != NULL) {
    pDest = dirname;
    while (*pathname != '/') *pDest++ = *pathname++;
    *pDest = 0;
    pathname++;
    entry = dir_search(dirname,&ret,&dir_sec,&dir_ofs);
    if ((entry.flags & 1) != 1) {
      printf("Invalid directory: %s\n",dirname);
      *err = -1;
      return ret;
      }
    if (entry.lump_hi == 0 && entry.lump_lo == 0) {
      printf("Invalid directory: %s\n",dirname);
      *err = -1;
      return ret;
      }
    tmp.offset = 0;
    tmp.dir_sector = dir_sec;
    tmp.dir_offset = dir_ofs;
    tmp.current_sector = entry.lump_lo * 8;
    read_sector(&sec,dir_sec);
    tmp.eof = (sec.data[dir_ofs+4] << 8) +
               sec.data[dir_ofs+5];
    fs_seek(&tmp,0,0);
    ret = tmp;
    pName = strchr(pathname,'/');
    }
  *err = 0;
  return ret;
  }

void fs_close(FILDES* fildes) {
  if (fildes->flags & 1)
    write_sector(&(fildes->dta),fildes->current_sector);
  if (fildes->flags & 4) {
    read_sector(&sector,fildes->dir_sector);
    sector.data[fildes->dir_offset+4] = fildes->eof / 256;
    sector.data[fildes->dir_offset+5] = fildes->eof % 256;
/*     sector.dir[fildes->dir_offset/32].eof = exchg(fildes->eof);  */
    write_sector(&sector,fildes->dir_sector);
    }
  }

DIR_ENT new_file_entry(char* fname,FILDES* dir,long* dir_sec,word* dir_ofs) {
  int i;
  word lump;
  long pos;
  char flag;
  DIR_ENT dirent;
  byte    buffer[32];
  pos = fs_seek(dir,0,0);
  flag = ' ';
  while (flag == ' ' && fs_read(buffer,32,dir) > 0) {
    if (buffer[0] == 0 && buffer[1] == 0 &&
        buffer[2] == 0 && buffer[3] == 0) {
      fs_seek(dir,pos,0);
      flag = '*';
      } else pos = fs_seek(dir,0,1);
    }
  pos = fs_seek(dir,0,1);
  lump = allocate_lump();
  write_lump(lump,0xfefe);
  dirent.lump_hi = 0;
  dirent.lump_lo = lump;
  dirent.eof = 0;
  dirent.flags = 4;
  dirent.date = 0;
  dirent.time = 0;
  *dir_sec = dir->current_sector;
  *dir_ofs = dir->offset & 0x1ff;
  buffer[0] = 0;    /* set starting lump */
  buffer[1] = 0;
  buffer[2] = lump / 256;
  buffer[3] = lump % 256;
  buffer[4] = 0;    /* eof is beginning of file */
  buffer[5] = 0;
  buffer[6] = 0;    /* nothing special about the file */
  buffer[7] = 0;    /* set no date for now */
  buffer[8] = 0;
  buffer[9] = 0;
  buffer[10] = 0;
  buffer[11] = 0;
  i = 12;
  while (*fname != 0) buffer[i++] = *fname++;
  buffer[i] = 0;
  fs_write(buffer,32,dir);
/*
  write_sector(&(dir->dta),dir->current_sector);
*/
  fs_close(dir);
  cwd=fs_open_dir(path,&i);
  return dirent;
  }

FILDES fs_open(char *fname,word flags) {
  word    lump;
  DIR_ENT dirent;
  FILDES  ret;
  long    dir_sec;
  word    dir_ofs;
  FILDES  dir;
  char*   slash;
  char    temp[1024];
  char    tmp[1024];
  int     err;
  dir = cwd;
  if (strchr(fname,'/') != NULL) {
    strcpy(temp,fname);
    slash = strrchr(temp,'/');
    *slash = 0;
    strcpy(tmp,path);
    if (*fname == '/') {
      strcpy(tmp,temp);
      } else {
      strcat(tmp,temp);
      }
    if (tmp[strlen(tmp)-1] != '/') strcat(tmp,"/");
    dir = fs_open_dir(tmp,&err);
    if (err == -1) {
      ret.dir_sector = 0;
      ret.dir_offset = 0;
      return ret;
      }
    slash = strrchr(fname,'/');
    fname = slash+1;
    }
  fs_seek(&dir,0,0);
  dirent = dir_search(fname,&dir,&dir_sec,&dir_ofs);
  if (dirent.lump_hi == 0 && dirent.lump_lo == 0) {
    if ((flags & 1) != 1) {
      ret.dir_sector = 0;
      ret.dir_offset = 0;
      return ret;
      }
    dirent = new_file_entry(fname,&dir,&dir_sec,&dir_ofs);
    }
  ret.offset = 0;
  ret.dir_sector = dir_sec;
  ret.dir_offset = dir_ofs;
  ret.flags = 0;
  ret.offset = 0;
  ret.eof = dirent.eof;
  ret.current_sector = dirent.lump_lo * 8;
  read_sector(&(ret.dta),ret.current_sector);
  lump = ret.current_sector / 8;
  lump = read_lump(lump);
  if ((flags & 2) == 2) {
    lump = ret.current_sector / 8;
    fs_delete_chain(lump);
    write_lump(lump,0xfefe);
    ret.eof = 0;
    lump = read_lump(lump);
    }
  if (lump == 0xfefe) ret.flags |= 4;
  return ret;
  }

void command_copy(char* buffer) {
  int    host_file;
  int    size;
  FILDES elf_file;
  FILDES elf_file2;
  char fname_in[255];
  char fname_out[255];
  char   buffer2[1025];
  char *pChar;
  while (*buffer > 0 && *buffer <= ' ') buffer++;
  pChar = fname_in;
  while (*buffer > 0 && *buffer > ' ') *pChar++ = *buffer++;
  *pChar = 0;
  while (*buffer > 0 && *buffer <= ' ') buffer++;
  pChar = fname_out;
  while (*buffer > 0 && *buffer > ' ') *pChar++ = *buffer++;
  *pChar = 0;
  printf("Copying %s -> %s\n",fname_in,fname_out);
  if (fname_in[0] == '[') {
    strcpy(buffer2,fname_in+1);
    strcpy(fname_in,buffer2);
    if (fname_in[strlen(fname_in)-1] != ']') {
      printf("Invalid copy format for host file\n");
      return;
      }
    fname_in[strlen(fname_in)-1] = 0;
    host_file = open(fname_in,O_RDONLY);
    if (host_file == -1) {
      printf("Could not open host file\n");
      return;
      }
    uc(fname_out);
/*
    entry = dir_search(fname_out,&cwd,&dir_sec,&dir_ofs);
*/
    elf_file = fs_open(fname_out,3);
    while ((size = read(host_file,buffer2,1024)) > 0) {
      fs_write(buffer2,size,&elf_file);
      }
    close(host_file);
    fs_close(&elf_file);
    close(host_file);
    return;
    }
  if (fname_out[0] == '[') {
    strcpy(buffer2,fname_out+1);
    strcpy(fname_out,buffer2);
    if (fname_out[strlen(fname_out)-1] != ']') {
      printf("Invalid copy format for host file\n");
      return;
      }
    fname_out[strlen(fname_out)-1] = 0;
    host_file = open(fname_out,O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (host_file == -1) {
      printf("Could not open host file\n");
      return;
      }
    uc(fname_in);
    elf_file = fs_open(fname_in,0);
    while ((size = fs_read(buffer2,1024,&elf_file)) > 0) {
      write(host_file,buffer2,size);
      }
    close(host_file);
    fs_close(&elf_file);
    return;
    }
  uc(fname_out);
  uc(fname_in);
  elf_file = fs_open(fname_in,0);
  if (elf_file.dir_sector == 0 &&
      elf_file.dir_offset == 0) {
    printf("File %s not found\n",fname_in);
    return;
    }
/*
  entry = dir_search(fname_out,&cwd,&dir_sec,&dir_ofs);
*/
  elf_file2 = fs_open(fname_out,3);
  while ((size = fs_read(buffer2,1024,&elf_file)) > 0) {
    fs_write(buffer2,size,&elf_file2);
    }
  fs_close(&elf_file2);
  fs_close(&elf_file);
  }


void command_cd(char* buffer) {
  char tmp[1024];
  int  err;
  strcpy(tmp,path);
  if (*buffer == '/') {
    strcpy(tmp,buffer);
    } else {
    strcat(tmp,buffer);
    }
  if (tmp[strlen(tmp)-1] != '/') strcat(tmp,"/");
  cwd = fs_open_dir(tmp,&err);
  if (err != -1) {
    strcpy(path,tmp);
    }
  }

void command_dir(char* command) {
  int    ct;
  int    lump;
  long   len;
  long   a,b,c,d;
  int    i;
  char   showSize;
  char   showLump;
  byte   buffer[256];
  showSize = 'N';
  showLump = 'N';
  i = 0;
  while (i<strlen(command)) {
    if (command[i] == '-') {
      i++;
      if (command[i] == 'S' || command[i] == 's') showSize = 'Y';
      if (command[i] == 'L' || command[i] == 'l') showLump = 'Y';
      }
    i++;
    }
  fs_seek(&cwd,0,0);
  while (fs_read(buffer,32,&cwd) > 0) {
    if ((buffer[0]|buffer[1]|buffer[2]|buffer[3]) != 0) {
      a = buffer[0]; b=buffer[1]; c=buffer[2]; d=buffer[3];
      lump = (a<<24) + (b<<16) + (c<<8) + d;
      if (showLump == 'Y') printf("%04x ",lump);
      lump = read_lump(lump);
      len = (buffer[4]<<8) + buffer[5];
      while (lump != 0xfefe) {
        lump = read_lump(lump);
        len += 4096;
        }
      i = 12;
      ct = 0;
      while (buffer[i] != 0){
        printf("%c",buffer[i++]);
        ct++;
        }
      if (buffer[6] & 1) {
        printf("/");
        ct++;
        }
      while (ct<20) {
        printf(" ");
        ct++;
        }
      if (showSize == 'Y') printf("%ld",len);
      if (showSize == 'Y' || showLump == 'Y') printf("\n");
      }
    }
  printf("\n");
  }

void command_chain(char* buffer) {
  unsigned int lump;
  sscanf(buffer,"%x",&lump);
  while (lump != 0xfefe && lump != 0xffff && lump != 0) {
    printf("%04x ",lump);
    lump = read_lump(lump);
    }
  printf("\n");
  }

void command_dump(char* buffer) {
  word   addr;
  int    ct;
  byte   chr;
  FILDES file;
  char   ascii[17];
  printf("%s\n",buffer);
  file = fs_open(buffer,0);
  if (file.dir_sector == 0 && file.dir_offset == 0) {
    printf("File not found\n");
    return;
    }
  ct = 0;
  addr = 0;
  while (fs_read(&chr,1,&file) == 1) {
    if (ct == 0) printf("%04x: ",addr);
    printf("%02x ",chr);
    ascii[ct] = (chr > 32 && chr <127) ? chr : '.';
    ct++;
    if (ct == 16) {
      addr += 16;
      ct = 0;
      ascii[16] = 0;
      printf("%s\n",ascii);
      }
    }
  if (ct != 0) {
    while (ct != 16) {
      ascii[ct] = ' ';
      printf("   ");
      ct++;
      }
    ascii[16] = 0;
    printf("%s\n",ascii);
    }
  }

void command_type(char* buffer) {
  byte   chr;
  FILDES file;
  printf("%s\n",buffer);
  file = fs_open(buffer,0);
  if (file.dir_sector == 0 && file.dir_offset == 0) {
    printf("File not found\n");
    return;
    }
  while (fs_read(&chr,1,&file) == 1) {
    printf("%c",chr);
    }
  printf("\n");
  }

void command_stat(char* buffer) {
  SECTOR sec;
  long   a,b,c,d;
  word   i;
  word   lump;
  read_sector(&sec,0);
  a = sec.data[256]; b=sec.data[257]; c=sec.data[258]; d=sec.data[259];
  a = (a<<24) + (b<<16) + (c<<8) + d;
  printf("Sector Count   : %ld (%ldmb)\n",a,a/2048);
  printf("Filesystem Type: %d\n",sec.data[260]);
  a = sec.data[261]; b=sec.data[262];
  a = (a<<8) + b;
  printf("Master Dir     : %ld\n",a);
  a = sec.data[265]; b=sec.data[266];
  a = (a<<8) + b;
  printf("AU size        : %ld (%ld bytes)\n",a,a*512);
  a = sec.data[267]; b=sec.data[268]; c=sec.data[269]; d=sec.data[270];
  a = (a<<8) + b;
  printf("Total AUs      : %ld\n",a);
  c = 0;
  for (i=0; i<a; i++) {
    lump = read_lump(i);
    if (lump == 0) c++;
    }
  printf("Free AUs       : %ld\n",c);
  read_sector(&sec,1);
  printf("Kernel         : %d.%d.%d",sec.data[256],sec.data[257],sec.data[258]);
  a = sec.data[259]; b=sec.data[260];
  printf(" Build %ld",a*256+b);
  a = sec.data[263]; b=sec.data[264];
  printf(" %d/%d/%ld\n",sec.data[261],sec.data[262],a*256+b);
  }

void command_showsec(char* buffer) {
  byte   chr;
  char   ascii[17];
  int    ct;
  int    i;
  word   addr;
  addr = 0;
  ct = 0;
  printf("Sector: %x\n",sec_num);
  for (i=0; i<512; i++) {
    chr = esec.data[i];
    ascii[ct] = (chr > 32 && chr <127) ? chr : '.';
    if (ct == 0) printf("%04x: ",addr);
    printf("%02x ",chr);
    ct++;
    if (ct == 16) {
      ascii[16] = 0;
      printf("%s\n",ascii);
      ct = 0;
      addr += 16;
      }
    }
  }

void command_sector(char* buffer) {
  sscanf(buffer,"%x",&sec_num);
  read_sector(&esec,sec_num);
  command_showsec(buffer);
  }

void command_delete(char* buffer) {
  DIR_ENT entry;
  long    dir_sec;
  word    dir_ofs;
  entry = dir_search(buffer,&cwd,&dir_sec,&dir_ofs);
  if (entry.lump_hi == 0 && entry.lump_lo == 0) {
    printf("File %s not found\n",buffer);
    return;
    }
  if ((entry.flags & 1) == 1) {
    printf("Cannot use DELETE on directories\n");
    return;
    }
  fs_delete(entry,dir_sec,dir_ofs);
  }


void command_md(char* buffer) {
  DIR_ENT entry;
  long    dir_sec;
  word    dir_ofs;
  SECTOR  sec;
  uc(buffer);
  entry = dir_search(buffer,&cwd,&dir_sec,&dir_ofs);
  if (entry.lump_hi != 0 || entry.lump_lo != 0) {
    printf("Name already exists\n");
    return;
    }
  entry = new_file_entry(buffer,&cwd,&dir_sec,&dir_ofs);
  read_sector(&sec,dir_sec);
  sec.data[dir_ofs+6] |= 1;
  write_sector(&sec,dir_sec);
  }

void command_rd(char* buffer) {
  DIR_ENT entry;
  FILDES  file;
  long    dir_sec;
  word    dir_ofs;
  SECTOR  sec;
  word    lump;
  uc(buffer);
  entry = dir_search(buffer,&cwd,&dir_sec,&dir_ofs);
  if (entry.lump_hi == 0 && entry.lump_lo == 0) {
    printf("Directory does not exist\n");
    return;
    }
  if ((entry.flags & 1) != 1) {
    printf("Not a directory\n");
    return;
    }
  file = fs_open(buffer,0);
  while (fs_read(buffer,32,&file) > 0) {
    if (buffer[0] != 0 ||
        buffer[1] != 0 ||
        buffer[2] != 0 ||
        buffer[3] != 0) {
      printf("Directory must be empty\n");
      return;
      }
    }
  read_sector(&sec,file.dir_sector);
  lump = sec.data[dir_ofs+2] << 8;
  lump += sec.data[dir_ofs+3];
  sec.data[dir_ofs] = 0;
  sec.data[dir_ofs+1] = 0;
  sec.data[dir_ofs+2] = 0;
  sec.data[dir_ofs+3] = 0;
  write_sector(&sec,file.dir_sector);
  fs_delete_chain(lump);
  }

void command_rename(char* buffer) {
  int     i;
  SECTOR  sec;
  FILDES  file;
  char fname_in[255];
  char fname_out[255];
  char *pChar;
  while (*buffer > 0 && *buffer <= ' ') buffer++;
  pChar = fname_in;
  while (*buffer > 0 && *buffer > ' ') *pChar++ = *buffer++;
  *pChar = 0;
  while (*buffer > 0 && *buffer <= ' ') buffer++;
  pChar = fname_out;
  while (*buffer > 0 && *buffer > ' ') *pChar++ = *buffer++;
  *pChar = 0;
  printf("Renaming %s -> %s\n",fname_in,fname_out);
  if (strchr(fname_out,'/') != NULL) {
    printf("Cannot use directory in destination\n");
    return;
    }
  file = fs_open(fname_in,0);
  if (file.dir_sector == 0 && file.dir_offset == 0) {
    printf("File not found: %s\n",fname_in);
    return;
    }
  uc(fname_out);
  read_sector(&sec,file.dir_sector);
  i = 12;
  while (fname_out[i-12] != 0) {
    sec.data[file.dir_offset+i] = fname_out[i-12];
    i++;
    }
  sec.data[file.dir_offset+i] = 0;
  write_sector(&sec,file.dir_sector);
  }

void command_extract(char* buffer) {
  SECTOR  sec;
  int     file;
  int     s;
  file = open(buffer,O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (file == -1) {
    printf("Could not open host file\n");
    return;
    }
  s= 1;
  while (s< 17) {
    read_sector(&sec,s);
    write(file,&sec,512);
    s++;
    }
  close(file);
  }

void command_sys(char* buffer) {
  SECTOR  sec;
  int     file;
  int     s;
  file = open(buffer,O_RDONLY);
  if (file == -1) {
    printf("Could not open host file\n");
    return;
    }
  s = 1;
  while (s<17) {
    read(file,&sec,512);
    write_sector(&sec,s);
    s++;
    }
  close(file);
  }

void command_fsgen(char* buffer) {
  int i;
  long size;
  long lumpsec;
  long dirsec;
  char tmp[256];
  SECTOR sec;
  long lumps;
  sscanf(buffer,"%ld",&size);
  printf("   **************** Warning ****************\n\n");
  printf("Running FSGEN will destroy all contents of this disk\n");
  printf("Type thye word CONTINUE if you wish to proceed.");
  printf("? ");
  fgets(tmp,256,stdin);
  for (i=0; i<strlen(tmp); i++)
    if (tmp[i]<32) tmp[i] = 0;
  if (strcasecmp(tmp,"CONTINUE") != 0) {
    printf("Canceled\n");
    return;
    }
  printf("\nSectors : %ld (%ldmb)\n",size,size/2048);
  printf("Clearing disk image. . .\n");
  for (i=0; i<512; i++) sec.data[i] = 0;
  i = 0;
  while (i < size) {
    write_sector(&sec,i);
    i++;
    }
  lumps = size / 8;
  printf("Number of lumps : %ld\n",lumps);
  lumpsec = (lumps / 256) + 1;
  lumpsec = (lumpsec & 7) ? (lumpsec / 8) + 1 : lumpsec / 8;
  printf("Lumps allocated to LAT : %ld\n",lumpsec);
  dirsec = lumpsec * 8 + 16;
  if (dirsec & 7) dirsec = (dirsec / 8) * 8 + 8;
  printf("Master Directory sector : %ld\n",dirsec);
  for (i=0; i<512; i++) sec.data[i] = 0xffff;
  i = 0;
  while (i<lumpsec * 8) {
    write_sector(&sec,i+17);
    i++;
    }
  i = dirsec / 8;
  while (i<lumps) {
    write_lump(i,0);
    i++;
    }
  write_lump(dirsec/8,0xfefe);
  for (i=0; i<512; i++) sec.data[i] = 0;
  for (i=0; i<256; i++) sec.data[i] = boot[i];
  sec.data[256] = (size >> 24) & 255;
  sec.data[257] = (size >> 16) & 255;
  sec.data[258] = (size >> 8) & 255;
  sec.data[259] = size & 255;
  sec.data[260] = 1;
  sec.data[261] = dirsec >> 8;
  sec.data[262] = dirsec & 255;
  sec.data[265] = 0;
  sec.data[266] = 8;
  sec.data[267] = lumps >> 8;
  sec.data[268] = lumps & 255;
  sec.data[300] = 0;
  sec.data[301] = 0;
  sec.data[302] = (dirsec / 8) >> 8;
  sec.data[303] = (dirsec / 8) & 255;
  sec.data[304] = 0;
  sec.data[305] = 0;
  sec.data[312] = 'M';
  sec.data[313] = 'D';
  sec.data[314] = '0';
  write_sector(&sec,0);
  }

char* tohex(char* buffer,long int *result) {
  char flag;
  *result = 0;
  while (*buffer ==' ') buffer++;
  flag = ' ';
  while (flag == ' ') {
    if (*buffer >= '0' && *buffer <= '9') {
      *result = *result * 16 + (*buffer - '0');
      buffer++;
      }
    else if (*buffer >= 'A' && *buffer <= 'F') {
      *result = *result * 16 + (*buffer - 'A' + 10);
      buffer++;
      }
    else if (*buffer >= 'a' && *buffer <= 'f') {
      *result = *result * 16 + (*buffer - 'a' + 10);
      buffer++;
      }
    else flag = '*';
    }
  return buffer;
  }

void command_write(char* buffer) {
  long int addr;
  long int value;
  buffer = tohex(buffer,&addr);
  while (*buffer != 0) {
    if (addr >= 512) {
      printf("Address exceeds sector buffer\n");
      return;
      }
    buffer = tohex(buffer,&value);
    esec.data[addr++] = value;
    }
  }

void command_wrsec(char* buffer) {
  write_sector(&esec,sec_num);
  }

void command_help(char* buffer) {
  printf("!addr by by .. - Write a sequence of bytes to sector buffer\n");
  printf("CD path        - Change directory\n");
  printf("CHAIN lump     - Display lump chain\n");
  printf("COPY src dest  - Copy source file to destination\n");
  printf("DELETE file    - Delete a file\n");
  printf("DIR            - Display directory\n");
  printf("     -L        - Show starting lump\n");
  printf("     -S        - Show file size\n");
  printf("DUMP file      - Display hexdump of file\n");
  printf("EXTRACT file   - Extract kernel image to host file\n");
  printf("FSGEN size     - Regenerate filesystem, destructive\n");
  printf("HELP           - Display help\n");
  printf("MD name        - Make directory\n");
  printf("PWD            - Print current working directory\n");
  printf("RD dir         - Remove a directory\n");
  printf("RENAME src dst - Rename a file\n");
  printf("SECTOR num     - Dump sector data\n");
  printf("SHOWSEC        - Show sector currently in edit buffer\n");
  printf("STAT           - Show dist statistics\n");
  printf("SYS file       - Install 'file' as kernel image\n");
  printf("TYPE file      - Type file as ASCII\n");
  printf("WRSEC          - Write sector buffer back to disk\n");
  printf("QUIT           - Exit\n");
  printf("\nNote: Sector and lump numbers are in hex\n");
  }

int main(int argc,char* argv[]) {
  int    i;
  char   flag;
  byte   buffer[256];
  strcpy(path,"/");
  if (argc == 2) {
    disk_file = open(argv[1],O_RDWR);
    } else disk_file = open("disk1.ide",O_RDWR);
  if (disk_file == -1) {
    printf("Could not open disk file\n");
    exit(1);
    }
  read_sector(&sector,0);
  dirsec = sector.data[261]*256 + sector.data[262];
  printf("\n\nElf/OS DiskTool V0.2.1 (Beta)\n\n");
  strcpy(path,"/");
  cwd = open_master_dir();
  flag = ' ';
  while (flag == ' ') {
    printf("\n%s>",path);
    fgets(buffer,250,stdin);
    for (i=0; i<strlen(buffer); i++)
      if (buffer[i]<32) buffer[i] = 0;
    if (strncasecmp(buffer,"cd ",3) == 0) command_cd(buffer+3);
    if (strcasecmp(buffer,"pwd") == 0) printf("%s\n",path);
    if (strncasecmp(buffer,"dir",3) == 0) command_dir(buffer+4);
    if (strcasecmp(buffer,"quit") == 0) flag = '*';
    if (strncasecmp(buffer,"help",4) == 0) command_help(buffer+5);
    if (strncasecmp(buffer,"copy",4) == 0) command_copy(buffer+5);
    if (strncasecmp(buffer,"chain ",6) == 0) command_chain(buffer+6);
    if (strncasecmp(buffer,"dump",4) == 0) command_dump(buffer+5);
    if (strncasecmp(buffer,"type",4) == 0) command_type(buffer+5);
    if (strncasecmp(buffer,"stat",4) == 0) command_stat(buffer+5);
    if (strncasecmp(buffer,"sector ",7) == 0) command_sector(buffer+7);
    if (strncasecmp(buffer,"delete ",7) == 0) command_delete(buffer+7);
    if (strncasecmp(buffer,"md ",3) == 0) command_md(buffer+3);
    if (strncasecmp(buffer,"rd ",3) == 0) command_rd(buffer+3);
    if (strncasecmp(buffer,"rename ",7) == 0) command_rename(buffer+7);
    if (strncasecmp(buffer,"extract ",8) == 0) command_extract(buffer+8);
    if (strncasecmp(buffer,"sys ",4) == 0) command_sys(buffer+4);
    if (strncasecmp(buffer,"fsgen ",6) == 0) command_fsgen(buffer+6);
    if (strcasecmp(buffer,"showsec") == 0) command_showsec(buffer);
    if (strncasecmp(buffer,"! ",1) == 0) command_write(buffer+1);
    if (strcasecmp(buffer,"wrsec") == 0) command_wrsec(buffer);
    }


  close(disk_file);
  return 0;
  }

