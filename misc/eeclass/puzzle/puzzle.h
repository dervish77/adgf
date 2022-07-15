/****************************************************************
* File:	   puzzle.h	      Author:  Brian Lingard	        *
*			                                        *
* Rev 3.0  rewritten from scratch               1-Apr-1994      *
* Rev 2.1  added DimList, FreeList, ErrPrint  	13-Mar-1994	*
* Rev 2.0  reduced file size of headers		8-Mar-1994	*
* Rev 1.0  originated				6-Feb-1994	*
*				                                *
*****************************************************************/

#define BUFLEN 80	/* buffer length for char line */

#define TRUE 1
#define FALSE 0
#define FOUND 1
#define NOTFOUND 0
#define ERROR -1
#define NOERROR 0
#define TIMEOUT 10000		/* max number of search iterations */
#define SEARCH_TIMEOUT 30	/* num seconds max time to wait for remote search */
#define SLAVES4DONE 0x0f
#define SLAVES8DONE 0xff

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

/* define interprocessor command types */
#define START 0		/* start and prepare to revc cube elements */
#define SEND 1		/* send cube element data */
#define SOLVE 2		/* begin solving algorithm */
#define DONE 3		/* finished solving puzzle */
#define STOP 4		/* stop program */
#define SRCH 5		/* perform remote search */
#define FAIL 6		/* remote search failed */
#define QTIME 7		/* query for all times */
#define RTIME 8		/* return all times */
#define ABORT 9		/* abort execution */


/* declare typedefs for structures used */

typedef struct Element {	/* element of cube puzzle */
	unsigned short tp;
	unsigned short bt;
	unsigned short lf;
	unsigned short rt;
	unsigned short fr;
	unsigned short bk;
	int usedflag;		/* used as source flag */
   	int surplus;      	/* surplus element flag */
        int ejected;		/* element has been ejected */
};

typedef struct Description {	/* description of current problem */
	int size;
        float dfactor;
	int numprocs;
	int distcnt[8];
        int IAmPEnum;
};

typedef struct ProcAddrs{     /* processor addr table entry */
   int  procid;
   char host[11];
   char port[11];
};
