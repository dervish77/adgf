typedef unsigned char byte;
typedef unsigned short word;

typedef struct {
  word lump_hi;
  word lump_lo;
  word eof;
  byte flags;
  byte flags2;
  word date;
  word time;
  char filename[21];
  } DIR_ENT;

typedef union {
  byte    data[512];
  word    au[256];
  } SECTOR;

typedef struct {
  long   offset;
  SECTOR dta;
  word   eof;
  byte   flags;
  long   dir_sector;
  word   dir_offset;
  long   current_sector;
  } FILDES;

int    disk_file;
SECTOR sector;
int    dirsec;
FILDES cwd;
char   path[1024];
SECTOR esec;
long   sec_num;
