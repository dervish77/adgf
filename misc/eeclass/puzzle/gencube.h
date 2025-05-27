/****************************************************************
* File:		gencube.h					*
*								*
* Author:	Brian Lingard					*
*								*
* Description:  header file for gencube.c			*
*		functions for run time multidim. 3D arrays 	*
*		functions for cube manipulation			*
*								*
* Revision history:						*
* 	1.0	originated			6-Feb-1994	*
*								*
*****************************************************************/

#include "stdlib.h"

#define HDEBUG 0	/* debug flag for header file */

#define FOUND 0
#define NOTFOUND 1

#define ERROR 2
#define NOERROR 0

#define KEY 9		/* which face? */
#define TOP 0
#define BOT 1
#define LFT 2
#define RGT 3
#define FRO 4
#define BCK 5

#define Z3 3		/* number of zeros */
#define Z2 2
#define Z1 1
#define Z0 0

typedef struct element {	/* element of cube puzzle */
	unsigned short tp;
	unsigned short bt;
	unsigned short lf;
	unsigned short rt;
	unsigned short fr;
	unsigned short bk;
	int flag;	/* used as source flag */
} blah;


/** Dimension and Allocate memory for 3D cube */
struct element ***DimCube(g,r,c) 
	int g,r,c;
  {
/*	char *calloc();*/
	register struct element *pdata;
	register struct element **prow;
	register struct element ***pgrid;
	int i;
	pdata = (struct element *) calloc(g * r * c, sizeof(struct element));
	if (pdata == (struct element *) NULL) {
		fprintf(stderr,"Null data spc\n");
		exit(1);
	}
	prow = (struct element **) calloc(g * r, sizeof(struct element *));
	if (prow == (struct element **) NULL) {
		fprintf(stderr,"Null row ptrs\n");
		exit(1);
	}
	pgrid = (struct element ***) calloc(g, sizeof(struct element **));
	if (pgrid == (struct element ***) NULL) {
		fprintf(stderr,"Null grid ptrs\n");
		exit(1);
	}
	for (i=0; i < g * r; i++) {
		prow[i] = pdata;
		pdata += c;
	}
	for (i=0; i < g; i++) {
		pgrid[i] = prow;
		prow += r;
	}
	return pgrid;
  }

/* free allocated memory for cube array */
void FreeCube(pgrid)
	struct element ***pgrid;
  {
	void free();
	free (**pgrid);
	free (*pgrid);
	free (pgrid);
  }


/** copy cube function **/
void CopyCube(icube, ocube, size)
	struct element ***icube;	/* input cube */
	struct element ***ocube;	/* output cube */
	int size;
{
  int i,j,k; 

/* copy cube face values */
  for (i=0; i<size; i++) {
     for (j=0; j<size; j++) {
        for (k=0; k<size; k++) {
	   ocube[i][j][k].tp = icube[i][j][k].tp;
	   ocube[i][j][k].bt = icube[i][j][k].bt;
	   ocube[i][j][k].lf = icube[i][j][k].lf;
	   ocube[i][j][k].rt = icube[i][j][k].rt;
	   ocube[i][j][k].fr = icube[i][j][k].fr;
	   ocube[i][j][k].bk = icube[i][j][k].bk;
	}
     }
  }
} /* end of CopyCube() */
		

/* output cube data for file */
void OutputCube(cube,size,outname)
	struct element ***cube;
	int size;
	char *outname;
{
  int i,j,k;
  FILE *outfile;

  if (HDEBUG == 1) printf("OutputCube -- declaring out file ptr\n");

/* declare output file ptr */
  outfile = fopen(outname,"w");
  if (outfile == (FILE *)NULL) {
	fprintf(stderr,"unable to open file %s for output\n",outname);
	exit(1);
  }

  if (HDEBUG == 1) printf("OutputCube -- writing cube to file\n");

/* output cube face values */
  for (i=0; i<size; i++) {
     for (j=0; j<size; j++)
        for (k=0; k<size; k++) {
           fprintf(outfile,"%d %d %d -> ",i,j,k);
	   fprintf(outfile,"%4X ",cube[i][j][k].tp);
	   fprintf(outfile,"%4X ",cube[i][j][k].bt);
	   fprintf(outfile,"%4X ",cube[i][j][k].lf);
	   fprintf(outfile,"%4X ",cube[i][j][k].rt);
	   fprintf(outfile,"%4X ",cube[i][j][k].fr);
	   fprintf(outfile,"%4X ",cube[i][j][k].bk);
	   fprintf(outfile,"\n");
	}
  }

  if (HDEBUG == 1) printf("OutputCube -- closing output file\n");
  fclose(outfile);

  if (HDEBUG == 1) printf("OutputCube -- done here\n");

} /* end of OutputCube() */


/* Check Element of a cube for uninitialized data          **
**	returns 0 if element is clear, a 1 if data present **
**/
int CheckElement(cube, g, r, c)
	struct element ***cube;
	int g,r,c;
{

  if (cube[g][r][c].tp != 0)
	return(1);
  if (cube[g][r][c].bt != 0)
	return(1);
  if (cube[g][r][c].lf != 0)
	return(1);
  if (cube[g][r][c].rt != 0)
	return(1);
  if (cube[g][r][c].fr != 0)
	return(1);
  if (cube[g][r][c].bk != 0)
	return(1);

  return(0);
} /* end of CheckElement() */


/** Test if cubes are equal, returns 0 if equal, 1-6 if not equal **/
int TestCubes(acube, bcube, size)
	struct element ***acube;
	struct element ***bcube;
	int size;
{
  register int i,j,k;

/* test each face value on each cube element of each cube */
  for (i=0; i<size; i++) {
     for (j=0; j<size; j++) {
        for (k=0; k<size; k++) {
	   if (acube[i][j][k].tp != bcube[i][j][k].tp)
		return(1);
	   if (acube[i][j][k].bt != bcube[i][j][k].bt)
		return(2);
	   if (acube[i][j][k].lf != bcube[i][j][k].lf)
		return(3);
	   if (acube[i][j][k].rt != bcube[i][j][k].rt)
		return(4);
	   if (acube[i][j][k].fr != bcube[i][j][k].fr)
		return(5);
	   if (acube[i][j][k].bk != bcube[i][j][k].bk)
		return(6);
	}
     }
  }

  return(0);	/* they're the same so return 0 */
} /* end of TestCubes() */


/* copy an element from one cube to another */
void CopyElement(scube,si,sj,sk,dcube,di,dj,dk)
	struct element ***scube;
	int si,sj,sk;
	struct element ***dcube;
	int di,dj,dk;
{

  dcube[di][dj][dk].tp = scube[si][sj][sk].tp;
  dcube[di][dj][dk].bt = scube[si][sj][sk].bt;
  dcube[di][dj][dk].lf = scube[si][sj][sk].lf;
  dcube[di][dj][dk].rt = scube[si][sj][sk].rt;
  dcube[di][dj][dk].fr = scube[si][sj][sk].fr;
  dcube[di][dj][dk].bk = scube[si][sj][sk].bk;

} /* end of CopyElement() */


/* calculate random offsets from current element */
void CalcOffset(size,i,j,k,off)
	int size;
	int i,j,k;
	int *off;
{
  int dir;

/* determine random direction					    *
*	0 - up, 1 - down, 2 - left, 3 - right, 4 - front, 5 - back  */
  dir = myrandom(6);

/* for each possible direction determine appropriate random displacement */
  if (dir == 0) {   /* dir is up */
	if (i == 0)
		off[0] = 0;
	else
		off[0] = -myrandom(size - i);
	off[1] = 0;
	off[2] = 0;
  }

  if (dir == 1) {   /* dir is down */
	if (i == size - 1)
		off[0] = 0;
	else
		off[0] = myrandom(size - i);
	off[1] = 0;
	off[2] = 0;
  }

  if (dir == 2) {   /* dir is left */
	off[0] = 0;
	if (j == 0)
		off[1] = 0;
	else
		off[1] = -myrandom(size - j);
	off[2] = 0;
  }

  if (dir == 3) {   /* dir is right */
	off[0] = 0;
	if (j == size - 1)
		off[0] = 0;
	else
		off[0] = myrandom(size - j);
	off[2] = 0;
  }

  if (dir == 4) {   /* dir is front */
	off[0] = 0;
	off[1] = 0;
	if (k == 0)
		off[2] = 0;
	else
		off[2] = -myrandom(size - k);
  }

  if (dir == 5) {   /* dir is back */
	off[0] = 0;
	off[1] = 0;
	if (k == size - 1)
		off[2] = 0;
	else
		off[2] = myrandom(size - k);
  }

} /* end of CalcOffset() */


/** clear cube function **/
void ClearCube(cube, size)
  struct element ***cube;
  int size;
{
  int i,j,k;

  for (i=0; i<size; i++) {
     for (j=0; j<size; j++) {
        for (k=0; k<size; k++) {
	   cube[i][j][k].tp = 0;
	   cube[i][j][k].bt = 0;
	   cube[i][j][k].lf = 0;
	   cube[i][j][k].rt = 0;
	   cube[i][j][k].fr = 0;
	   cube[i][j][k].bk = 0;
	   cube[i][j][k].flag = 0;
	}
     }
  }

}/* end of ClearCube() */


/** counts the number of zero faces */
int CountZeros(cube,i,j,k)
	struct element ***cube;
	int i,j,k;
{
  int count=0;

  if (cube[i][j][k].tp == 0) count++;
  if (cube[i][j][k].bt == 0) count++;
  if (cube[i][j][k].lf == 0) count++;
  if (cube[i][j][k].rt == 0) count++;
  if (cube[i][j][k].fr == 0) count++;
  if (cube[i][j][k].bk == 0) count++;

  return(count);
} /* end of CountZeros() */


/** search cube for matching piece 			**/
/**	NOTE: function returns FOUND if successful,	**/
/**		NOTFOUND if not successful 		**/

int SearchCube(cube, size, which_face, face_value, nz, coord)
  struct element ***cube;	/* cube array pointer */
  int size;			/* size of cube */
  int which_face;		/* index to which face to match (0-5) */
  unsigned short face_value;	/* face value to match */
  int nz;			/* number of zero faces */
  int *coord;			/* return coordinate array (i,j,k) */
{
  register int i,j,k;		/* cube indices */
  int flag=NOTFOUND;		/* success flag */
  unsigned short MATCH=0xffff;	/* successful matching value */

  unsigned short sum;		/* temp sum variable */

/* search entire cube for matching face value */
  for (i=0; i < size; i++) {
     for (j=0; j < size; j++) {
	for (k=0; k < size; k++) {

	   if (CountZeros(cube,i,j,k) == nz) {  /* right num of zeros? */

		switch(which_face) { 		/* yes, search for match */
		   case TOP:	/* top */
			sum = cube[i][j][k].tp + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case BOT:	/* bottom */
			sum = cube[i][j][k].bt + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case LFT:	/* left */
			sum = cube[i][j][k].lf + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case RGT:	/* right */
			sum = cube[i][j][k].rt + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case FRO:	/* front */
			sum = cube[i][j][k].fr + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case BCK:	/* back */
			sum = cube[i][j][k].bk + face_value;
			if (sum == MATCH)
			   flag = FOUND;
			break;
		   case KEY:	/* key cube */
			if ((cube[i][j][k].tp == 0)
				&& (cube[i][j][k].lf == 0)
				&& (cube[i][j][k].fr == 0))
			   flag = FOUND;
			break;
		   default:
			return(ERROR);	/* something wrong!! */
			break;
		} /* end of switch */

		if (flag == FOUND) {	/* found match, return coord's */
		   coord[0] = i;
		   coord[1] = j;
	           coord[2] = k;
		   return(FOUND);
		}

	   } /* end if CountZeros() = nz */

	} /* end for k */
     } /* end for j */
  } /* end for i */

  return(NOTFOUND);	/* search failed !!! */
} /* end of SearchCube() */
