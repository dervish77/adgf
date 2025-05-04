#include <stdio.h>
#include <cbm.h>

char *expand_filetype(unsigned char);

int main() 
{
      // Display directory from drive 8
   struct cbm_dirent dir;
   unsigned char filenum;
   
   filenum=2;
   if( cbm_opendir(filenum,8) !=0 ){
      printf("Error opening directory on device 8.\n");
      return 1;
   }
   printf("Filename         BLKS Type\n\n");
   while(cbm_readdir(filenum,&dir)==0) {
      printf("%16s %4d %s\n",
         dir.name,dir.size,
         expand_filetype(dir.type));
   }   
   cbm_closedir(filenum);
}

char *expand_filetype(unsigned char c)
{
   switch(c) {
      case CBM_T_DEL:
         return "DEL";
      case CBM_T_SEQ:
         return "SEQ";
      case CBM_T_PRG:
         return "PRG";
      case CBM_T_USR:
         return "USR";
      case CBM_T_REL:
         return "REL";
      case CBM_T_CBM:
         return "CBM";
      case CBM_T_DIR:
         return "DIR";
      case CBM_T_VRP:
         return "VRP";
      default:
         return "OTH";
   }
}

