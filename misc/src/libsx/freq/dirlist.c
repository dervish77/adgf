/*
 * This file contains a function, get_dir_list() that will get a directory
 * listing and put all the names into a table (an array of char *'s table)
 * and return it to you (along with the number of entries in the directory
 * if desired). The table is NULL terminated (i.e. the entry after the last
 * one is a NULL), and is just like an argv style array.
 *
 * If an error occurs (memory allocation, bad directory name, etc), you
 * will get a NULL back.
 *
 * Each entry of the returned table points to a NULL-terminated string
 * that contains the name of a file in the directory.  If the name is
 * a directory, it has a slash appended to it.
 *
 * When you are done with the table, you should free it manually, or you
 * can call the function free_table() provided down below.
 *
 * See the sample main() down below for how to use it.  Ignore (or steal
 * if you'd like) the other code that isn't particularly relevant (i.e.
 * the support functions).
 * 
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>


void free_table(char **table, int n)
{
  char **orig = table;

  for(; n > 0; n--, table++)
   {
     if (*table)
       free(*table);
   }

  free(orig);
}


void free_dirlist(char **table)
{
  char **orig = table;

  while(*table)
   {
     free(*table);
     table++;
   }

  free(orig);
}


char *get_file_name(struct dirent *d)
{
  struct stat s;
  char *name;

  if (d == NULL)
   {
     fprintf(stderr, "BUG BUG BUG (got a NULL in get_file_name()).\n");
     return NULL;
   }

  if (stat(d->d_name, &s) < 0)
   {
     perror(d->d_name);
     return NULL;
   }
  
  if (S_ISDIR(s.st_mode))
   {
     name = (char *)malloc(strlen(d->d_name)+2);
     if (name == NULL)
       return NULL;
     sprintf(name, "%s/", d->d_name);
   }
  else 
   {
     name = (char *)strdup(d->d_name); 
   }

  return name;
}




#define CHUNK  100


char **get_dir_list(char *dirname, int *num_entries)
{
  int i,size=CHUNK;
  char **table, old_dir[MAXPATHLEN];
  DIR  *dir;
  struct dirent *dirent;

  getwd(old_dir);
  if (dirname && chdir(dirname) < 0)
    return NULL;
  
  dir = opendir(".");
  if (dir == NULL)
   {
     chdir(old_dir);
     return NULL;
   }
  
  table = (char **)calloc(size, sizeof(char *));
  if (table == NULL)
   {
     closedir(dir);
     chdir(old_dir);

     return NULL;
   }

  dirent = NULL;   i = 0;
  for(dirent = readdir(dir); dirent != NULL; dirent = readdir(dir))
   {
     table[i] = get_file_name(dirent);
     if (table[i] == NULL)   /* continue if there was an error */
      {
	continue;
      }

     i++;
     if (i == size)
      {
	char **table2;

	size *= 2;
	table2 = (char **)realloc(table, size * sizeof(char *));
	if (table2 == NULL)
	 {
	   free_table(table, i);
	   closedir(dir);
	   chdir(old_dir);

	   return NULL;
	 }

	table = table2;
      }
   }

  table[i] = NULL;    /* make sure the table ends with a NULL */

  if (num_entries)
    *num_entries = i;
  
  closedir(dir);
  chdir(old_dir);
  
  return table;
}


#ifdef TEST
/*
 * This function is just a wrapper for strcmp(), and is called by qsort()
 * (if used) down below.
 */
int mystrcmp(char **a, char **b)
{
  return strcmp(*a, *b);
}



main(int argc, char **argv)
{
  int i, num_entries;
  char *dirname, **table;

  if (argv[1] == NULL)
    dirname = ".";
  else
    dirname = argv[1];

  table = get_dir_list(dirname, &num_entries);
  if (table == NULL)
    printf("No such directory: %s\n", dirname);
  else
   {
     /*
      * If you want to sort the table, you would do it as follows:
      */
     qsort(table, num_entries, sizeof(char *), mystrcmp);

     printf("Number of files == %d\n", num_entries);
     for(i=0; table[i] != NULL; i++)
       printf("%s\n", table[i]);  
     
     free_table(table, num_entries);
   }

  
  exit(0);
}
#endif  /* TEST */



