/****************************************************************
* File:		cubeutil.h	Author:	Brian Lingard		*
*								*
* Header -  cube puzzle program functions for cube manipulation	*
*								*
* Rev	2.0	reduced file size of headers	8-Mar-1994	*
* Rev	1.0	originated			6-Feb-1994	*
*								*
*****************************************************************/

/** copy cube function **/
void CopyCube(icube, ocube)
   struct Element ***icube;	/* input cube */
   struct Element ***ocube;	/* output cube */
{
   int i,j,k; 
 
/* copy cube face values */
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
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


/* CopyCubeElement - copies element from one cube to another */
int
CopyCubeElement(scube,si,sj,sk,dcube,di,dj,dk)
   struct Element ***scube;
   int si,sj,sk;
   struct Element ***dcube;
   int di,dj,dk;
{
   dcube[di][dj][dk].tp = scube[si][sj][sk].tp;
   dcube[di][dj][dk].bt = scube[si][sj][sk].bt;
   dcube[di][dj][dk].lf = scube[si][sj][sk].lf;
   dcube[di][dj][dk].rt = scube[si][sj][sk].rt;
   dcube[di][dj][dk].fr = scube[si][sj][sk].fr;
   dcube[di][dj][dk].bk = scube[si][sj][sk].bk;

} /* end of CopyCubeElement() */
	

/* CopyListElement - copies element from one list to another */
int
CopyListElement(srclist,sindex,destlist,dindex)
   struct Element *srclist;
   int sindex;
   struct Element *destlist;
   int dindex;
{
   destlist[dindex].tp = srclist[sindex].tp;
   destlist[dindex].bt = srclist[sindex].bt;
   destlist[dindex].lf = srclist[sindex].lf;
   destlist[dindex].rt = srclist[sindex].rt;
   destlist[dindex].fr = srclist[sindex].fr;
   destlist[dindex].bk = srclist[sindex].bk;

} /* end of CopyListElement() */
	

/* CheckElement - checks if element is clear, returns 1 if not clear */
int 
CheckElement(cube, g, r, c)
   struct Element ***cube; 	/* pointer to cube */
   int g,r,c;			/* index to cube element */
{
   if (cube[g][r][c].tp != 0) return(1);
   if (cube[g][r][c].bt != 0) return(1);
   if (cube[g][r][c].lf != 0) return(1);
   if (cube[g][r][c].rt != 0) return(1);
   if (cube[g][r][c].fr != 0) return(1);
   if (cube[g][r][c].bk != 0) return(1);

   return(0);
} /* end of CheckElement() */


/* TestCubes - if cubes are equal, returns 0 if equal, 1-6 if not equal */
int 
TestCubes(acube, bcube)
   struct Element ***acube;
   struct Element ***bcube;
{
   register int i,j,k;

/* test each face value on each cube element of each cube */
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
	    if (acube[i][j][k].tp != bcube[i][j][k].tp) return(1);
	    if (acube[i][j][k].bt != bcube[i][j][k].bt) return(2);
	    if (acube[i][j][k].lf != bcube[i][j][k].lf) return(3);
	    if (acube[i][j][k].rt != bcube[i][j][k].rt) return(4);
	    if (acube[i][j][k].fr != bcube[i][j][k].fr) return(5);
	    if (acube[i][j][k].bk != bcube[i][j][k].bk) return(6);
	 }
      }
   }

   return(0);	/* they're the same so return 0 */
} /* end of TestCubes() */


/* ClearCube - clears all cube elements */
void 
ClearCube(cube)
   struct Element ***cube; /* cube pointer */
{
   int i,j,k;

   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
	    cube[i][j][k].tp = 0;
	    cube[i][j][k].bt = 0;
	    cube[i][j][k].lf = 0;
	    cube[i][j][k].rt = 0;
	    cube[i][j][k].fr = 0;
	    cube[i][j][k].bk = 0;
	    cube[i][j][k].usedflag = 0;
	    cube[i][j][k].surplus = 0;
	    cube[i][j][k].ejected = 0;
	 }
      }
   }
}/* end of ClearCube() */


/** CountZeros - counts the number of zero faces */
int 
CountZeros(cube,i,j,k)
   struct Element ***cube; 	/* cube pointer */
   int i,j,k;           /* cube element index */
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


/** ZeroCount - counts the number of zero faces */
int 
ZeroCount(list, index)
   struct Element *list; 	/* list pointer */
   int index;           	/* list element index */
{
   int count=0;

   if (list[index].tp == 0) count++;
   if (list[index].bt == 0) count++;
   if (list[index].lf == 0) count++;
   if (list[index].rt == 0) count++;
   if (list[index].fr == 0) count++;
   if (list[index].bk == 0) count++;

   return(count);
} /* end of ZeroCount() */


/* CubeToList - copy cube structure to list structure */
int
CubeToList(cube, list)
   struct Element ***cube;
   struct Element *list;
{
   int i,j,k,n;

   n = 0;
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
	    list[n].tp = cube[i][j][k].tp;
	    list[n].bt = cube[i][j][k].bt;
	    list[n].lf = cube[i][j][k].lf;
 	    list[n].rt = cube[i][j][k].rt;
	    list[n].fr = cube[i][j][k].fr;
	    list[n].bk = cube[i][j][k].bk;
	    list[n].usedflag = cube[i][j][k].usedflag;
	    list[n].surplus  = cube[i][j][k].surplus;
	    list[n].ejected  = cube[i][j][k].ejected;
            n++;
	 }
      }
   }

   return(0);
} /* end of CubeToList() */


/* parsestring - parses list of strings into array of strings */
int 
parsestring(string, args)
   char *string;
   char *args[];
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of parsestring() */


/* ParseCmdBuf - parse command buffer string received, return cmd code */
int
ParseCmdBuf(buf, faces, timevals, flag)
   char *buf;
   int  faces[];
   long timevals[];
   int  flag;		/* indicates whether cmd out or ack returned */
{
   char *argarray[7];
   int i, cmdcode;

/* translate command string to command code */
   cmdcode = 99;

   if (strncmp(buf, "strt", 4) == 0)
      cmdcode = START;
   if (strncmp(buf, "send", 4) == 0)
      cmdcode = SEND;
   if (strncmp(buf, "solv", 4) == 0)
      cmdcode = SOLVE;
   if (strncmp(buf, "done", 4) == 0)
      cmdcode = DONE;
   if (strncmp(buf, "stop", 4) == 0)
      cmdcode = STOP;
   if (strncmp(buf, "srch", 4) == 0)
      cmdcode = SRCH;
   if (strncmp(buf, "fail", 4) == 0)
      cmdcode = FAIL;
   if (strncmp(buf, "qtim", 4) == 0)
      cmdcode = QTIME;
   if (strncmp(buf, "rtim", 4) == 0)
      cmdcode = RTIME;
   if (strncmp(buf, "abrt", 4) == 0)
      cmdcode = ABORT;

/* further parse command string if necessary */
   if (flag == 0) {	/* command received */
      switch(cmdcode) {
         case SEND:	/* return 6 face value of this element */
            parsestring(buf, argarray);
            for (i=1; i<7; i++)
                faces[i-1] = atoi(argarray[i]);
            break;
         case DONE:	/* return PE num as face[0] */
            parsestring(buf, argarray);
            faces[0] = atoi(argarray[1]);
            break;
         case SRCH:
            parsestring(buf, argarray);
            faces[0] = atoi(argarray[1]);	/* from PE num */
            faces[1] = atoi(argarray[2]);	/* search value */
            faces[2] = atoi(argarray[3]);	/* num zeros */
            break;
         case RTIME:	/* return PE num and 4 time values */
            parsestring(buf, argarray);
            for (i=1; i<6; i++)
               timevals[i-1] = atol(argarray[i]);
            break;
         default:
            break;		/* no further parsing necessary */
      }
   }
   else {		/* ack returned */
      switch(cmdcode) {
         case SRCH:
            parsestring(buf, argarray);
            for (i=1; i<7; i++)
                faces[i-1] = atoi(argarray[i]); /* returned element */
            break;
         default:
            break;		/* no further parsing necessary */
      }
   }

   return(cmdcode);
} /* end of ParseCmdBuffer() */


/* FormCmdString - forms character string for specified command */
int
FormCmdString(command, sbuf, parm1, parm2)
   int command;
   char *sbuf;
   unsigned short parm1;
   int parm2;
{
   int err;

   err = 0;

   switch(command) {
      case START:
         sprintf(sbuf, "strt");
         break;
      case SOLVE:
         sprintf(sbuf, "solv");
         break;
      case DONE:
         sprintf(sbuf, "done %d ", prob.IAmPEnum);
         break;
      case STOP:
         sprintf(sbuf, "stop");
         break;
      case SRCH:
         sprintf(sbuf, "srch %d %d %d ", prob.IAmPEnum, parm1, parm2);
         break;
      case FAIL:
         sprintf(sbuf, "fail");
         break;
      case QTIME:
         sprintf(sbuf, "qtim");
         break;
      case RTIME:
         sprintf(sbuf, "rtim %d %d %d %d %d ", prob.IAmPEnum, 
                      timearray[START], timearray[SEND],
                      timearray[SOLVE], timearray[DONE]);
         break;
      case ABORT:
         sprintf(sbuf, "abrt");
         break;
      default:
         err = -1;	/* unknown command specified */
         break;
   }
   return(err);
} /* end of FormCmdString() */


/* imod - integer modulo division, returns (x mod y) */
int
imod(x,y)
   int x, y;
{
   int result;
   
   if (x > y ) 
      result = x - ((x / y) * y);
   else
      result = -1;

   return(result);
} /* end of imod */
