/****************************************************************
* File:	   cubefunc.h	      Author:  Brian Lingard	        *
*								*
* Cube puzzle functions						*
*			                                        *
* Rev 3.0  added functions for final version    1-Apr-1994      *
* Rev 2.1  added DimList, FreeList, ErrPrint  	13-Mar-1994	*
* Rev 2.0  reduced file size of headers		8-Mar-1994	*
* Rev 1.0  originated				6-Feb-1994	*
*				                                *
*****************************************************************/

#define PICKTIMEOUT 10000

/** DimCube - Dimension and Allocate memory for 3D cube */
struct Element ***DimCube(size) 
   int size;
{
   register struct Element *pdata;
   register struct Element **prow;
   register struct Element ***pgrid;
   int i,g,r,c;

   g = size;
   r = size;
   c = size;

   pdata = (struct Element *) calloc(g * r * c, sizeof(struct Element));
   if (pdata == (struct Element *) NULL)
      ErrPrint("DimCube: null data spc",0);

   prow = (struct Element **) calloc(g * r, sizeof(struct Element *));
   if (prow == (struct Element **) NULL)
      ErrPrint("DimCube: null row ptrs",0);

   pgrid = (struct Element ***) calloc(g, sizeof(struct Element **));
   if (pgrid == (struct Element ***) NULL) 
      ErrPrint("DimCube: null grid ptrs",0);

   for (i=0; i < g * r; i++) {
      prow[i] = pdata;
      pdata += c;
   }
   for (i=0; i < g; i++) {
      pgrid[i] = prow;
      prow += r;
   }
   return pgrid;
} /* end of DimCube() */


/* FreeCube - free allocated memory for cube array */
void 
FreeCube(pgrid)
   struct Element ***pgrid;
{
   void free();
   free(**pgrid);
   free(*pgrid);
   free(pgrid);
} /* end of FreeCube() */


/* DimList - dimension and allocate memory for cube element list */
struct Element *DimList(length)
   int length;
{
   struct Element *plist;

   plist = (struct Element *) calloc(length, sizeof(struct Element));
   if (plist == (struct Element *) NULL)
      ErrPrint("DimList: null data list pointer", 0);
   return plist;
} /* end of DimList() */


/* FreeList - free up allocated memory for cube list */
int
FreeList(list)
   struct Element *list;
{
   void free();
   free(list);
   return(0);
} /* end of FreeList() */


/* ErrPrint - prints error message and exits program */
int
ErrPrint(format, code)
   char *format;	/* error message string */
   int code;		/* error code */
{
   fprintf(stderr,"Error %d: %s\n", code, format);
   FreeCube(initcube);
   FreeCube(scramcube);
   FreeCube(solvecube);
   FreeList(initlist);
   FreeList(plist);
   exit(1);
   return(0);
} /* end of ErrPrint() */


/* MarkTime - marks current time at indicated entry in time array */
int
MarkTime(index)
   int index;
{
   time(&timearray[index]);
   return(0);
} /* end of MarkTime() */


/* GetProcAddrs - read processor address file */
int
GetProcAddrs(refname)
   char *refname;
{
   FILE *reffile;
   int proc, procid;
   char host[11], port[11];
   char format[BUFLEN];

   reffile = fopen(refname, "r");
   if (reffile == (FILE *)NULL) {
      sprintf(format, "GetProcAddrs: couldn't open %s for input", refname);
      ErrPrint(format, 0);
   }

/* read proc entry record, store in procaddr structure */
   for (proc=0; proc < prob.numprocs; proc++) {
      fscanf(reffile, "%d %s %s\n", &procid, host, port); 
      procaddr[proc].procid = procid;
      strcpy(procaddr[proc].host, host);
      strcpy(procaddr[proc].port, port);
   }

/* output processor table to logfile */
   for (proc=0; proc < prob.numprocs; proc++) {
      fprintf(logfile, "PE%d is host %s with port %s\n",
             procaddr[proc].procid, procaddr[proc].host, procaddr[proc].port);
   }
   return(0);
} /* end of GetProcAddrs() */


/* ReadCube - read input cube data from file */
int 
ReadCube(inname)
   char *inname;	/* input file name */
{
   int i,j,k;
   FILE *infile;
   char format[BUFLEN];

   printf("Reading Initial Cube ...\n");

/* open input file */
   infile = fopen(inname,"r");
   if (infile == (FILE *) NULL) {
      sprintf(format, "ReadCube: unable to open %s for input", inname);
      ErrPrint(format, 0);
   }

/* read in size, num of procs, distribution counts */
   fscanf(infile,"%d\n", prob.size);
   fscanf(infile,"%d\n", prob.numprocs);
   for (i=0; i < prob.numprocs; i++)
      fscanf(infile,"%d\n", prob.distcnt[i]);

/* read in cube face values */
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
 	    fscanf(infile,"%4x  %4x  %4x  %4x  %4x  %4x\n",
				initcube[i][j][k].tp,
				initcube[i][j][k].bt,
				initcube[i][j][k].lf,
				initcube[i][j][k].rt,
				initcube[i][j][k].fr,
				initcube[i][j][k].bk);
            initcube[i][j][k].usedflag = 0;
            initcube[i][j][k].surplus = 0;
            initcube[i][j][k].ejected = 0;
         } /* end for k */
      } /* end for j */
   } /* end for i */

   fclose(infile);
   return(0);
} /* end of ReadCube() */

 
/* ReadList - read input list data from file */
int 
ReadList(inname)
   char *inname;	/* input file name */
{
   int length;
   int i;
   FILE *infile;
   char format[BUFLEN];

   printf("Reading Initial List ...\n");

/* open input file */
   infile = fopen(inname,"r");
   if (infile == (FILE *) NULL) {
      sprintf(format, "ReadList: unable to open %s for input", inname);
      ErrPrint(format, 0);
   }

/* read in size, num of procs, distribution counts */
   fscanf(infile,"%d\n", prob.size);
   fscanf(infile,"%d\n", prob.numprocs);
   for (i=0; i < prob.numprocs; i++)
      fscanf(infile,"%d\n", prob.distcnt[i]);

/* read in cube face values */
   length = prob.size * prob.size * prob.size;
   for (i=0; i < length; i++) {
      fscanf(infile,"%4x  %4x  %4x  %4x  %4x  %4x\n",
				initlist[i].tp,
				initlist[i].bt,
				initlist[i].lf,
				initlist[i].rt,
				initlist[i].fr,
				initlist[i].bk);
      initlist[i].usedflag = 0;
      initlist[i].surplus = 0;
      initlist[i].ejected = 0;
   } /* end for i */

   fclose(infile);
   return(0);
} /* end of ReadList() */

		
/* OutputCube - output cube data to file */
int 
OutputCube(cube,outname)
   struct Element ***cube;
   char *outname;
{
   int i,j,k;
   FILE *outfile;
   char format[BUFLEN];

/* declare output file ptr */
   outfile = fopen(outname,"w");
   if (outfile == (FILE *)NULL) {
      sprintf(format,"OutputCube: unable to open %s for output\n",outname);
      ErrPrint(format, 0);
   }

   fprintf(outfile,"%d\n", prob.size);
   fprintf(outfile,"%d\n", prob.numprocs);

/* output cube face values */
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
            fprintf(outfile,"%d %d %d -> %4x  %4x  %4x  %4x  %4x  %4x\n",
				i,j,k,
				cube[i][j][k].tp,
				cube[i][j][k].bt,
				cube[i][j][k].lf,
				cube[i][j][k].rt,
				cube[i][j][k].fr,
				cube[i][j][k].bk);
 	 }
      }
   }
   fclose(outfile);
   return(0);
} /* end of OutputCube() */


/* OutputList - output list data to file */
int 
OutputList(list, length, outname)
   struct Element *list;	/* pointer to list of elements */
   int length;			/* length of list */
   char *outname;		/* output file name */
{
   int i,j,k;
   FILE *outfile;
   char format[BUFLEN];

/* declare output file ptr */
   outfile = fopen(outname,"w");
   if (outfile == (FILE *)NULL) {
      sprintf(format,"OutputList: unable to open %s for output\n",outname);
      ErrPrint(format, 0);
   }

   fprintf(outfile,"%d\n", prob.size);
   fprintf(outfile,"%d\n", prob.numprocs);

/* output cube face values */
   for (i=0; i < length; i++) {
            fprintf(outfile,"%d -> %4x  %4x  %4x  %4x  %4x  %4x\n",
				i,
				list[i].tp,
				list[i].bt,
				list[i].lf,
				list[i].rt,
				list[i].fr,
				list[i].bk);
   }
   fclose(outfile);
   return(0);
} /* end of OutputList() */


/* OutputStartupMsg - outputs startup message about current problem */
int
OutputStartupMsg()
{
   printf("\nCurrent Problem:\n");
   printf("  proc id      = %d\n", prob.IAmPEnum);
   printf("  num of procs = %d\n", prob.numprocs);
   printf("  size of cube = %d\n", prob.size);
   printf("  decomp factr = %f\n\n", prob.dfactor);

   fprintf(logfile, "\nCurrent Problem:\n");
   fprintf(logfile, "  proc id      = %d\n", prob.IAmPEnum);
   fprintf(logfile, "  num of procs = %d\n", prob.numprocs);
   fprintf(logfile, "  size of cube = %d\n", prob.size);
   fprintf(logfile, "  decomp factr = %f\n\n", prob.dfactor);

   return(0);
}


/* GatherStats - gather time statistics from other PEs */
int
GatherStats()
{
   int i;

   printf("Gathering Statistics from PEs ...\n");

/* request all time values from PEs */
   for (i=1; i < prob.numprocs; i++)
      SendCommand(QTIME, i);

/* MAY NEED SLEEP STATEMENT HERE TO WAIT FOR RESPONSES FROM SLAVES */	

/* copy in master's local times */
   alltimes[0][START] = timearray[START];
   alltimes[0][SEND] = timearray[SEND];
   alltimes[0][SOLVE] = timearray[SOLVE];
   alltimes[0][DONE] = timearray[DONE];

   return(0);
} /* end of GatherStats() */


/* OutputStats - output statistics to screen and logfile */
int
OutputStats()
{
  int i;
  long einit,exmit,esolv,etotal;

/* output time summary to screen */
  printf("\nStatistic summary:\n");
  printf("  proc id         = %d\n", prob.IAmPEnum);
  printf("  number of procs = %d\n", prob.numprocs);
  printf("  size of cube    = %d\n", prob.size);
  printf("  decomp factor   = %f\n\n", prob.dfactor);

  for (i=0; i < prob.numprocs; i++) {
     einit = alltimes[i][SEND] - alltimes[i][START];
     exmit = alltimes[i][SOLVE] - alltimes[i][SEND];
     esolv = alltimes[i][DONE] - alltimes[i][SOLVE];
     etotal = alltimes[i][DONE] - alltimes[i][START];
     if (i == 0) {
        printf("  PE%d's elapsed init time  = %d\n", i, einit);
        printf("  PE%d's elapsed xmit time  = %d\n", i, exmit);
     }
     printf("  PE%d's elapsed solve time = %d\n", i, esolv);
     printf("  PE%d's elapsed total time = %d\n", i, etotal);
     printf("\n");
  }

/* output statistic summary to log file */
  fprintf(logfile,"Statistic summary:\n");
  fprintf(logfile,"  proc id         = %d\n", prob.IAmPEnum);
  fprintf(logfile,"  number of procs = %d\n", prob.numprocs);
  fprintf(logfile,"  size of cube    = %d\n", prob.size);
  fprintf(logfile,"  decomp factor   = %f\n\n", prob.dfactor);

  for (i=0; i < prob.numprocs; i++) {
     einit = alltimes[i][SEND] - alltimes[i][START];
     exmit = alltimes[i][SOLVE] - alltimes[i][SEND];
     esolv = alltimes[i][DONE] - alltimes[i][SOLVE];
     etotal = alltimes[i][DONE] - alltimes[i][START];
     if (i == 0) {
        fprintf(logfile,"  PE%d's elapsed init time  = %d\n", i, einit);
        fprintf(logfile,"  PE%d's elapsed xmit time  = %d\n", i, exmit);
     }
     fprintf(logfile,"  PE%d's elapsed solve time = %d\n", i, esolv);
     fprintf(logfile,"  PE%d's elapsed total time = %d\n", i, etotal);
     fprintf(logfile,"\n");
  }

  return(0);
}


/* InitCube - initialize cube from scratch */
void 
InitCube()
{
   register int i;			/* cube indices */
   register int j;
   register int k;
   unsigned short count=1;		/* non-zero face count value */

   printf("Initializing Cube Puzzle ...\n");

/* assign all face values to each cube element */
   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
 	    if (i!=0) {			/* assign all tops and bottoms */
	       initcube[i][j][k].tp = count++;
	       initcube[i-1][j][k].bt = ~initcube[i][j][k].tp;
	    }
   	    if (j!=0) {			/* assign all lefts and rights */
	       initcube[i][j][k].lf = count++;
	       initcube[i][j-1][k].rt = ~initcube[i][j][k].lf;
	    }
	    if (k!=0) {			/* assign all fronts and backs */
	       initcube[i][j][k].fr = count++;
	       initcube[i][j][k-1].bk = ~initcube[i][j][k].fr;
	    }
	    initcube[i][j][k].usedflag = 0; /* init used flag to unused */
	    initcube[i][j][k].surplus = 0;  /* init surplus flag */
	    initcube[i][j][k].ejected = 0;  /* init ejected flag */
  	 } /* end for k */
      } /* end for j */
   } /* end for i */

} /* end of InitCube() */


/* ScrambleCube - scramble init cube puzzle */
int 
ScrambleCube()
{
   int si,sj,sk;	/* source cube indices */
   int di,dj,dk; 	/* destination cube indices */
   int icount = 0;	/* iteration count */

   printf("Scrambling Cube Puzzle ...\n");
   MarkTime(SEND);

/* scan through each element of destination cube */
   for (di=0; di < prob.size; di++) {
      for (dj=0; dj < prob.size; dj++) {
         for (dk=0; dk < prob.size; dk++) {

	    si = myrandom(prob.size);	/* pick random source element */
	    sj = myrandom(prob.size);
	    sk = myrandom(prob.size);

	    icount = 0;
	    while (initcube[si][sj][sk].usedflag != 0) { /* src elem. used? */
	       sk = sk + 1;		/* scan to next element */
	       if (sk == prob.size) {
	 	  sk = 0;
		  sj = sj + 1;
		  if (sj == prob.size) {
		     sj = 0;
		     si = si + 1;
		     if (si == prob.size) 
		        si = 0;
		  }
	       }
	       icount++;			/* incr iteration count */
	       if (icount > TIMEOUT)	/* too many iterations? */
		  ErrPrint("ScrambleCube: timed out!!",0);
	    } /* end while */
		
            CopyCubeElement(initcube,si,sj,sk,scramcube,di,dj,dk);
	    initcube[si][sj][sk].usedflag = 1;  /* update used */

	 } /* end for dk */
      } /* end for dj */
   } /* end for di */    
} /* end of ScrambleCube() */


/* CalcDecompBounds - calculates decomp factor probability bounds */
int
CalcDecompBounds(bounds)
   double bounds[];
{
   double sameprob, incrprob;
   int i;

   if (prob.numprocs > 0) {
      sameprob = 1 - (((prob.numprocs - 1) * prob.dfactor) / prob.numprocs);
      incrprob = prob.dfactor / prob.numprocs;
   }
   else
      ErrPrint("CalcDecompBounds: divide by zero while calc'ing bounds", 0);

   bounds[0] = 0.0;
   bounds[1] = sameprob;
   for (i=2; i < (prob.numprocs + 1); i++) 
      bounds[i] = bounds[i-1] + incrprob;

   if (bounds[prob.numprocs] != 1.0)
      ErrPrint("CalcDecompBounds: error calc'ing bounds", 0);

   if (DEBUG==TRUE) {
      fprintf(logfile,"Calc'ed Bounds are:\n");
      for (i=0; i < (prob.numprocs + 1); i++)
         fprintf(logfile,"  %d - %f\n", i, bounds[i]);
   }

   return(0);
} /* end of CalcDecompBounds() */


/* RandomTarget - determines random target PE based on source region */
int
RandomTarget(i, j, k, bounds)
   int i,j,k;
   double bounds[];
{
   int pe;			/* target pe */
   int quadrant;		/* source region */
   int halfdim, fulldim;
   int loopcnt;
   short int inum;
   double rannum;		/* random floating number */
   long seednum;

   fulldim = prob.size;
   halfdim = fulldim / 2;

/* determine source region */
   if ((i < halfdim) || (prob.numprocs <= 4)) {
      if ((j < halfdim) && (k < halfdim))
         quadrant = 0;
      if ((j >= halfdim) && (k < halfdim))
         quadrant = 1;
      if ((j < halfdim) && (k >= halfdim))
         quadrant = 2;
      if ((j >= halfdim) && (k >= halfdim))
         quadrant = 3;
   }
   else {
      if ((j < halfdim) && (k < halfdim))
         quadrant = 4;
      if ((j >= halfdim) && (k < halfdim))
         quadrant = 5;
      if ((j < halfdim) && (k >= halfdim))
         quadrant = 6;
      if ((j >= halfdim) && (k >= halfdim))
         quadrant = 7;
   }

/* pick random number and chose target PE */
   inum = myrandom(MAXINT);			/* random integer */
   rannum = (double) inum / MAXINT;
   if (rannum < 0.0)				/* if number is negative */
      rannum = rannum * -1;			/* change it to positive*/

/*if (DEBUG==TRUE) printf("rannum = %f, quad = %d, ", rannum, quadrant);*/

   if ((rannum < bounds[1]) || (prob.dfactor == 0.0)) {	/* keep in same region */
/*if (DEBUG==TRUE) printf("keep same quadrant,");*/
      pe = quadrant;
   }
   else {				/* pick new region */
if (DEBUG==TRUE) printf("pick new quadrant, i,j,k = %d,%d,%d, quad was %d, rannum is %f\n", 
i,j,k,quadrant,rannum);
      if (prob.numprocs < 4) {
         pe = 1;
      }
      else {
         loopcnt = 0;
         pe = myrandom(prob.numprocs);
         while ((pe == quadrant) && (loopcnt < PICKTIMEOUT)) {
/*if (DEBUG==TRUE) printf("\nin while loop\n");*/
            pe = myrandom(prob.numprocs);
            loopcnt++;
         }
      }
   }
/*if (DEBUG==TRUE) printf(" pe = %d\n", pe);*/
   return(pe);
} /* end of RandomTarget() */


/* DistributeCube - distribute cube elements to the other PEs */
int
DistributeCube()
{
   double bounds[MAXPROCS];	/* array of boundary probabilities */
   int src, i, j, k;		/* indices */
   int pe;			/* target PE num */

   printf("Distributing Cube Puzzle ...\n");
   MarkTime(SEND);
   program_state = SEND;

/* calculate decomposition probability boundaries */
   CalcDecompBounds(bounds);

/* randomly distribute elements from initlist to the PEs */
   src = 0;

   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
            pe = RandomTarget(i, j, k, bounds);

/*if (imod(src, 100) == 0)*/
/*   if (DEBUG==TRUE) printf("from src = %d, target pe is = %d\n", src, pe);*/

            switch(pe) {
               case 0:   /* PE0 - master PE */
                  if (plistcnt < MAXLISTLEN) {
                     plist[plistcnt].tp = initlist[src].tp;
                     plist[plistcnt].bt = initlist[src].bt;
                     plist[plistcnt].lf = initlist[src].lf;
                     plist[plistcnt].rt = initlist[src].rt;
                     plist[plistcnt].fr = initlist[src].fr;
                     plist[plistcnt].bk = initlist[src].bk;
                     plist[plistcnt].usedflag = 0;
                     plist[plistcnt].surplus = 0;
                     plist[plistcnt].ejected = 0;
                     plistcnt++;
                  }
                  else
                     ErrPrint("DistributeCube: exceeded max plistcnt", 0);
                  break;
               default:  /* send any other PE */
                  if (pe < prob.numprocs) {
                     SendElement(SEND, pe, initlist, src);
                  }
                  else
                     ErrPrint("DistributeCube: invalid target pe", 0);
                  break;
            } /* end switch pe */

            src++;
         } /* end for k */
      } /* end for j */
   } /* end for i */

   return(0);
} /* end of DistributeCube() */


/* NewDistributeCube - alternate function distribute cube elements to the other PEs */
int
NewDistributeCube()
{
   double bounds[MAXPROCS];	/* array of boundary probabilities */
   int src, i, j, k;		/* indices */
   int pe;			/* target PE num */

   printf("Distributing Cube Puzzle ...\n");
   MarkTime(SEND);
   program_state = SEND;

/* calculate decomposition probability boundaries */
   CalcDecompBounds(bounds);

/* randomly distribute elements from initlist to the PEs */
   src = 0;

   for (i=0; i < prob.size; i++) {
      for (j=0; j < prob.size; j++) {
         for (k=0; k < prob.size; k++) {
            pe = RandomTarget(i, j, k, bounds);

if (DEBUG==TRUE) printf("from src = %d, target pe is = %d\n", src, pe);
            switch(pe) {
               case 0:   /* PE0 - master PE */
                  if (plistcnt < MAXLISTLEN) {
                     plist[plistcnt].tp = initlist[src].tp;
                     plist[plistcnt].bt = initlist[src].bt;
                     plist[plistcnt].lf = initlist[src].lf;
                     plist[plistcnt].rt = initlist[src].rt;
                     plist[plistcnt].fr = initlist[src].fr;
                     plist[plistcnt].bk = initlist[src].bk;
                     plist[plistcnt].usedflag = 0;
                     plist[plistcnt].surplus = 0;
                     plist[plistcnt].ejected = 0;
                     plistcnt++;
                  }
                  else
                     ErrPrint("DistributeCube: exceeded max plistcnt", 0);
                  break;
               default:  /* send any other PE */
                  if (pe < prob.numprocs) {
                     CopyListElement(initlist, src, dlist[pe], dlistcnt[pe]);
                     dlistcnt[pe]++;
                  }
                  else
                     ErrPrint("DistributeCube: invalid target pe", 0);
                  break;
            } /* end switch pe */

            src++;
         } /* end for k */
      } /* end for j */
   } /* end for i */

/* distribute elements a list at a time to appropriate PE */
   for (pe=1; pe < prob.numprocs; pe++) {
      SendList(SEND, pe);
   }

   return(0);
} /* end of NewDistributeCube() */



/* SolveCube - cube puzzle solver function */
int
SolveCube()
{
   int successful;

   printf("Solving Cube Puzzle ...\n");
   MarkTime(SOLVE);
   program_state = SOLVE;

   successful = -1;

/* perform solving algorithm -- note only good for 4 or 8 PEs */
   while(successful < 0) {
      FindCorner(TOP);		/* find corner element for top corner */
      BuildHorizEdge(TOP, FRO);	/* build top front edge */
      BuildHorizEdge(TOP, LFT);	/* build top left edge */
      BuildVertEdge(FRO, LFT);	/* build front left edge - vertical */
      if (prob.numprocs < 8) {
         FindCorner(BOT);	/* find corner element for bottom corner */
      }

      /*EjectSurplus(3);*/		/* eject all remaining 3 zero pieces */

      if (prob.numprocs < 8) {
         BuildHorizEdge(BOT, FRO);	/* build bottom front edge */
         BuildHorizEdge(BOT, LFT);	/* build bottom left edge */
      }

      /*EjectSurplus(2);*/		/* eject all remaining 2 zero pieces */

      BuildSurface(TOP);	/* build top surface */   
      BuildSurface(FRO);	/* build front surface */   
      BuildSurface(LFT);	/* build left surface */
      if (prob.numprocs < 8)
         BuildSurface(BOT);	/* build bottom surface */   

      /*EjectSurplus(1);*/		/* eject all remaining 1 zero pieces */

      BuildGuts();		/* build the guts of the puzzle */

      /*EjectSurplus(0);*/		/* eject all remaining 0 zero pieces */

      printf("... puzzle completed\n");
      successful = 0;
   } /* end while not successful */

   return(0);
} /* end of SolveCube() */


/* FindCorner - finds corner element and places it at specified position */
int
FindCorner(position)
   int position;
{
   int i, index, face;
   int done, found_corner;
   int direction;
   unsigned short srchval;

   done = 0;

/* search list for element with 3 zeros on faces */
   while (!done) {
      index = -1;
      found_corner = 0;

      /* place element found at the specified corner */
      if (position == TOP) {		/* place corner at top */
         printf("... finding TOP corner\n");

         while (index == -1) {
            i = 0;
            while ((i < plistcnt) && (!found_corner)) { /* search list for a 3 zero piece */
               if (ZeroCount(plist, i) == 3) {
                  index = i;			/* found one, save the index */
                  found_corner = 1;
               }
               i++;
            }
            if (index == -1 ) {
               if (RemoteSearch(32768, 3) < 0) 		/* any corner */
                  ErrPrint("FindCorner: remote search failed", 0);               
            }
         }

         /* correct the orientation of the piece found */
         while (plist[index].tp != 0) {
            direction = myrandom(3) + 1;		/* rotate in random direction */
            RotateOnce(plist, index, direction);
         }
         while ((plist[index].lf != 0) || (plist[index].fr != 0)) {
            RotateOnce(plist, index, 3);	/* rotate in yaw */
         }

         CopyElement(plist, index, solvecube, 0, 0, 0);
      }
      else {				/* place corner at bottom */
         printf("... finding BOT corner\n");

         srchval = solvecube[prob.size - 2][0][0].bt;
         index = SearchList(plist, plistcnt, srchval, 3);
         while (index < 0) {	/* while not found */
/*            EjectRandom();*/		/* eject random unused piece */
            if (RemoteSearch(srchval, 3) < 0) 
               ErrPrint("FindCorner: remote search failed", 0);
            index = SearchList(plist, plistcnt, srchval, 3); /* check again */
         }

         /* correct the orientation of the piece found */
         face = WhichFace(plist, index, srchval);	/* srchval found on correct face? */
         if (face != TOP)
            RotateElement(plist, index, srchval, TOP, face);	/* rotate it */

         while ((plist[index].lf != 0) || (plist[index].fr != 0))
            RotateOnce(plist, index, 3);	/* rotate in yaw */

         CopyElement(plist, index, solvecube, prob.size-1, 0, 0);
      }
      done = 1;
   }

   return(0);
} /* end of FindCorner() */


/* BuildHorizEdge - builds a specified horizontal edge of the puzzle */
int 
BuildHorizEdge(position, edge)
   int position;	/* allowed values are TOP and BOT */
   int edge;		/* allowed values are LFT and FRO */
{
   int done, i, j, k, index, face;
   int ilimit, jlimit, klimit;
   unsigned short srchval;

   done = 0;

   printf("... building horizontal edge at pos %d at %d\n", position, edge);

/* set for loop limits */
   switch(prob.numprocs) {
      case 1:
         ilimit = prob.size-1;	/* just shy of the opposite corners */
         jlimit = prob.size-1;
         klimit = prob.size-1;
         break;
      case 2:
         ErrPrint("BuildSurface: 2 PEs not supported", 0);
      case 4:
         ilimit = prob.size-1;	/* just shy of the bottom corner */
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      case 8:
         ilimit = prob.size/2;
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      default:
         ErrPrint("BuildHorizEdge: invalid number of PEs", 0);
   }

/* set i coordinate value */
   if (position == TOP)
      i = 0;			/* must be top edge */
   else
      i = prob.size - 1;	/* must be bottom edge */

/* set j and k coordinate values based on which edge were building */
   if (edge == FRO) {		/* must be front edge */		
      k = 0;

      while (!done) {		/* build front edge */
         for (j=1; j < jlimit; j++) {
            srchval = solvecube[i][j-1][k].rt;
            index = SearchList(plist, plistcnt, srchval, 2);	/* search for 2 zero pcs */
            while (index < 0) {	/* while not found */
/*               EjectRandom();*/		/* eject random unused piece */
               if (RemoteSearch(srchval, 2) < 0) 
                  ErrPrint("BuildHorizEdge: remote search failed", 0);
               index = SearchList(plist, plistcnt, srchval, 2); /* check again */
            }

            /* check if search value on correct face, if not then fix it */
            face = WhichFace(plist, index, srchval);	/* srchval found on correct face? */
            if (face != LFT)
               RotateElement(plist, index, srchval, LFT, face);	/* rotate it */

            /* orient piece with respect to outer surface positions */
            if (position == TOP) {	/* top front edge */
               while ((plist[index].fr != 0) || (plist[index].tp != 0)) {
                  RotateOnce(plist, index, 1);			/* rotate in pitch */
               }
/*if (DEBUG==TRUE) printf("after correction, tp = %x, fr = %x\n", plist[index].tp, plist[index].fr);*/
            }
            else {			/* bottom front edge */
               while ((plist[index].fr != 0) || (plist[index].bt != 0)) {
                  RotateOnce(plist, index, 1);			/* rotate in pitch */
               }
/*if (DEBUG==TRUE) printf("after correction, bt = %x, fr = %x\n", plist[index].bt, plist[index].fr);*/
            }
 
            CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
         }
         done = 1;
      }
   }
   else {			/* must be left edge */
      j = 0;

      while (!done) {		/* build left edge */
         for (k=1; k < klimit; k++) {
            srchval = solvecube[i][j][k-1].bk;

            index = SearchList(plist, plistcnt, srchval, 2);	/* search for 2 zero pcs */
            while (index < 0) {	/* while not found */
/*               EjectRandom();*/		/* eject random unused piece */
               if (RemoteSearch(srchval, 2) < 0) 
                  ErrPrint("BuildHorizEdge: remote search failed", 0);
               index = SearchList(plist, plistcnt, srchval, 2);	/* check again */
            }

            /* check if search value on correct face, if not then fix it */
            face = WhichFace(plist, index, srchval);	/* srchval found on correct face? */
            if (face != FRO)
               RotateElement(plist, index, srchval, FRO, face);	/* rotate it */

            /* orient piece with respect to outer surface positions */
            if (position == TOP) {	/* top left edge */
               while ((plist[index].lf != 0) || (plist[index].tp != 0)) {
                  RotateOnce(plist, index, 2);			/* rotate in roll */
               }
/*if (DEBUG==TRUE) printf("after correction, tp = %x, lf = %x\n", plist[index].tp, plist[index].lf);*/
            }
            else {			/* bottom left edge */
               while ((plist[index].lf != 0) || (plist[index].bt != 0)) {
                  RotateOnce(plist, index, 2);			/* rotate in roll */
               }
/*if (DEBUG==TRUE) printf("after correction, bt = %x, lf = %x\n", plist[index].bt, plist[index].lf);*/
            }

            CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
         }
         done = 1;
      }
   }

   return(0);
} /* end of BuildHorizEdge() */


/* BuildVertEdge - builds a vertical edge of the puzzle */
int
BuildVertEdge(position, edge)
   int position;
   int edge;
{
   int done, i, j, k, index, face;
   int ilimit;
   unsigned short srchval;

   done = 0;

   printf("... building vertical edge\n");

/* set for loop limits */
   switch(prob.numprocs) {
      case 1:
         ilimit = prob.size-1;	/* just shy of the bottom corner */
         break;
      case 2:
         ErrPrint("BuildSurface: 2 PEs not supported", 0);
      case 4:
         ilimit = prob.size-1;	/* just shy of the bottom corner */
         break;
      case 8:
         ilimit = prob.size/2;
         break;
      default:
         ErrPrint("BuildSurface: invalid number of PEs", 0);
   }

/* set j and k coordinate values */
   if (position == FRO) {
      j = 0;
      k = 0;
   }
   else
      ErrPrint("BuildVertEdge: unsupported position", 0);

   if (edge == LFT) {		/* must be front left vertical edge */		
      while (!done) {		/* build front left edge */
         for (i=1; i < ilimit; i++) {
            srchval = solvecube[i-1][j][k].bt;
            index = SearchList(plist, plistcnt, srchval, 2);	/* search for 2 zero pcs */
            while (index < 0) {	/* while not found */
/*               EjectRandom();*/		/* eject random unused piece */
               if (RemoteSearch(srchval, 2) < 0) 
                  ErrPrint("BuildVertEdge: remote search failed", 0);
               index = SearchList(plist, plistcnt, srchval, 2); /* check again */
            }

            /* check if search value is on correct face, if not then fix it */
            face = WhichFace(plist, index, srchval);	/* search value on correct face? */
            if (face != TOP)
               RotateElement(plist, index, srchval, TOP, face);	/* rotate it */

            /* orient piece with respect to outer surface positions */
            while ((plist[index].fr != 0) || (plist[index].lf != 0))
               RotateOnce(plist, index, 3);			/* rotate in yaw */

            CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
         }
         done = 1;
      }
   }
   else
      ErrPrint("BuildVertEdge: unsupported edge", 0);

   return(0);
} /* end of BuildVertEdge() */


/* BuildSurface - builds a specified surface of the puzzle */
int
BuildSurface(surface)
   int surface;
{
   int i, j, k, index, face, done;
   int ilimit, jlimit, klimit;
   unsigned short srchval;

   done = 0;

   printf("... building surface %d\n", surface);

/* set for loop limits */
   switch(prob.numprocs) {
      case 1:
         ilimit = prob.size-1;	/* just shy of the opposite corners */
         jlimit = prob.size-1;
         klimit = prob.size-1;
         break;
      case 2:
         ErrPrint("BuildSurface: 2 PEs not supported", 0);
      case 4:
         ilimit = prob.size-1;	/* just shy of the bottom corner */
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      case 8:
         ilimit = prob.size/2;
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      default:
         ErrPrint("BuildSurface: invalid number of PEs", 0);
   }

/* build the specified surface */
   switch (surface) {
      case TOP:			/* build top surface */
         i = 0;
         while (!done) {
            for (j=1; j < jlimit; j++) {
               for (k=1; k < klimit; k++) {
                  srchval = solvecube[i][j][k-1].bk;	/* use front neighbor's back */
                  index = SearchList(plist, plistcnt, srchval, 1); /* search for 1 zero pcs */
                  while (index < 0) {	/* while not found */
/*                     EjectRandom();*/	/* eject random unused piece */
                     if (RemoteSearch(srchval, 1) < 0) 
                        ErrPrint("BuildSurface: remote search failed", 0);
                     index = SearchList(plist, plistcnt, srchval, 1); /* check again */
                  }

                  /* check if search value is on correct face, if not then fix it */
                  face = WhichFace(plist, index, srchval);	/* search value on correct face? */
                  if (face != FRO)
                     RotateElement(plist, index, srchval, FRO, face);	/* rotate it */

                  /* orient piece with respect to top outer surface */
                  while (plist[index].tp != 0)
                     RotateOnce(plist, index, 2);			/* rotate in roll */
   
                  CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
               } /* end for k */
            } /* end for j */
            done = 1;
         }
         break;
      case BOT:			/* build bottom surface */
         i = prob.size - 1;
         while (!done) {
            for (j=1; j < jlimit; j++) {
               for (k=1; k < klimit; k++) {
                  srchval = solvecube[i][j][k-1].bk;	/* use front neighbor's back */
                  index = SearchList(plist, plistcnt, srchval, 1); /* search for 1 zero pcs */
                  while (index < 0) {	/* while not found */
/*                     EjectRandom();*/	/* eject random unused piece */
                     if (RemoteSearch(srchval, 1) < 0) 
                        ErrPrint("BuildSurface: remote search failed", 0);
                     index = SearchList(plist, plistcnt, srchval, 1); /* check again */
                  }

                  /* check if search value is on correct face, if not then fix it */
                  face = WhichFace(plist, index, srchval);	/* search value on correct face? */
                  if (face != FRO)
                     RotateElement(plist, index, srchval, FRO, face);	/* rotate it */

                  /* orient piece with respect to bottom outer surface */
                  while (plist[index].bt != 0)
                     RotateOnce(plist, index, 2);			/* rotate in roll */
   
                  CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
               } /* end for k */
            } /* end for j */
            done = 1;
         }
         break;
      case FRO:			/* build front surface */
         k = 0;
         while (!done) {
            for (i=1; i < ilimit; i++) {
               for (j=1; j < jlimit; j++) {
                  srchval = solvecube[i][j-1][k].rt;	/* use left neighbor's right side */
                  index = SearchList(plist, plistcnt, srchval, 1); /* search for 1 zero pcs */
                  while (index < 0) {	/* while not found */
/*                     EjectRandom();*/	/* eject random unused piece */
                     if (RemoteSearch(srchval, 1) < 0) 
                        ErrPrint("BuildSurface: remote search failed", 0);
                     index = SearchList(plist, plistcnt, srchval, 1); /* check again */
                  }

                  /* check if search value is on correct face, if not then fix it */
                  face = WhichFace(plist, index, srchval);	/* search value on correct face? */
                  if (face != LFT)
                     RotateElement(plist, index, srchval, LFT, face);	/* rotate it */

                  /* orient piece with respect to front outer surface */
                  while (plist[index].fr != 0)
                     RotateOnce(plist, index, 1);			/* rotate in pitch */
   
                  CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
               } /* end for j */
            } /* end for i */
            done = 1;
         }
         break;
      case LFT:			/* build left surface */
         j = 0;
         while (!done) {
            for (i=1; i < ilimit; i++) {
               for (k=1; k < klimit; k++) {
                  srchval = solvecube[i][j][k-1].bk;	/* use front neighbor's back */
                  index = SearchList(plist, plistcnt, srchval, 1); /* search for 1 zero pcs */
                  while (index < 0) {	/* while not found */
/*                     EjectRandom();*/	/* eject random unused piece */
                     if (RemoteSearch(srchval, 0) < 0) 
                        ErrPrint("BuildSurface: remote search failed", 0);
                     index = SearchList(plist, plistcnt, srchval, 1); /* check again */
                  }

                  /* check if search value is on correct face, if not then fix it */
                  face = WhichFace(plist, index, srchval);	/* search value on correct face? */
                  if (face != FRO)
                     RotateElement(plist, index, srchval, FRO, face);	/* rotate it */

                  /* orient piece with respect to left outer surface */
                  while (plist[index].lf != 0)
                     RotateOnce(plist, index, 2);			/* rotate in roll */
   
                  CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
               } /* end for j */
            } /* end for i */
            done = 1;
         }
         break;
      default:
         ErrPrint("BuildSurface: invalid surface specified", 0);
         break;
   }

   return(0);
} /* end of BuildSurface() */


/* BuildGuts - builds the guts of the puzzle */
int
BuildGuts()
{
   int i, j, k, index, face, done;
   int ilimit, jlimit, klimit;
   unsigned short srchval, matchingval;

   done = 0;

   printf("... building guts of puzzle\n");

/* set for loop limits */
   switch(prob.numprocs) {
      case 1:
         ilimit = prob.size-1;	/* just shy of the opposite corners */
         jlimit = prob.size-1;
         klimit = prob.size-1;
         break;
      case 2:
         ErrPrint("BuildSurface: 2 PEs not supported", 0);
      case 4:
         ilimit = prob.size-1;	/* just shy of the bottom corner */
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      case 8:
         ilimit = prob.size/2;
         jlimit = prob.size/2;
         klimit = prob.size/2;
         break;
      default:
         ErrPrint("BuildSurface: invalid number of PEs", 0);
   }

/* search list for gut elements - fill in this PEs region */
   while (!done) {
      for (i=1; i < ilimit; i++) {
         for (j=1; j < jlimit; j++) {
            for (k=1; k < klimit; k++) {
               srchval = solvecube[i][j][k-1].bk;	/* use front neighbor's back */
               index = SearchList(plist, plistcnt, srchval, 0); /* search for non zero pcs */
               while (index < 0) {	/* while not found */
/*                  EjectRandom();*/	/* eject random unused piece */
                  if (RemoteSearch(srchval, 0) < 0) 
                     ErrPrint("BuildGuts: remote search failed", 0);
                  index = SearchList(plist, plistcnt, srchval, 0); /* check again */
               }

               /* check if search value is on correct face, if not then fix it */
               face = WhichFace(plist, index, srchval);	/* search value on correct face? */
               if (face != FRO) {
                  RotateElement(plist, index, srchval, FRO, face); /* rotate it */
               }

               /* orient piece with respect to left neighbor */
               matchingval = ~solvecube[i][j-1][k].rt;
               while (plist[index].lf != matchingval) {
                  RotateOnce(plist, index, 2);			/* rotate in roll */
               }
   
               CopyElement(plist, index, solvecube, i, j, k); 	/* copy it */
            } /* end for k */
         } /* end for j */
      } /* end for i */
      done = 1;
   }

   return(0);
} /* end of BuildGuts() */


/* SearchList - searches list for element that has matching face value */
int
SearchList(list, listcnt, srchval, zerocnt)
   struct Element *list;
   int listcnt;
   unsigned short srchval;
   int zerocnt;
{
   int i, count;
   unsigned short matchingval;

   matchingval = ~srchval;
/*if (DEBUG==TRUE) printf("zcnt = %d, sval = %x, mval = %x\n", zerocnt, srchval, matchingval);*/

   for (i=0; i < listcnt; i++) {
      count = ZeroCount(list, i);

      if ((list[i].usedflag == 0) && (list[i].ejected == 0) && (zerocnt == count)) {

         if (srchval == 0x8000) {	/* found an unused corner? */
            if (DEBUG==TRUE) printf("search found unused corner\n");
            list[i].usedflag = 1;
            return(i);  
         }
             
         if ((list[i].tp == matchingval) || (list[i].bt == matchingval)
                || (list[i].lf == matchingval) || (list[i].rt == matchingval)
                || (list[i].fr == matchingval) || (list[i].bk == matchingval)) {
            list[i].usedflag = 1;
            return(i);
         } 
      }
   } /* end for i */

if (DEBUG==TRUE) printf("search for %x(%x), found no match\n", srchval, matchingval);

   return(-1);	/* matching element not found */
} /* end of SearchList() */


/* WhichFace - returns which face has matching value */
int
WhichFace(list, index, srchval)
   struct Element *list;
   int index;
   unsigned short srchval;
{
   unsigned short matchingval;

   matchingval = ~srchval;

   if (list[index].tp == matchingval) return(TOP);
   if (list[index].bt == matchingval) return(BOT);
   if (list[index].lf == matchingval) return(LFT);
   if (list[index].rt == matchingval) return(RGT);
   if (list[index].fr == matchingval) return(FRO);
   if (list[index].bk == matchingval) return(BCK);

   return(-1);	/* error, not found for some reason */
} /* end of WhichFace() */


/* RotateElement - rotates element's face values so that they are in desired state */
int
RotateElement(list, index, srchval, dface, cface)
   struct Element *list;
   int index;
   unsigned short srchval;
   int dface, cface;	/* desired face, current face */
{
   int direction;

/*if (DEBUG==TRUE) printf("srchval = %x, dface = %d, cface = %d\n", srchval, dface, cface);*/

/* determine direction of rotation */
   switch(dface) {
      case TOP:
          if ((cface==BOT) || (cface==FRO) || (cface==BCK))
             direction = 1;
          else 
             if ((cface==BOT) || (cface==LFT) || (cface==RGT))
                direction = 2;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      case BOT:
          if ((cface==TOP) || (cface==FRO) || (cface==BCK))
             direction = 1;
          else 
             if ((cface==LFT) || (cface==RGT))
                direction = 2;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      case LFT:
          if ((cface==FRO) || (cface==BCK))
             direction = 3;
          else 
             if ((cface==BOT) || (cface==TOP) || (cface==RGT))
                direction = 2;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      case RGT:
          if ((cface==FRO) || (cface==BCK))
             direction = 3;
          else 
             if ((cface==BOT) || (cface==TOP) || (cface==LFT))
                direction = 2;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      case FRO:
          if ((cface==BOT) || (cface==TOP) || (cface==BCK))
             direction = 1;
          else 
             if ((cface==LFT) || (cface==RGT))
                direction = 3;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      case BCK:
          if ((cface==BOT) || (cface==TOP) || (cface==FRO))
             direction = 1;
          else 
             if ((cface==LFT) || (cface==RGT))
                direction = 3;
             else
                ErrPrint("RotateElement: cface is invalid", 0);
          break;
      default:
          ErrPrint("RotateElement: dface is invalid", 0);
          break;
   }

/* rotate cube element until desired face matches current face */
   while(dface != WhichFace(list, index, srchval)) {
      RotateOnce(list, index, direction); /* should be max of 3 rotations */
   }

   return(0);
} /* end of RotateElement() */


/* RotateOnce - rotates element's face by 90 degrees in specified direction */
int
RotateOnce(list, index, dir)
   struct Element *list;
   int index;
   int dir;		/* direction of positive rotation (1,2, or 3) */
{
   short int temp;	/* temporary face value */

   switch(dir) {
      case 1:		/* pitch rotation - tp->bk->bt->fr->tp */
         temp = list[index].tp;
         list[index].tp = list[index].fr;
         list[index].fr = list[index].bt;
         list[index].bt = list[index].bk;
         list[index].bk = temp;
         break;
      case 2:		/* roll rotation - tp->rt->bt->lf->tp */
         temp = list[index].tp;
         list[index].tp = list[index].lf;
         list[index].lf = list[index].bt;
         list[index].bt = list[index].rt;
         list[index].rt = temp;
         break;
      case 3:		/* yaw rotation - fr->rt->bk->lf->fr */
         temp = list[index].fr;
         list[index].fr = list[index].lf;
         list[index].lf = list[index].bk;
         list[index].bk = list[index].rt;
         list[index].rt = temp;
         break;
      default:
         ErrPrint("RotateOnce: invalid direction specified", 0);
         break;
   }

   return(0);
} /* end of RotateOnce() */


/* CopyElement - copies specified element from list to specified cube location */
int
CopyElement(list, index, cube, i, j, k)
   struct Element *list;
   int index;
   struct Element ***cube;
   int i, j, k;
{
   cube[i][j][k].tp = list[index].tp;
   cube[i][j][k].bt = list[index].bt;
   cube[i][j][k].lf = list[index].lf;
   cube[i][j][k].rt = list[index].rt;
   cube[i][j][k].fr = list[index].fr;
   cube[i][j][k].bk = list[index].bk;

   list[index].usedflag = 1;		/* mark this element as used in solved cube */

   return(0);
} /* end of CopyElement() */


/* RemoteSearch - searches all other PEs for element with specified value */
int
RemoteSearch(srchval, zerocnt)
   unsigned short srchval;
   int zerocnt;
{
   int i;
   int pe_array[MAXPROCS-1];
   int command;
   int faces[6];
   long timevals[5];

/* pick search array order */
   switch(prob.IAmPEnum) {
      case 0:
         pe_array[0] = 1;
         pe_array[1] = 3;
         pe_array[2] = 2;
         pe_array[3] = 7;
         pe_array[4] = 5;
         pe_array[5] = 4;
         pe_array[6] = 6;
         break;
      case 1:
         pe_array[0] = 3;
         pe_array[1] = 2;
         pe_array[2] = 0;
         pe_array[3] = 4;
         pe_array[4] = 6;
         pe_array[5] = 5;
         pe_array[6] = 7;
         break;
      case 2:
         pe_array[0] = 1;
         pe_array[1] = 0;
         pe_array[2] = 3;
         pe_array[3] = 7;
         pe_array[4] = 5;
         pe_array[5] = 6;
         pe_array[6] = 4;
         break;
      case 3:
         pe_array[0] = 0;
         pe_array[1] = 2;
         pe_array[2] = 1;
         pe_array[3] = 6;
         pe_array[4] = 5;
         pe_array[5] = 4;
         pe_array[6] = 7;
         break;
      case 4:
         pe_array[0] = 5;
         pe_array[1] = 2;
         pe_array[2] = 3;
         pe_array[3] = 0;
         pe_array[4] = 1;
         pe_array[5] = 6;
         pe_array[6] = 7;
         break;
      case 5:
         pe_array[0] = 1;
         pe_array[1] = 6;
         pe_array[2] = 3;
         pe_array[3] = 4;
         pe_array[4] = 0;
         pe_array[5] = 2;
         pe_array[6] = 7;
         break;
      case 6:
         pe_array[0] = 7;
         pe_array[1] = 2;
         pe_array[2] = 4;
         pe_array[3] = 3;
         pe_array[4] = 5;
         pe_array[5] = 0;
         pe_array[6] = 1;
         break;
      case 7:
         pe_array[0] = 6;
         pe_array[1] = 5;
         pe_array[2] = 4;
         pe_array[3] = 3;
         pe_array[4] = 2;
         pe_array[5] = 1;
         pe_array[6] = 0;
         break;
      default:
         ErrPrint("RemoteSearch: unknown PE num", 0);
   }

/* search remotely using the chosen search order */
   for (i=0; i < (prob.numprocs - 1); i++) {
      if (pe_array[i] != prob.IAmPEnum) {	/* and not same as me */
if (DEBUG==TRUE) printf("searching remote PE%d for %x with %d zeros\n", 
                                             pe_array[i], srchval, zerocnt);
         SendCommand(SRCH, pe_array[i], srchval, zerocnt);
         if (read(srchpipe[0], pipebuf, BUFSIZE) < 0) {	/* wait for response from parent */
            ErrPrint("RemoteSearch: error during read of pipe", 0);
         }

if (DEBUG==TRUE) printf("msg recvd on pipe = %s\n", pipebuf);
         command = ParseCmdBuf(pipebuf, faces, timevals, 0);

         switch(command) {
            case SEND:
               plist[plistcnt].tp = faces[0];
               plist[plistcnt].bt = faces[1];
               plist[plistcnt].lf = faces[2];
               plist[plistcnt].rt = faces[3];
               plist[plistcnt].fr = faces[4];
               plist[plistcnt].bk = faces[5];
               plist[plistcnt].usedflag = 0;
               plist[plistcnt].surplus = 0;
               plist[plistcnt].ejected = 0;
               plistcnt++;
               return(0);
            case FAIL:
if (DEBUG==TRUE) printf("remote search of PE%d failed\n", pe_array[i]);
               break;
            default:
               ErrPrint("RemoteSearch: unknown msg recvd on pipe", 0);
         }
      }
      else
         ErrPrint("RemoteSearch: error in search order array", 0);
   }

   return(-1);	/* should have found it from another PE */
} /* end of RemoteSearch() */


/* MarkSurplus - determines which elements are surplus and marks them */
int
MarkSurplus(zcnt)
   int zcnt;
{
   int i;
   int count;

   for (i=0; i < plistcnt; i++) {
      count = ZeroCount(plist, i);
      if (zcnt == count) {  /* does this element have correct num of 0's */
         if ((plist[i].usedflag == 0) && (plist[i].ejected == 0)) {
            plist[i].surplus = 1;		/* yes, mark it as surplus */
         }
      }
   }

   return(0);
} /* end of MarkSurplus() */


/* EjectSurplus - sends surplus elements to random PEs and marks them ejected */
int
EjectSurplus(zcnt)
   int zcnt;		/* number of 0 valued faces to treat as surplus */
{
   int i, pe;		/* index, target pe */

if (DEBUG==TRUE) printf("... ejecting surplus, zerocnt = %d\n", zcnt);

   MarkSurplus(zcnt);	/* mark elements w/ zerocnt 0's as surplus */
 
   for (i=0; i < plistcnt; i++) {
      if (plist[i].surplus == 1) {	/* is this one surplus? */
         pe = myrandom(prob.numprocs);		/* pick random target */
         if (pe == prob.IAmPEnum) {
            pe = pe + 1;
            if (pe == prob.numprocs)		/* handle overflow */
               pe = 0;
         }

         plist[i].ejected = 1;			/* mark it ejected */
         plist[i].surplus = 0;			/* no longer surplus since ejected */
         SendElement(SEND, pe, plist, i);	/* send it to another PE */
      }
   }

   return(0);
} /* end of EjectSurplus() */


/* EjectRandom - ejects a random unused element from the list to a random PE */
int
EjectRandom()
{
   int index, done_eject, pe;

   done_eject = 0;

   while (!done_eject) {
      index = myrandom(plistcnt);		/* pick random element */
      if ((plist[index].usedflag == 0) && (plist[index].ejected == 0)) {
         pe = myrandom(prob.numprocs);		/* pick random target */
         if (pe == prob.IAmPEnum) {
            pe = pe + 1;
            if (pe == prob.numprocs)		/* handle overflow */
               pe = 0;
         }

if (DEBUG==TRUE) printf("... ejecting random element to PE%d\n", pe);

         plist[index].ejected = 1;			/* mark it ejected */
         SendElement(SEND, pe, plist, index);	/* send it to another PE */
         done_eject = 1;
      }
   }

   return(0);
} /* end of EjectRandom() */
