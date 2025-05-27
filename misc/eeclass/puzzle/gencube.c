/************************************************************************
Solve Cube Puzzle for EE575 project.  Uniprocessor version.

Author:		Brian Lingard

File:		gencube.c

Usage:		gencube cube_size log_file

Unix Compile string:	cc gencube.c -O -o gencube -lm
Amiga Compile string:	lc -L gencube

Revision History:
1.0	originated uniprocessor version			23-Jan-1994
1.1	working version of scramble function		6-Feb-1994
1.2	added solver function, no rotation		8-Feb-1994
1.22	added log file output, more comments		17-Feb-1994
	
Description:
    
     This program creates a 3-D cube puzzle and partitions it into smaller
cubes.  The position of these smaller cubes are scrambled and then divided
amongst several processors which will solve the puzzle in parallel.  For
example, if we are using four processors, the puzzle will be split into 
four separate sections and each section's pieces will be sent to four 
different processors.  To further add complexity, a decomposition factor
is used to cause some pieces to be sent to a processor which cannot use 
them in solving its portion of the puzzle.  For example, if a decomposition
factor of 0.25 is specified, then one quarter of a particular section will 
not be sent to the assigned processor for that section.  They will be 
randomly distributed amongst the other processors.

     Uniprocessor version (1.x) will only create, scramble and then solve 
the puzzle.  It will not need the decomposition factor, since there is only
one processor working on the puzzle.  

************************************************************************/

/* define some constants */
#define VERSION 1.22		/* current version number */

#define UNIPROC 1		/* must be a '1' for version 1.x */
#define NUMOFPROCS 1		/* must be a '1' for version 1.x */
#define NUMFACES 6
#define MAX_OUT_SIZE 20		/* cubes <8 can be output to file */

#define DEBUG 0			/* general debug flag */
#define MDEBUG 0		/* debug flag for main() */

/* include necessary files */
#include <stdio.h>
#include <math.h>
#include "random.h"		/* random number functions */
#include "gencube.h"		/* 3D cube functions */



/********************************************
* Initialize Cube Puzzle Function           *
*                                           *
* input:  cube pointer, cube size           *
* output: none                              *
*                                           *
* assume: all big cube surfaces are zero    *
*         touching faces will have opposite *
*            values                         *
*         all faces will have unique values *
********************************************/
void InitCube(cube,size)
	struct element ***cube;		/* pointer to cube array */
	int size;			/* size of cube */
{
  register int i;			/* cube indices */
  register int j;
  register int k;
  unsigned short count=1;		/* non-zero face count value */

/*  if (DEBUG == 1) printf("InitCube -- fill'ing cube\n");*/

/* assign all face values to each cube element */
  for (i=0; i<size; i++) {
     for (j=0; j<size; j++) {
        for (k=0; k<size; k++) {
	   if (i!=0) {			/* assign all tops and bottoms */
	      cube[i][j][k].tp = count++;
	      cube[i-1][j][k].bt = ~cube[i][j][k].tp;
	   }
   	   if (j!=0) {			/* assign all lefts and rights */
	      cube[i][j][k].lf = count++;
	      cube[i][j-1][k].rt = ~cube[i][j][k].lf;
	   }
	   if (k!=0) {			/* assign all fronts and backs */
	      cube[i][j][k].fr = count++;
	      cube[i][j][k-1].bk = ~cube[i][j][k].fr;
	   }
	   cube[i][j][k].flag = 0;	/* init used flag to unused */
	} /* end for k */
     } /* end for j */
  } /* end for i */

} /* end of InitCube() */


/************************************************
* Scramble Cube Puzzle Function			*
*						*
* input:   source cube pointer, destination     *
*          cube pointer, cube size              *
*						*
* output:  none                                 *
*						*
* summary:					*
*	for each element of dest cube loop	*
*	   pick random source element		*
*	   while source already used loop	*
*             adv. to next src element		*
*	      timeout?				*
*	         yes, exit on error		*
*	   end loop				*
*	   copy src element to current dest	*
*	end loop				*
*************************************************/

void ScrambleCube(scube, dcube, size)
	struct element ***scube;	/* initial source cube */
	struct element ***dcube;	/* scrambled destination cube */
	int size;
{
  int si,sj,sk;		/* source cube indices */
  int di,dj,dk; 	/* destination cube indices */
  int icount = 0;	/* iteration count */

/* scan through each element of destination cube */
  for (di=0; di<size; di++) {
     for (dj=0; dj<size; dj++) {
        for (dk=0; dk<size; dk++) {

	   si = myrandom(size);	/* pick random source element */
	   sj = myrandom(size);
	   sk = myrandom(size);

	   icount = 0;
	   while (scube[si][sj][sk].flag != 0) { /* src elem. been used? */

	      sk = sk + 1;		/* scan to next element */
	      if (sk == size) {
		 sk = 0;
		 sj = sj + 1;
		 if (sj == size) {
		    sj = 0;
		    si = si + 1;
		    if (si == size) 
		       si = 0;
		 }
	      }

	      icount++;			/* incr interation count */

	      if (icount > 10000) {	/* too many iterations? */
		fprintf(stderr,"Error - ScrambleCube() timed out!!!!\n");
		exit(1);
	      }
	   } /* end while */
		
           CopyElement(scube,si,sj,sk,dcube,di,dj,dk); /* do the copy */
	   scube[si][sj][sk].flag = 1;	/* update src elem flag to used */

	} /* end for dk */
     } /* end for dj */
  } /* end for di */
    
} /* end of ScrambleCube() */


/********************************************************
* Solve Cube Puzzle Function - NO Rotation allowed	*
*							*
* input:  scrambled cube pointer, solved cube pointer,  *
*         cube size                                     *
*							*
* output: success flag                                  *
*							*
* summary:						*
*							*
********************************************************/

int NORSolveCube(icube, scube, size)
  struct element ***icube;	/* scrambled cube pointer */
  struct element ***scube;	/* solved cube pointer */
  int size;			/* size of cube */
{
  int i,j,k;			/* solved cube indices */
  int crd[3];			/* matched piece indices (0,1,2)=(i,j,k) */


  printf("  solver: entering phase 1 ...\n");
/* search for key corner (0,0,0) */
  if (SearchCube(icube,size,KEY,0,Z3,crd) == FOUND) {
     CopyElement(icube,crd[0],crd[1],crd[2],scube,0,0,0);
  }
  else {
     printf("  solver: ERROR - key cube not found!!\n");
     exit(1);
  }

/* search for key column w/ i=0,k=0 */
  for (j=1; j < size-1; j++) {
     if (SearchCube(icube,size,LFT,scube[0][j-1][0].rt,Z2,crd) == FOUND) {
        CopyElement(icube,crd[0],crd[1],crd[2],scube,0,j,0);
     }
  } /* end for j */

  if (SearchCube(icube,size,LFT,scube[0][size-2][0].rt,Z3,crd) == FOUND) {
     CopyElement(icube,crd[0],crd[1],crd[2],scube,0,size-1,0);
  }

/* search for row i=0,j=0 */
  for (k=1; k < size-1; k++) {
     if (SearchCube(icube,size,FRO,scube[0][0][k-1].bk,Z2,crd) == FOUND) {
        CopyElement(icube,crd[0],crd[1],crd[2],scube,0,0,k);
     }
  } /* end for k */

  if (SearchCube(icube,size,FRO,scube[0][0][size-2].bk,Z3,crd) == FOUND) {
     CopyElement(icube,crd[0],crd[1],crd[2],scube,0,0,size-1);
  }

/* search for row i=0,j=size-1 */
  for (k=1; k < size-1; k++) {
     if (SearchCube(icube,size,FRO,scube[0][size-1][k-1].bk,Z2,crd) == FOUND) {
        CopyElement(icube,crd[0],crd[1],crd[2],scube,0,size-1,k);
     }
  } /* end for k */

  if (SearchCube(icube,size,FRO,scube[0][size-1][size-2].bk,Z3,crd) == FOUND) {
     CopyElement(icube,crd[0],crd[1],crd[2],scube,0,size-1,size-1);
  }

  printf("  solver: entering phase 2 ...\n");
/* search for top of cube where i=0 */
  for (j=1; j<size-1; j++) {
     for (k=1; k<size; k++) {
        if (k != size-1) { /* if not last column */
           if (SearchCube(icube,size,FRO,scube[0][j][k-1].bk,Z1,crd) == FOUND) {
              CopyElement(icube,crd[0],crd[1],crd[2],scube,0,j,k);
           }
           else {
              printf("  solver: FAILED!\n");
              exit(1);
           }
        }

        else { /* last column */
           if (SearchCube(icube,size,FRO,scube[0][j][k-1].bk,Z2,crd) == FOUND) {
              CopyElement(icube,crd[0],crd[1],crd[2],scube,0,j,k);
           }
           else {
              printf("  solver: FAILED (lc)!\n");
              exit(1);
           }
        }

     } /* end for k */
  } /* end for j */

  printf("  solver: entering phase 3 ...\n");
  printf("  i = ");
/* search for remainder of cube using bottoms as reference */
  for (i=1; i<size-1; i++) {
     printf("%d ",i);
     for (j=0; j<size; j++) {
        for (k=0; k<size; k++) {

           if (j==0) {
              if (k==0) { 		/* left front */
                 if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z2,crd) == FOUND)
                    CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
              }
              else {
                 if (k==size-1) { 	/* left back */
                    if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z2,crd) == FOUND)
                       CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                 }
                 else { 		/* left surface */
                    if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z1,crd) == FOUND)
                       CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                 }
              }
           }
           else {
              if (j==size-1) {
                 if (k==0) { 		/* right front */
                    if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z2,crd) == FOUND)
                       CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                 }
                 else {
                    if (k==size-1) { 	/* right back */
                       if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z2,crd) == FOUND)
                          CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                    }
                    else { 		/* right surface */
                       if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z1,crd) == FOUND)
                          CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                    }           
                 }
              }
              else {
                 if (k==0) {		/* front surface */
                    if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z1,crd) == FOUND)
                       CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                 }
                 else {
                    if (k==size-1) {	/* back surface */
                       if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z1,crd) == FOUND)
                          CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                    }
                    else {		/* guts of cube */
                       if (SearchCube(icube,size,TOP,scube[i-1][j][k].bt,Z0,crd) == FOUND)
                          CopyElement(icube,crd[0],crd[1],crd[2],scube,i,j,k);
                    }
                 }
              }
           }

        } /* end for k */
     } /* end for j */
  } /* end for i */

  printf("\n  solver: entering phase 4 ...\n");
/* finish by solving bottom of cube -- corners first */
  if (SearchCube(icube,size,TOP,scube[size-2][0][0].bt,Z3,crd) == FOUND)
     CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,0,0);

  if (SearchCube(icube,size,TOP,scube[size-2][0][size-1].bt,Z3,crd) == FOUND)
     CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,0,size-1);

  if (SearchCube(icube,size,TOP,scube[size-2][size-1][0].bt,Z3,crd) == FOUND)
     CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,size-1,0);

  if (SearchCube(icube,size,TOP,scube[size-2][size-1][size-1].bt,Z3,crd) == FOUND)
     CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,size-1,size-1);

/* edges next */
  for (k=1; k<size-1; k++) { /* left and right edges */
     if (SearchCube(icube,size,TOP,scube[size-2][0][k].bt,Z2,crd) == FOUND)
        CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,0,k);
     if (SearchCube(icube,size,TOP,scube[size-2][size-1][k].bt,Z2,crd) == FOUND)
        CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,size-1,k);
  }

  for (j=1; j<size-1; j++) { /* front and back edges */
     if (SearchCube(icube,size,TOP,scube[size-2][j][0].bt,Z2,crd) == FOUND)
        CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,j,0);
     if (SearchCube(icube,size,TOP,scube[size-2][j][size-1].bt,Z2,crd) == FOUND)
        CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,j,size-1);
  }

/* lastly bottom surface */
  for (j=1; j<size-1; j++) {
     for (k=1; k<size-1; k++) {
     if (SearchCube(icube,size,TOP,scube[size-2][j][k].bt,Z1,crd) == FOUND)
        CopyElement(icube,crd[0],crd[1],crd[2],scube,size-1,j,k);
     }
  }

  return(NOERROR);	/* done, no errors */
} /* end of NORSolveCube() */


/** MAIN function **/
int main(argc, argv)
     int argc;
     char *argv[];
{
  int size;				/* size of cube */
  long start_time;
  long pre_solve_time;
  long post_solve_time;

/*  char init_cube_name[] = { "cube.init" };*/
/*  char scram_cube_name[] = { "cube.scram" };*/
/*  char solve_cube_name[] = { "cube.solve" };*/
  char init_cube_name[10];
  char scram_cube_name[11];
  char solve_cube_name[11];
  FILE *logfile;

  struct element ***icube;		/* pointer to initial cube */
  struct element ***scramcube;		/* pointer to scrambled cube */
  struct element ***solvecube;		/* pointer to solved cube */

/* setup debug output file names */
  sprintf(init_cube_name, "cube.init");
  sprintf(scram_cube_name,"cube.scram");
  sprintf(solve_cube_name,"cube.solve");

/* check arguments */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s cube_size log_file\n", argv[0]);
    fprintf(stderr, "	cube_size = 8,16,20\n");
    fprintf(stderr, "   log_file = log output file name\n");
    exit(1);
  }

/* extract command line arguments */
  start_time = time ((long int *) 0);	/* measure start time */
  size = atoi(argv[1]);			/* get size of cube */

/* open log file */
  logfile = fopen(argv[2], "w");
  if (logfile == (FILE *) NULL) {
	printf("ERROR! - could not open %s as log file\n",argv[2]);
	exit(1);
  }

/* output log file header */
  fprintf(logfile,"************************************\n\n");
  fprintf(logfile,"Cube Puzzle Solver -- version %1.2f\n\n",VERSION);
  fprintf(logfile,"************************************\n\n");
  if (VERSION < 1.5) { /* use no rotation version of solver */
     fprintf(logfile,"NOTE:  NO rotation version of solver running\n\n");
  }

/* generate initial cube*/
  printf("Initializing Cube Puzzle ...\n");

  icube = DimCube(size, size, size);	 /* allocate cube memory */
  scramcube = DimCube(size, size, size);
  solvecube = DimCube(size, size, size);

  InitCube(icube, size);		 /* fill face values of cube */

  if (size < MAX_OUT_SIZE) /* output initial cube to file if size < MAX */
	OutputCube(icube, size, init_cube_name); /* out init cube to file */


/* scramble cube */
  printf("Scrambling Cube Puzzle ...\n");

  ScrambleCube(icube, scramcube, size);		/* scramble cube puzzle */

  while (TestCubes(icube, scramcube, size) == 0) {  /* scrambled? */
	printf("	not scrambled, trying again ...\n");
	ClearCube(scramcube, size);		/* clear scrambled cube */
	ScrambleCube(icube, scramcube, size);	/* scramble again */
  }

  if (size < MAX_OUT_SIZE) /* output scrambled cube to file if size < MAX */
	OutputCube(scramcube, size, scram_cube_name); /* scram cube to file */


/* solve the puzzle */
  printf("Solving Cube Puzzle ...\n");
  pre_solve_time = time((long int *) 0);	/* measure time */

  if (VERSION < 1.5) { /* use no rotation version of solver */
     if (NORSolveCube(scramcube, solvecube, size) == ERROR) {
	printf("Error returned by solver!!\n");	/* solve cube puzzle */
     }
  }
  else {
	printf("ERROR - missing rotation solver function!!!\n");
  }

  post_solve_time = time((long int *) 0);	/* measure time */
  if (size < MAX_OUT_SIZE) /* output solved cube to file if size < MAX */
	OutputCube(solvecube, size, solve_cube_name); /* solved cube to file */

/* test solution to puzzle */
  printf("Testing Solution to Puzzle ...\n");

  if (TestCubes(icube, solvecube, size) == 0) {
	printf("	Puzzle is solved!!!\n");
	fprintf(logfile,"Puzzle is solved!!!\n\n");
  }
  else {
	printf("	Puzzle not solved.\n\n");
	fprintf(logfile,"Puzzle not solved.\n\n");
  }

/* free up allocated memory for cubes */
  FreeCube(icube);
  FreeCube(scramcube);
  FreeCube(solvecube);


/* output time summary to screen */
  printf("Statistic summary:\n");
  printf("  number of processors = %d\n",NUMOFPROCS);
  printf("  size of cube = %d\n", size);
  printf("  elapsed solve time = %d\n", post_solve_time - pre_solve_time);
  printf("  elapsed total time = %d\n", post_solve_time - start_time);


/* output statistic summary to log file */
  fprintf(logfile,"Statistic summary:\n");
  fprintf(logfile,"  number of processors = %d\n",NUMOFPROCS);
  fprintf(logfile,"  size of cube = %d\n", size);
  fprintf(logfile,"\n  elapsed solve time = %d\n", 
			post_solve_time - pre_solve_time);
  fprintf(logfile,"  elapsed total time = %d\n", 
			post_solve_time - start_time);

  exit(0);
}   /* end main */

 
