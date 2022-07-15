/*
Name:
convert-sun-dec.c

Use:
convert-sun-dec in.img out.img

Function:
Convert from big-endian to little endian and back 

Author:
Michael A. Gennert

Compile string:
cc convert-sun-dec.c -O -o convert-sun-dec
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *file_in, *file_out;
  int c1, c2;

  if(argc != 3) {
    fprintf(stderr, "Usage: %s input.img output.img\n", argv[0]);
    exit(1);
  }

  if ((file_in = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "%s: could not open input file %s\n", argv[0], argv[1]);
    exit(1);
  }

  if ((file_out = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "%s: could not open output file %s\n", argv[0], argv[2]);
    exit(1);
  }

  while( ((c1 = getc(file_in)) != EOF) && ((c2 = getc(file_in)) != EOF)) {
    putc(c2, file_out); putc(c1, file_out);
  }

/*  while(!feof(file_in)) {
    c1 = getc(file_in); c2 = getc(file_in);
    putc(c2, file_out); putc(c1, file_out);
  }
*/
  fclose(file_in); fclose(file_out);

  exit(0);
}
