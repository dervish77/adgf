/***********************************************************************
 ***** SRECTOC.C
 ***********************************************************************
 *****                                                                  
 ***** Takes motorola srecord file as input and converts it to a file
 ***** which can be compiled and linked as 'C' program. Since SRECORDS
 ***** are lines of ASCII text characters terminated by \n, this program 
 ***** basically prepends the C directives necessary to make it an array
 ***** of pointers to these character strings. 
 *****
 ***** Usage: % srectoc -I <srecord-infile> -O <cfileout> -A <arrayname>
 *****        
 *****
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

unsigned long MaxChars;
unsigned long NumBytesCopied;
unsigned long NumLinesCopied;

unsigned char InFileName[80];		   /* Input Srec file name              */
unsigned char OutFileName[80];		   /* Output 'C' file name              */	
unsigned char ArrayName[80];

#define NL 		'\n'
#define SPACE 		' '
#define TAB 		0x9
#define CR		'\r'

#define PASS		1
#define FAIL		0
#define TRUE		1
#define FALSE		0

/* Function Prototypes */
unsigned ParseSFile();
unsigned LineIn(FILE *infile, unsigned char *deststr);
int HelpScreen();
unsigned AutoSwitch(int argc, char *argv[]);
char lookahead(FILE *fptr);
void scanner(FILE *infile);
void LineOut(FILE *outfile, char *stringout);
void StampArray(FILE *outfile);

/* enter program here */

int main(int argc, char *argv[])
{
  int error;

  NumBytesCopied = 0;
  NumLinesCopied = 0;
  MaxChars = 0;

  /* set some defaults */

  sprintf(InFileName, "Infile.hex");
  sprintf(OutFileName,"Outfile.c");
  sprintf(ArrayName,  "CodeArray");

  /* get command line arguments and switches */

  (void)AutoSwitch(argc, argv);
  
  if ((error = ParseSFile()) != FAIL)
    {
      printf("\n");
      printf("\nSrecToC - Input  file %s was parsed  without error.", InFileName);
      printf("\nSrecToC - Output file %s was created without error.\n", OutFileName);
      printf("\n");
    }

  exit(0);
}

unsigned ParseSFile()
{
  int last;
  FILE *infile;
  FILE *outfile;
  char inbuf[256];
  char outbuf[256];

  last = FALSE;

  printf("\nSrecToC - Processing Input File %s ......", InFileName);

  /* Open the input and output files */

  infile = fopen(InFileName, "rt");
  if(infile == NULL)
    {
      fprintf(stderr,"Error: Unable to open file %s to process input\n", InFileName);
      exit(1);
    }
  
  printf("\nSrecToC - Processing Output File %s ......", OutFileName); 
  
  outfile = fopen(OutFileName, "wb");
  if(outfile == NULL)
    {
      fprintf(stderr,"Error: Unable to open output file %s for writing\n", OutFileName);
      return(0);
    }
  
  /* remove white space */

  scanner(infile);  
  
  /* begin creating output file */
  
  printf("\nSrecToC - Processing Output C Language Array File %s ......", OutFileName); 
  
  /* time/date stamp the output file with a comment block */
  
  StampArray(outfile);
  
  fprintf(outfile, "\nunsigned char *%s[] = {\n", ArrayName);
  
  while (LineIn(infile, &inbuf[0]))
    { 
      inbuf[0] = toupper(inbuf[0]);
      
      /* we don't care about S0 records in the download file... so skip these */
      if (strncmp("S0", &inbuf[0], 2) == 0)
        continue;
      /* S7,S8,S9 records are typically the last record in the file */
      else if (strncmp("S7", &inbuf[0], 2) == 0)
        last = TRUE;
      else if (strncmp("S8", &inbuf[0], 2) == 0)
        last = TRUE;
      else if (strncmp("S9", &inbuf[0], 2) == 0)
        last = TRUE;
      
      sprintf(&outbuf[0], "\"%s\"%s", &inbuf[0], last ? "\n" : ",\n");
      
      NumBytesCopied += (strlen(&outbuf[0]) -4);  /* do not count two quotes, comma + newline */
      
      fprintf(outfile, "%s", &outbuf[0]);
      
      NumLinesCopied++;
    }
  
  NumBytesCopied++;  /* sub 1 too many when reach EOF  (-4 above should be -3) */
  
  fprintf(outfile, "};\n");
  
  fprintf(outfile,"\n\n/* ***********************************************************");
  fprintf(outfile,"\n * Total Number of Srecord Chars: %d", NumBytesCopied);
  fprintf(outfile,"\n * Number of Srecord Lines:       %d", NumLinesCopied);
  fprintf(outfile,"\n * Longest Srecord Line:          %d chars", MaxChars);  
  fprintf(outfile,"\n * ***********************************************************");
  fprintf(outfile,"\n */\n\n\n");
  
  fclose(outfile);
  fclose(infile);
  
  return(PASS);
}


unsigned LineIn(FILE *infile, unsigned char *deststr)
{
  int i;
  int ch = 0;
  
  for (i=0; ch != EOF; i++)
    {
      ch = fgetc(infile);

      if ((ch == '\n') || (ch == '\0'))
        {
          if (i > MaxChars) MaxChars =i;
          deststr[i] = (unsigned char)'\0';
          return(1);
        }

      deststr[i] = (unsigned char)ch;
    }
  
  deststr[i] = '\0';
  
  return(0);
}


int HelpScreen()
{
  printf("\nUsage: srectoc /I infile /O outfile /A arrayname\n");
  return(1);
}

/*****************************************************************************/
/****  AutoSwitch - Resolves User Switches                                ****/
/****                                                                     ****/
/****                                                                     ****/
/****  By: Brian Findlay 2/95                                             ****/
/*****************************************************************************/

unsigned AutoSwitch(int argc, char *argv[])
{
  char switchstr[80];
  unsigned cntr = 1, cntr1, tmp;

  if (argc == 1) exit(HelpScreen());
  
  while(cntr != (unsigned)argc)
    {
      strcpy(switchstr, argv[cntr++]);
      
      cntr1 = 0;
      
      if((switchstr[cntr1] == '/')||(switchstr[cntr1] == '-'))
        cntr1++;
      else
        exit(HelpScreen());

      for(tmp = 0; switchstr[tmp]; tmp++)
        switchstr[tmp] = toupper(switchstr[tmp]);
      
      switch(switchstr[cntr1++])
        {
        case 'I' :  
          cntr1++;
          strcpy(switchstr, argv[cntr++]);
          sscanf(switchstr,"%s",&InFileName);
          break;
          
        case 'O' : 	
          cntr1++;
          strcpy(switchstr, argv[cntr++]);
          sscanf(switchstr,"%s",&OutFileName);
          break;
          
        case 'A' :
          cntr1++;
          strcpy(switchstr, argv[cntr++]);
          sscanf(switchstr,"%s",&ArrayName);
          break;
        case '?' :
        case 'H' : 
          HelpScreen();
          exit(0);
          break;
        default	 :  
          break;
        }
    }
  
  return(0);
}


char lookahead(FILE *fptr)
{
  int let1;
  let1 =fgetc(fptr);
  ungetc(let1, fptr);
  return(let1);
}

void scanner(FILE *infile)
{
  while(isspace(lookahead(infile)))  fgetc(infile);
}

void StampArray(FILE *outfile)
{
  time_t whattime;
  unsigned char *cptr;
  unsigned char when[30];
  
  whattime = time(NULL);
  cptr = ctime(&whattime);
  sprintf(when,"%-20s", cptr);
  when[24] = '\0';
  
  fprintf(outfile,"\n/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */");
  fprintf(outfile,"\n/* |                                                          | */");
  fprintf(outfile,"\n/* |  FileName:   %-35s         | */",OutFileName);
  fprintf(outfile,"\n/* |  Input File: %-35s         | */",InFileName);
  fprintf(outfile,"\n/* |                                                          | */");
  fprintf(outfile,"\n/* |  Creation:   %-s                    | */",when);
  fprintf(outfile,"\n/* |                                                          | */");
  fprintf(outfile,"\n/* |  DESCRIPTION:                                            | */");
  fprintf(outfile,"\n/* |  C Language Array contains pointers to Motorola Srecords,| */");
  fprintf(outfile,"\n/* |  enabling srecord download at runtime.                   | */");
  fprintf(outfile,"\n/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */");
  fprintf(outfile,"\n\n\n\n");
}

/****************************************************************************/
/********************************** finis ***********************************/
/****************************************************************************/



