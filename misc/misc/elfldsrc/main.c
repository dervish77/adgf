#include <stdio.h>
#include <types.h>
#include <elf.h>
#include <elfcommon.h>
#include <elfld.h>


/* ****************************************************************
 * The elf formatted file resides in FLASH at location 0xFFF10000
 *
 * We emulate the unix style file IO glue routines for embedded 
 * code in "fio.c" for:
 *
 * fopen(), fseek(), fread(), fclose().
 *
 * We Parse with library function parse_elf(). This function will 
 * also run under unix when linked with main.c for test purposes. It
 * also serves as a very useful utility for dealing with .elf images.
 * *****************************************************************
 */

static char filename[128];

void main(argc, argv)
     int argc;
     char *argv[];
{
  uint32_t address;
  FILE    *fd_in;             /* file descriptor for fopen(), fread(), etc */
  Elf32_External_Ehdr elfhdr; /* allocate space on stack for elfheader */
  

   switch (argc)
   {
      case 2:
         strcpy(filename, argv[1]);
         break;

/*
      case 1:
         strcpy(filename, "diag24.elf");
         break;
*/

      default:
         fprintf(stderr, 
		"Usage:  %s <elf_file>\n", argv[0]);
         fprintf(stderr, 
		"i.e.:   %s diag24.elf\n", argv[0]);
         exit(1);
   } 


  printf("\n\nOpening file: %s\n\n", &filename[0]);
  
  if ((fd_in = fopen(filename, "r")) == 0) {
    fprintf(stderr, "\nUnable to open input file: %s @0x%x \n", filename);
    fclose(fd_in);    /* Close the input file */
    exit(1);
  }
  
  /* Now, parse the ELF file:
   * Arguments:
   *   Pass in the (FILE *) return by fopen() 
   *   Pass in a pointer to an elfhdr data structure allocated on our stack.
   */	
	
  if (elfld(fd_in, &elfhdr) == FAILED) {
    fprintf(stderr, "\nFailed to load image!");
    fclose(fd_in);    /* Close the input file */
    exit(2);
  }
  
  fclose(fd_in);    /* Close the input file */
  
}




