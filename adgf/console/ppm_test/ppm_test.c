/*****************************************************************************
 *
 *	Test program for reading, writing, and generating PPM image files.
 *
 *	File:	ppm_test.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/19/95
 *
 *	Revisions:
 *	  2.0   03/22/96  replaced x,y with r,c
 *	  1.0	01/30/96  header cleaned up
 * 	  0.0	10/19/95  originated
 *
 *	Usage:
 *
 *	  ppm_test rf gf pf wf [rsize] [csize]
 *
 *	  rf - read flag, 0 = no read, 1 = read
 *	  gf - gen flag, 0 = no gen, 1 to 11 = gen pattern
 *	  pf - print flag, 0 = no print, 1 = print to screen, 2 = print to log
 *	  wf - write flag, 0 = no write, 1 = write
 *
 *	Examples:
 *
 *	  ppm_test 0 3 0 1 200 200      - would generate a 200x200 checkerboard
 *					  image in the file "output.ppm"
 *
 *	  ppm_test 1 0 1 0      	- would read an image from the file   
 * 					  "input.ppm" and print to screen
 *
 *****************************************************************************/


#include <stdio.h>

#ifndef _PPM_H
#include "ppm.h"
#endif


#ifndef COLOR_S_T
typedef struct {
   unsigned char r;
   unsigned char g;
   unsigned char b;
} COLOR_S_T;
#endif


/*  define some constants
 */

#define MAX_R_SIZE	800
#define MAX_C_SIZE	800

#define DEFAULT_R_SIZE	100
#define DEFAULT_C_SIZE	100

#define COLOR_BLACK	((unsigned char) 0)
#define COLOR_GREY	((unsigned char) 200)
#define COLOR_WHITE	((unsigned char) 255)

#define READ_FLAG_NO	0
#define READ_FLAG	1

#define RT_NONE		0
#define RT_BLACK	1
#define RT_WHITE	2
#define RT_CHECKER	3
#define RT_DIAG_LEFT	4
#define RT_DIAG_RIGHT	5
#define RT_CROSS	6
#define RT_GREY_BOX	7
#define RT_GREY_SCALE	8
#define RT_CROSS_HATCH	9
#define RT_RANDOM	10
#define RT_NOISE	11

#define PRINT_FLAG_NO	0
#define PRINT_SCREEN	1
#define PRINT_LOG	2

#define WRITE_FLAG_NO	0
#define WRITE_FLAG	1


#define INPUT_FILE_NAME		"input.ppm"
#define OUTPUT_FILE_NAME	"output.ppm"
#define LOG_FILE_NAME		"ppm_test.log"



#ifndef RAND_MAX
#define RAND_MAX 32767
#endif




/*  define useful macros
 */
#define ISODD(n)		(((n) % (2)) ? (0) : (1))
#define ISEVEN(n)		(((n) % (2)) ? (1) : (0))

#define ONEQUARTER(n)		( (int) ( (n) / (4) ) )
#define ONEHALF(n)		( (int) ( (n) / (2) ) )
#define THREEQUARTER(n)		( (int) ( ((n) / (4)) * (3) ) )

/* clamp the input to a specified range */
#define CLAMP(v,l,h)	((v) < (l) ? (l) : (v) > (h) ? (h) : v)


/*  define a global raster array
 */
 



/* 
 * nrand() - normalized rand(), returns floating point random number
 *		between -1.0 and 1.0
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	rand	- normalized random number
 *
 */
float nrand(void)
{
   return(2.0*(rand() / (float)RAND_MAX) - 1.0);
}




/*  AllocateRaster - allocates memory to store a simple raster RGB image
 *
 *  Parameters:
 *	R	- size of image in Y (rows)
 *	C	- size of image in X (columns)
 *
 *  Returns:
 *	raster	- pointer to allocated raster array
 */
COLOR_S_T
*AllocateRaster(int R, int C)
{
   COLOR_S_T *raster_p;

   raster_p = (COLOR_S_T *) NULL;

   return(raster_p);
}


/*  GenerateRaster - generates a test raster image
 *
 *  Parameters:
 *	R	- size of image in Y (rows)
 *	C	- size of image in X (columns)
 *	type	- type of test pattern
 *
 *  Returns:
 *	raster	- pointer to image raster array
 */
void
GenerateRaster(int type, int R, int C, COLOR_S_T *raster)
{
   int r, c;
   unsigned char level;
   char *ras_p;

   int R14, R34;
   int C14, C34;


   ras_p = (char *)raster;

   R14 = ONEQUARTER(R);
   R34 = THREEQUARTER(R);

   C14 = ONEQUARTER(C);
   C34 = THREEQUARTER(C);

   switch(type)
   {
      case RT_BLACK:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               *(ras_p++) = COLOR_BLACK;
               *(ras_p++) = COLOR_BLACK;
               *(ras_p++) = COLOR_BLACK;
            }
         }
         break;

      case RT_WHITE:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               *(ras_p++) = COLOR_WHITE;
               *(ras_p++) = COLOR_WHITE;
               *(ras_p++) = COLOR_WHITE;
            }
         }
         break;

      case RT_CHECKER:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if ( (ISEVEN(r) && ISEVEN(c)) || ( ISODD(r) &&  ISODD(c)) )
               { 
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
               if ( (ISEVEN(r) &&  ISODD(c)) || ( ISODD(r) && ISEVEN(c)) )
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
            }
         }
         break;

      case RT_DIAG_LEFT:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if (r == c)
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_DIAG_RIGHT:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if (r == (C - c))
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_CROSS:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if ( (r < R14) && (C14 < c) && (c < C34) )
               {
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
               }
               else if ( (R14 < r) && (r < R34) && (c < C14) )
               {
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
               }
               else if ( (R14 < r) && (r < R34) && (C34 < c) && (c < C) )
               {
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
               }
               else if ( (R34 < r) && (r < R) && (C14 < c) && (c < C34) )
               {
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
               }
               else if ( (R14 < r) && (r < R34) && (C14 < c) && (c < C34) )
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_GREY_BOX:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if ( (R14 < r) && (r < R34) && (C14 < c) && (c < C34) )
               {
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
                  *(ras_p++) = COLOR_GREY;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_GREY_SCALE:
         level = 26;

         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c = c + 2)
            {
               *(ras_p++) = level;
               *(ras_p++) = level;
               *(ras_p++) = level;

               *(ras_p++) = level;
               *(ras_p++) = level;
               *(ras_p++) = level;
            }

            level += 2;
         }
         break;

      case RT_CROSS_HATCH:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c = c + 2)
            {
               if ( ((r % 10) == 0) || ((c % 10) == 0) )
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_RANDOM:
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c = c++)
            {
               if (nrand() > 0.75)
               {
                  level = 128 + CLAMP( (int)(64 * nrand()), 0, 63);
                  *(ras_p++) = level;
                  *(ras_p++) = level;
                  *(ras_p++) = level;
               }
               else if ((r == ONEQUARTER(R)) || (r == THREEQUARTER(R)))
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else if ((c == ONEQUARTER(C)) || (c == THREEQUARTER(C)))
               {
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
                  *(ras_p++) = COLOR_WHITE;
               }
               else
               {
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
                  *(ras_p++) = COLOR_BLACK;
               }
            }
         }
         break;

      case RT_NOISE:
         /* draw cross shape */
         for (r = 0; r < R; r++)
         {
            for (c = 0; c < C; c++)
            {
               if ( ( (r < R14) && (C14 < c) && (c < C34) )
			|| ( (R14 < r) && (r < R34) && (c < C14) )
               		|| ( (R14 < r) && (r < R34) && (C34 < c) && (c < C) )
			|| ( (R34 < r) && (r < R) && (C14 < c) && (c < C34) ) )
               {
                  if (nrand() > 0.9)
                  {
                     if (nrand() > 0.0)
                     {
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                     }
                     else
                     {
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                     }
                  }
                  else
                  {
                     *(ras_p++) = COLOR_GREY;
                     *(ras_p++) = COLOR_GREY;
                     *(ras_p++) = COLOR_GREY;
                  }
               }
               else if ( (R14 < r) && (r < R34) && (C14 < c) && (c < C34) )
               {
                  if (nrand() > 0.9)
                  {
                     if (nrand() > 0.0)
                     {
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                     }
                     else
                     {
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                     }
                  }
                  else
                  {
                     *(ras_p++) = COLOR_WHITE;
                     *(ras_p++) = COLOR_WHITE;
                     *(ras_p++) = COLOR_WHITE;
                  }
               }
               else
               {
                  if (nrand() > 0.9)
                  {
                     if (nrand() > 0.0)
                     {
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                        *(ras_p++) = COLOR_WHITE;
                     }
                     else
                     {
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                        *(ras_p++) = COLOR_BLACK;
                     }
                  }
                  else
                  {
                     *(ras_p++) = COLOR_BLACK;
                     *(ras_p++) = COLOR_BLACK;
                     *(ras_p++) = COLOR_BLACK;
                  }
               }
            }
         }
         break;

      default:
         break;
   }
}


/*  PrintRasterDataToFile - prints a subset of raster array to indicated file
 *
 *  Parameters:
 *	fp	- pointer to output file (could be stdout)
 *	raster	- pointer to image raster array
 *	startr	- starting pixel in y (row)
 *	startc	- starting pixel in x (column)
 *	endr	- ending pixel in y (row)
 *	endc	- ending pixel in x (column)
 *	R	- max y (row)
 *	C	- max x (column)
 *
 *  Returns:
 *	none
 */
void
PrintRasterDataToFile(FILE *fp, COLOR_S_T *raster, 
			int startr, int startc, 
			int endr, int endc,
			int R, int C)
{
   int r, c;
   char *ras_p;

   ras_p = (char *)(raster + startr * C + startc);

   fprintf(fp, "Raster data:\n");
   fprintf(fp, "  r from %d to %d\n", startr, endr);
   fprintf(fp, "  c from %d to %d\n\n", startc, endc);

   for (r = startr; r < endr; r++)
   {
      for (c = startc; c < endc; c++)
      {
         fprintf(fp, "%03d,%03d = %d %d %d\n", 
					r, c, 
					*(ras_p++), 
					*(ras_p++), 
					*(ras_p++) );
      }
   }
}


/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
void 
main(int argc, char **argv)
{
   int r_size, c_size;
   FILE *readfile, *writefile, *logfile;
   int type;

   COLOR_S_T raster[MAX_R_SIZE][MAX_C_SIZE];



   if (argc < 5)
   {
      fprintf(stderr, "usage: %s rf gf pf wf [rs] [cs]\n", argv[0] );
      exit(1);
   }
   else
   {
      /*  check for read operation 
       */
      if (atoi(argv[1]) == READ_FLAG)
      {
         readfile = fopen(INPUT_FILE_NAME, "r");
         if (readfile == (FILE *)NULL)
         {
            printf("Main: error opening file to read\n");
            exit(1);
         }
         else
         {
            printf("reading PPM file ...\n");

            r_size = MAX_R_SIZE;	/* set to size of raster array */
            c_size = MAX_C_SIZE;

            if (PPM_read(readfile, (char *)&raster[0][0], &r_size, &c_size))
            {
               exit(1);
            }
         }
      }
      else
      {
         if (argc == 7)
         {
            r_size = atoi(argv[5]);
            c_size = atoi(argv[6]);
         }
         else
         {
            r_size = DEFAULT_R_SIZE;
            c_size = DEFAULT_C_SIZE;
         }
      }

      /*  check for generate operation 
       */
      if (atoi(argv[2]) != RT_NONE)
      {
         printf("generating raster ...\n");

         type = atoi(argv[2]);

         GenerateRaster(type, r_size, c_size, &raster[0][0]);
      }

      /*  check for print operation 
       */
      if (atoi(argv[3]) > PRINT_FLAG_NO)
      {
         printf("printing raster ...\n");

         if (atoi(argv[3]) == PRINT_SCREEN)
         {
            PrintRasterDataToFile(stdout, &raster[0][0], 
			0, 0, r_size, c_size, r_size, c_size);
         }
         else
         {
            logfile = fopen(LOG_FILE_NAME, "w");
            if (logfile == (FILE *)NULL)
            {
               printf("Main: error opening %s to write\n", LOG_FILE_NAME);
               exit(1);
            }
            else
            {
               PrintRasterDataToFile(logfile, &raster[0][0], 
			0, 0, r_size, c_size, r_size, c_size);
            }
         }
      }

      /*  check for write operation 
       */
      if (atoi(argv[4]) == WRITE_FLAG)
      {
         writefile = fopen(OUTPUT_FILE_NAME, "w");
         if (writefile == (FILE *)NULL)
         {
            printf("Main: error opening %s to write\n", OUTPUT_FILE_NAME);
            exit(1);
         }
         else
         {
            printf("writing PPM file ...\n");

            PPM_write(writefile, (char *)&raster[0][0], 
			r_size, c_size, "generated by ppm_test v1.0");
         }
      }
   }
}
