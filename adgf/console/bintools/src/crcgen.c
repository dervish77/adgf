/*
 *     Module Name:   crcgen.c
 *
 *     Description:
 *
 *     This file is a program file for calculating CRC of operational image
 *     and decompression module.
 *
 *     Assumptions:   N/A
 *
 *
 *
 */

/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>

unsigned long CalculateCRC(unsigned char *array, unsigned long Size );
void CRCgen(void);
unsigned long crcTable[256];
typedef short  Int16;
static unsigned char array[2097152];

/****************************************************************************/
/* *%S%FUNCTION***************************************************************
 *
 * main(int argc, char *argv[])
 * ----------------------------
 *  Description:
 *
 *       This is a main routine that is called to calculate CRC of a .bin file
 *       that contains uncompressed loader, compressed operational image and
 *       uncompressed decompression agent.
 *       It opens the .bin file, calculates CRC, writes CRC at the end of
 *       the file. Calculate the length of the file including CRC and write it
 *       down at the end of the file.
 *
 *  Parameters:
 *       expects file name.
 *  Returns:
 *
 *
 *  External variables:
 *
 *      None
 *
 * *%E%***********************************************************************
 */
int main(int argc, char *argv[])
{

unsigned long  textsize, flashsize;
unsigned long calcCRC;
unsigned char ch;
int i;
FILE *input;

/*hdmplus.bin file is made up of operational image and decompression utility.
  display the correct length of the file in the first byte. Calculate CRC and
  display it in the last byte.*/

if((input=fopen(argv[1], "r+b")) == NULL)
  return 0;

/*move the file pointer to the beginning of the file */
fseek(input,0L,2);
textsize = ftell(input);

/*calculate CRC */

CRCgen();
fseek(input,0L,0);
i=0;
while(!feof(input))
  {

    ch=fgetc(input);
    if(!feof(input)){
    array[i]=ch;
    i++;
  }
  }

calcCRC =  CalculateCRC(array, textsize);


fseek(input, 0L, 2);
textsize = ftell(input);


/*move the file pointer at the end of the file and write down CRC*/
fseek(input, 0L, 2);
fputc((Int16)((calcCRC & 0xff000000L) >> 24),input);
fputc((Int16)((calcCRC & 0xff0000L) >> 16),input);
fputc((Int16)((calcCRC & 0xff00) >> 8),input);
fputc((Int16)((calcCRC & 0xff)),input);


/*display crc and size of the file*/
printf("\nFile CRC  : %X", calcCRC);

/*software download module expects the address where contents of that address
indicates CRC */
textsize=textsize-1;

printf("\nFile Size : %X\n\n", textsize);

/*move the file pointer at the begining and overwrite the correct length*/
fseek(input, 0L, 0);
fputc((Int16)((textsize & 0xff000000L) >> 24),input);
fputc((Int16)((textsize & 0xff0000L) >> 16),input);
fputc((Int16)((textsize & 0xff00) >> 8),input);
fputc((Int16)((textsize & 0xff)),input);

fseek(input, 0L, 0);

fclose(input);


return 0;
}  /*end main*/


/****************************************************************************/
/* *%S%FUNCTION***************************************************************
 *
 * unsigned long calculateCRC(unsigned char *array, unsigned long Size)
 * --------------------------------------------------------------------
 *  Description:
 *
 *	This function calculates 32 bit CRC of a file that has uncompressed
 *      loader, compresed operational image, uncompressed decompression agent.
 *
 *  Parameters:
 *      array   -  points to the base of memory (lowest Memory Address)
 *	Size    -  size in bytes of the memory to be CRC'ed.
 *  Returns:
 *	32 bit CRC for the block of memory tested.
 *
 *  External variables:
 *
 *      None
 *
 * *%E%***********************************************************************
 */

unsigned long CalculateCRC(unsigned char *array, unsigned long Size )
{
  unsigned char *tmptr;
  register unsigned long crc;
  int i;
  unsigned char c, ch;
  unsigned long size;
  size = Size;


  crc = 0xFFFFFFFF;
  tmptr = array;

 /*move the array by 4 positions*/
   for(i=0; i<=3; i++)
     {
       tmptr++;
     }

/*    tmptr++;
    tmptr++;
    tmptr++;
    tmptr++; */


   tmptr--;

 do
    {
       tmptr++;
      c = *tmptr;
      crc = ((crc>>8) & 0x00FFFFFF) ^ crcTable[ (crc^c) & 0xFF];

    }while(tmptr!= ((array+size)-1));

    return( crc^0xFFFFFFFF );
}


/****************************************************************************/
/* *%S%FUNCTION***************************************************************
 *
 * void CRCgen( void )
 * -------------------
 *  Description:
 *
 *	This function generates a table of 32 bit CRCs. The size of the table
 *      is 256*4 = 1024 bytes long. It is used by func CalculateCRC to calc
 *      a CRC for a block of memory.
 *
 *  Parameters:
 *      none
 *
 *  Returns:
 *	none
 *
 *  External variables:
 *
 *      None
 *
 * *%E%***********************************************************************
 */
void CRCgen( void )
{

  unsigned long crc, poly;
  int     i, j;


  poly = 0xEDB88320L;
  for (i=0; i<256; i++)
    {
      crc = i;
      for (j=8; j>0; j--)
	{
	  if (crc&1)
	    {
	      crc = (crc >> 1) ^ poly;
	    }
	  else
	    {
	      crc >>= 1;
	    }
	}
	crcTable[i] = crc;
    }

}
