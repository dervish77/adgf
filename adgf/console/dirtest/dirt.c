/*****************************************************************************
 *
 *	File:	dirt.c
 *
 *	Test program for reading unix directories.
 *
 *	Usage:	dirt [path] [filter]
 *
 *	Date:	11/02/95
 *
 *	Revisions:
 *	  0.2  02/08/96  added filtering
 *	  0.1  01/30/96  added output of file list
 *	  0.0  11/02/95  Originated
 *****************************************************************************/


#include <stdio.h>
#include <dirent.h>

#define MAX_BUFFER_SIZE 80
typedef char buffer_t[MAX_BUFFER_SIZE];

#define MAX_BUFF_ARRAY_SIZE 100


/*
#define _VERBOSE
*/


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
   DIR *dirp, *tempdirp;
   struct dirent *direntp;

   buffer_t file_list_a[MAX_BUFF_ARRAY_SIZE];

   int i, file_count;

   char filter[5];			/* i.e. ".bmp\0" */
   char *substring;			/* sub string pointer */


   if (argc == 1)
   {
      dirp = opendir( "." );		/* open current directory */
   }
   else
   {
      dirp = opendir( argv[1] );	/* open specified dir path */
   }

   if (dirp == (DIR *) NULL)
   {
      fprintf(stderr, "ERROR:  directory path does not exist!\n");
      exit(1);
   }

#ifdef _VERBOSE
   printf( "dir stream info:\n" );
   printf( "  fd   = %d\n", dirp->dd_fd );
   printf( "  loc  = %d\n", dirp->dd_loc );
   printf( "  size = %d\n", dirp->dd_size );
   printf( "\n" );
#endif


   /*  while not end of dir stream, read next directory entry
    */
   file_count = 0;

   while ( (direntp = readdir( dirp )) != NULL )
   {
#ifdef _VERBOSE
      (void)printf( "ino = %#lx, off = %#lx, chars = %d, %s\n", 
				direntp->d_ino, 
				direntp->d_off, 
				direntp->d_reclen, 
				direntp->d_name );
#endif

      strcpy( &file_list_a[file_count][0], direntp->d_name );

      file_count++;
   }


   /*  output saved file list
    */
   printf("\nFile List:\n");

   for (i = 0; i < file_count; i++)
   {
      tempdirp = opendir( file_list_a[i] );

      if (tempdirp == (DIR *) NULL)
      {
         printf( "  file - %s\n", file_list_a[i]);
      }
      else
      {
         printf( "  dir  - %s\n", file_list_a[i]);

         (void)closedir( tempdirp );
      }
   }
   
   printf("\n%d files listed\n\n", file_count);


   /*  output filtered saved file list
    */
   if (argc == 3)
   {
      printf("\nFiltered File List:\n");

      if (strlen(argv[2]) == 4)
         strcpy( filter, argv[2]);
      else
         strncpy( filter, argv[2], 4);

      for (i = 0; i < file_count; i++)
      {
         tempdirp = opendir( file_list_a[i] );

         if (tempdirp == (DIR *) NULL)
         {
            substring = (char *) strstr( file_list_a[i], filter);

            if (substring != (char *) NULL)
            {
               printf( "  file - %s\n", file_list_a[i]);
            }
         }
      }
   }

   /*  close opened directory stream 
    */
   (void)closedir( dirp );		

   exit(0);
}


/* end of dirt.c */
