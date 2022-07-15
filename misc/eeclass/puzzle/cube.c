/************************************************************************
Cube Puzzle Solver for EE575 project.

Author:	Brian Lingard

File:	puzzle.c

Usage:	puzzle [-i listfile][-m or -s][-d n][-p n][-f n.n][-l logfile]

Options:
  -i file   default "cube.list"  input file name
  -m	    default              master processor
  -s                             slave processor
  -d n      default 8            size of cube
  -n n      default 1            number of processors
  -p n      default 1            this proc number
  -f n.n    default 0            decomposition factor
  -l file   default "log.out"    output log file

Compile string:    cc puzzle.c -O -o puzzle -lm

Revision History:
3.0     multiprocessor version                          1-Apr-1994
2.0	modified for list oriented processing		13-Mar-1994	
1.0	originated uniprocessor version			23-Jan-1994

************************************************************************/

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tcplib.h"	 	 /* my tcp library functions */
#include "random.h"		 /* random number functions */
#include "puzzle.h"        	 /* cube definitions and structures */

/* define some constants */
#define VERSION 3.0		/* current version number */
#define DEBUG 1			/* general debug flag */

#define MAXPROCS 8		/* maximum number of processors */
#define MAXARGS 12		/* max number of command line arguments */
#define MAXLISTLEN 8000		/* max length of element lists */
#define MAXSIZE 20		/* max number of sides of cube */

#define QLEN    10		/* max connection queue length */
#define BUFSIZE 4096
#define LINELEN 128

/* declare global variables */
struct ProcAddrs    procaddr[MAXPROCS]; /* array proc address entries */
struct Description  prob;	   	/* problem description */

struct Element ***initcube;	 	/* pointer to initial cube */
struct Element ***scramcube;	 	/* pointer to scrambled cube */
struct Element ***solvecube;	  	/* pointer to solved cube */
struct Element *initlist;            	/* pointer to input list */

struct Element *plist; 			/* pointer to PE's working list */
int  plistcnt=0;			/* number of elements in working list */

struct Element *dlist[MAXPROCS];	/* array of pointers to distribution lists */
int  dlistcnt[MAXPROCS];		/* array of elements counts for each dlist */

char init_cube_name[32];
char init_list_name[32];
char scram_cube_name[32];
char solve_cube_name[32];

long timearray[4];	 	 /* array of local time values */
long alltimes[MAXPROCS][4];	 /* array of all time values */
FILE *logfile;                   /* output log file pointer */
int  donesolving = 0;            /* all slaves are done solving flag */
int  stopflag = 0;               /* stop command recv'd flag */
int  pesdone = 0;		 /* lsb's indicate which pe's are done solving */
int  gottimes = -1;		 /* flag for whether all time reports are in */

int  pesocks[MAXPROCS];		 /* array of sockets descriptors for all PEs */

int srchpipe[2];		/* remote search pipe to child solver process */
char pipebuf[BUFSIZE];		/* search pipe recv buffer */
char success_msg[BUFSIZE];
char *fail_msg = "fail";

int  program_state = 99;	 /* program's current state (initially idle) */

#include "cubefunc.h"		 /* cube functions */
#include "cubeutil.h"            /* misc utility functions */

int reaper();

/** MAIN function **/
int 
main(argc, argv)
   int argc;
   char *argv[];
{
   int masterflag=1;		/* this program is the master */
   int inputflag=0;		/* input file specified */
   int i, ifactor;              /* index, integer decomp factor */
   int length;

   char format[BUFLEN];

   char *procrefname = "processor.table";
   char *ilistname = "cube.list";
   char *logfilename = "log.out";

   struct sockaddr_in fsin;	/* the address of a client */
   int alen;			/* length of client's address */
   int msock;			/* master server socket */
   int ssock;			/* slave server socket */

   myrandominit();

/* initialize problem to default values */
   prob.numprocs = 1;
   prob.size = 4;
   prob.dfactor = 0.0;
   prob.IAmPEnum = 0;

/* check command line arguments */
   switch(argc) {
     case 1:			/* use defaults */
        break;
     default:			/* check args and parse */
        if (argc > MAXARGS) {
           sprintf(format,"usage: gencube [-i listfile][-m|-s][-d n]\
[-n n][-p n][-f n.n][-l logfile]");
           ErrPrint(format, 0);
        }
        else {                  /* parse argument inputs */
           i = 1;
           while (i < argc) {
              switch(argv[i][1]) {	/* switch on dash option */
                 case 'i':
                    ilistname = argv[i+1];
                    i++;
                    inputflag = 1;
                    break;
                 case 'm':
                    break;
                 case 's':
                    masterflag = 0;
                    break;
                 case 'd':
                    if (inputflag == FALSE) {
                       prob.size = atoi(argv[i+1]);
                       if (prob.size > MAXSIZE) {
                          sprintf(format,"Main: size exceeds max of %d",MAXSIZE);
                          ErrPrint(format, 0);
                       }
                       i++;
                    }
                    else
                       ErrPrint("conflicting option specified",0);
                    break;
                 case 'n':
                    if (inputflag == FALSE) {
                       prob.numprocs = atoi(argv[i+1]);
                       if (prob.numprocs > MAXPROCS) {
                          sprintf(format,"numprocs exceeds max of %d",
                                                                MAXPROCS);
                          ErrPrint(format, 0);
                       }
                       i++;
                    }
                    else
                       ErrPrint("Main: conflicting option specified",0);
                    break;
                 case 'p':
                    prob.IAmPEnum = atoi(argv[i+1]);
                    if (prob.IAmPEnum >= MAXPROCS) {
                       ErrPrint("Main: PE num is invalid, too large",0);
                    }
                    if (prob.IAmPEnum != 0 && masterflag == TRUE) {
                       ErrPrint("Main: PE num is invalid, master must be PE0",0);
                    }
                    i++;
                    break;
                 case 'f':
                    prob.dfactor = atof(argv[i+1]);
                    ifactor = prob.dfactor * 100;
                    switch(ifactor) {
                       case 0:
                       case 25:
                       case 50:
                       case 75:
                       case 100:
                          break;
                       default:
                          ErrPrint("Main: invalid decomposition factor",0);
                    }
                    i++;
                    break;
                 case 'l':
                    logfilename = argv[i+1];
                    i++;
                    break;
                 default:
                    ErrPrint("Main: unknown option(s) specified",0);
              } /* end inner switch */
              i++;
           } /* end while */
        } /* end else */
     break;
   } /*end outer switch */

/* open log output file */
   logfile = fopen(logfilename,"w");
   if (logfile == (FILE *) NULL) {
      sprintf(format,"Main: could not open %s as log file",logfilename);
      ErrPrint(format, 0);
   }

/* set up search comm pipe */
   if (pipe(srchpipe) < 0) {
      ErrPrint("main: error establishing pipe", 0);
   }

/* setup debug output file names */
   sprintf(init_cube_name, "cube%d.init", prob.IAmPEnum);
   sprintf(init_list_name, "list%d.init", prob.IAmPEnum);
   sprintf(scram_cube_name,"cube%d.scram", prob.IAmPEnum);
   sprintf(solve_cube_name,"cube%d.solve", prob.IAmPEnum);

/* measure begin time */
   MarkTime(START);
   OutputStartupMsg();	
   if (masterflag == TRUE)
      program_state = START;

/* Allocate memory for cube and list structures */
   initcube  = DimCube(prob.size);
   scramcube = DimCube(prob.size);
   solvecube = DimCube(prob.size);

   length = prob.size * prob.size * prob.size;
   initlist = DimList(length);
   plist = DimList(MAXLISTLEN);

/*   for (i=0; i < prob.numprocs; i++) {*/
/*      dlist[i] = DimList(MAXLISTLEN);*/
/*      dlistcnt[i] = 0;*/
/*   }*/

/* create master socket to receive commands */
   if (prob.numprocs > 1) {
      GetProcAddrs(procrefname);
      msock = passiveTCP(procaddr[prob.IAmPEnum].port, QLEN);
   }
   (void) signal(SIGCLD, reaper);	/* cleanup zombies */

/* perform following functions only if master PE */
   if (masterflag == TRUE) {	/* this PE is master */
/*      InitPESocks();*/

      if (inputflag == TRUE)
         ReadList(ilistname);		/* input cube list from file */
      else {
         InitCube();                     /* else, create new cube */
         CubeToList(initcube, initlist);
         OutputCube(initcube, init_cube_name);	/* write out initial cube to file */
      }

      if (prob.numprocs > 1) {	/* multiple PEs */
         for (i=1; i < prob.numprocs; i++)
            SendCommand(START,i);	/* send START command to each PE */

         DistributeCube();		/* distribute cube to other PEs */
        
         for (i=1; i < prob.numprocs; i++)
            SendCommand(SOLVE,i);	/* send SOLVE command to each PE */

         program_state = SOLVE;

/* initiate master's solving and command handling */
         switch(fork()) {
            case -1:	/* couldn't fork, for some reason */
               errexit("fork: %s\n", sys_errlist[errno]);
            case 0:	/* child process */
               close(srchpipe[1]);	/* close write side of pipe */
               OutputList(plist, plistcnt, init_list_name);
               SolveCube();		/* start solving cube puzzle */
               SignalChildDone();	/* signal parent, child is done solving */
               exit(0);
            default:	/* parent process */
               close(srchpipe[0]);	/* close read side of pipe */
               while(!donesolving) { /* recv cmds 'til all slaves done */ 
                  alen = sizeof(fsin);
                  ssock = accept(msock, (struct sockaddr_in *)&fsin, &alen);
                  if (ssock < 0) {
                     if (errno == EINTR)
                        continue;
                     errexit("accept: %s\n",sys_errlist[errno]);
                  }
                  (void) HandleCommand(ssock, masterflag); /* as master */
                  /*(void) CleanUp();*/	/* reject elements if done solving */

                  if (((prob.numprocs == 4) && (pesdone == SLAVES4DONE))
                          || ((prob.numprocs == 8) && (pesdone == SLAVES8DONE))) {
                     for (i=1; i<prob.numprocs; i++) {
                        SendCommand(STOP,i);	/* send STOP command to each PE */
                     }
                     donesolving = 1;
                     printf("... all PE's are finished, exitting\n");
                  }
                  (void) close(ssock);
               }
               break;  
         } /* end of switch fork() */
         OutputStats();	/* output time statistics to logfile */
         FreeCube(initcube);
         FreeCube(scramcube);
         FreeCube(solvecube);
         FreeList(initlist);
         FreeList(plist);
         (void) close(msock);
      }
      else {	/* single PE */
         ScrambleCube();		 /* scramble cube if only one PE */
         CubeToList(scramcube, plist);   /* copy cube to list */
         SolveCube();			 /* begin solving puzzle */
         TestCubes(initcube,solvecube);	 /* test solution to puzzle */
         OutputStats();
      }
   } /* end if master */

/* perform following only if slave PE */
   else {                        /* this PE is slave */
      if (prob.numprocs > 1) {
         printf("Slave Cube Solver running as PE%d ...\n", prob.IAmPEnum);

         while(!stopflag) {		/* recv cmds 'til stop command */ 
            alen = sizeof(fsin);
            ssock = accept(msock, (struct sockaddr_in *)&fsin, &alen);
            if (ssock < 0) {
               if (errno == EINTR)
                  continue;
               errexit("accept: %s\n",sys_errlist[errno]);
            }
            (void) HandleCommand(ssock, masterflag);  /* as slave */
            /*(void) CleanUp();*/		/* reject elements if done solving */
            (void) close(ssock);
         }

/*         ClosePESocks();*/
         (void) close(msock);
      }
      else {
         ErrPrint("Main: single PE cannot be slave", 0);
      }
   } /* end else slave */
} /* end of main() */


/* InitPESocks - open connection of sockets to other PEs */
int
InitPESocks()
{
   int pe;

   for (pe = 0; pe < prob.numprocs; pe++) {
      if (pe != prob.IAmPEnum) {	/* connect, but not to self */
         pesocks[pe] = connectTCP(procaddr[pe].host, procaddr[pe].port);
      }
   }

   return(0);
} /* end of InitPESocks() */

 
/* ClosePESocks - closes all opened sockets to remote PEs */
int
ClosePESocks()
{
   int pe;

   for (pe = 0; pe < prob.numprocs; pe++) {
      if (pe != prob.IAmPEnum) {
 
/* shutdown connection in both directions */
         if (shutdown(pesocks[pe], 2) == -1)
            errexit("shutdown failed: %s\n", sys_errlist[errno]);

/* close connection to remote PE */
         if (close(pesocks[pe]) == -1)
            errexit("close failed: %s\n", sys_errlist[errno]);
      }
   }

   return(0);
} /* end of ClosePESocks() */


/* SendCommand - sends specified command to specified PE */
int
SendCommand(command, pe, parm1, parm2)
   int command;		/* command to be sent */
   int pe;		/* target PE */
   unsigned short parm1;  /* optional parameter 1 */
   int parm2;		/* optional parameter 2 */
{
   char sbuf[LINELEN];	/* send buffer */
   char rbuf[LINELEN];	/* recv buffer */
   int  s;		/* socket */
   int  n, i;		/* read count, index */
   int  outchars, inchars;  /* characters sent and received */
   int  retcmd;		/* returned command code */
   int  faces[6];	/* dummy array for faces return values */
   long timevals[4];	/* time values returned from slave */
   int err;

   err = 0;

/* connect to target PE as client */
   s = connectTCP(procaddr[pe].host, procaddr[pe].port);

/* form command string */
   for (i=0; i < LINELEN; i++) {	/* clear command string buffer */
      sbuf[i] = '\0';
      rbuf[i] = '\0';
   }

   if (FormCmdString(command, sbuf, parm1, parm2) < 0)
      ErrPrint("SendCommand: unknown command specified", 0);

   if (DEBUG==TRUE) printf("cmd sent: %s to PE%d\n", sbuf, pe);

/* send command to target PE */
   sbuf[LINELEN] = '\0';		/* ensure line null-term'ed */
   outchars = strlen(sbuf);		/* number of chars to send */
   (void) write(s, sbuf, outchars);	/* send command string */

   if (DEBUG==TRUE) fprintf(logfile,"sent cmd %s to PE%d\n",sbuf,pe);

/* read back acknowledgement */
/*   for (inchars = 0; inchars < outchars; inchars+=n) {*/
/*      n = read(s, &rbuf[inchars], outchars - inchars);*/
/*      if (n < 0)*/
/*         errexit("socket read failed: %s\n", sys_errlist[errno]);*/
/*   }*/
/*   if (DEBUG==TRUE) printf("cmd recv: %s\n", rbuf);*/

/* check acknowledge against command sent */

/*   retcmd = ParseCmdBuf( rbuf, faces, timevals, 1);*/

/*   if (retcmd != command)*/
/*      ErrPrint("SendCommand: cmd acknowledge is incorrect", 0);*/

/* if command was a remote search, handle if it was successful */
/*   if (retcmd == SRCH) {*/
/*      if ((faces[0] == 99) && (faces[1] == 99) && (faces[2] == 99)*/
/*              && (faces[3] == 99) && (faces[4] == 99) && (faces[5] == 99)) */
/*         err = 99;*/
/*      else {*/
/*         if (plistcnt < MAXLISTLEN) {*/
/*            plist[plistcnt].tp = faces[0];*/
/*            plist[plistcnt].bt = faces[1];*/
/*            plist[plistcnt].lf = faces[2];*/
/*            plist[plistcnt].rt = faces[3];*/
/*            plist[plistcnt].fr = faces[4];*/
/*            plist[plistcnt].bk = faces[5];*/
/*            plist[plistcnt].usedflag = 0;*/
/*            plist[plistcnt].surplus = 0;*/
/*            plist[plistcnt].ejected = 0;*/
/*            plistcnt++;*/
/*         }*/
/*      }*/
/*   }*/

/* shutdown connection in both directions */
   if (shutdown(s, 2) == -1)
      errexit("shutdown failed: %s\n", sys_errlist[errno]);

/* close connection to remote PE */
   if (close(s) == -1)
      errexit("close failed: %s\n", sys_errlist[errno]);

   return(err);
} /* end of SendCommand() */


/* HandleCommand - handles receipt of command */
int
HandleCommand(fd, master)
   int fd;		/* input socket descriptor */
   int master;		/* master flag */
{
   char cbuf[BUFSIZE];	/* command recvd buffer */
   char rbuf[BUFSIZE];	/* acknowledge/response buffer */
   char *buf = "";
   char *timestr = "";
   int  i, cc;
   int  index, zerocnt;
   unsigned short srchval;
   int  maskdone;
   int  frompe;		/* from PE num */
   int  command;	/* command */
   int  faces[6];	/* face values */
   long timevals[5];	/* time values */

/* clear command string and ack string buffers */
   for (i=0; i < BUFSIZE; i++) {
      cbuf[i] = '\0';
      rbuf[i] = '\0';
   }

/* read command */
   cc = read(fd, cbuf, sizeof(cbuf));
   if (cc < 0)
      errexit("handlecommand read: %s\n", sys_errlist[errno]);

/*   logcmd(logfile, cbuf);*/
/*   if (DEBUG==TRUE) printf("command recvd: %s\n", cbuf);*/

/* handle command received */
   command = ParseCmdBuf(cbuf, faces, timevals, 0);

   if (master==TRUE) {	/* handle as master PE */
      switch(command) {
         case SEND:		/* store element faces in new list */
            strncpy(rbuf, cbuf, cc);
            if (plistcnt < MAXLISTLEN) {
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
               if (program_state == SOLVE) {/* send success msg to child solver */
                  sprintf(success_msg, "send %d %d %d %d %d %d ", faces[0], faces[1],
                                           faces[2], faces[3], faces[4], faces[5]);
/*                  printf("new element recvd, sending msg %s down pipe\n", success_msg);*/
                  write(srchpipe[1], success_msg, sizeof(success_msg));
               }
            }
            else
               ErrPrint("HandleCommand: exceeded max plistcnt", 0);
            break;
         case DONE:		/* mark which slave has finished */
            strncpy(rbuf, cbuf, cc);
            maskdone = 1 << faces[0];		/* form done mask */
            pesdone = pesdone | maskdone;	/* OR it with current flags */
            break;
         case SRCH:		/* remote search query */
            frompe = faces[0];
if (DEBUG==TRUE) printf("handling remote search from PE%d\n", frompe);
            srchval = faces[1];
            zerocnt = faces[2];
            index = SearchList(plist, plistcnt, srchval, zerocnt);
            if (index >= 0) {	/* found match, return element values */	
               SendElement(SEND, frompe, plist, index);
            }
            else
               SendCommand(FAIL, frompe, 0, 0);
            break;
         case FAIL:		/* remote search failed */
            strncpy(rbuf, cbuf, cc);
/*            printf("search failed, sending msg %s down pipe\n", fail_msg);*/
            write(srchpipe[1], fail_msg, sizeof(fail_msg));
            break;
         case RTIME:		/* returned time values from slave */
            strncpy(rbuf, cbuf, cc);
            gottimes++;
            frompe = (int) timevals[0];
            for (i=1; i<5; i++)
               alltimes[frompe][i-1] = timevals[i];	
            break;
         default:
            ErrPrint("HandleCommand: inappropriate or unknown cmd recvd by master", 0);
      }
   }
   else {		/* handle as slave PE */
      switch(command) {
         case START:
            strncpy(rbuf, cbuf, cc);
            program_state = START;
            break;
         case SEND:		/* store element faces in new list */
            strncpy(rbuf, cbuf, cc);
            if (plistcnt < MAXLISTLEN) {
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
               if (program_state == SOLVE) { /* send success msg to child solver */
                  sprintf(success_msg, "send %d %d %d %d %d %d ", faces[0], faces[1],
                                        faces[2], faces[3], faces[4], faces[5]);
/*                  printf("new element recvd, sending msg %s down pipe\n", success_msg);*/
                  write(srchpipe[1], success_msg, sizeof(success_msg));
               }
            }
            else
               ErrPrint("exceeded max plistcnt", 0);
            break;
         case SOLVE:
            strncpy(rbuf, cbuf, cc);
            OutputList(plist, plistcnt, init_list_name);
            program_state = SOLVE;
            switch(fork()) {
               case -1:	/* couldn't fork, for some reason */
                  errexit("fork: %s\n", sys_errlist[errno]);
               case 0:	/* child process */
                  SolveCube();		/* start solving cube puzzle */
                  SignalSlaveDone();	/* signal master PE done solving */
                  exit(0);
               default:	/* parent process */
                  break;
            }
            break;
         case DONE:		/* should never recv this command as slave */
            strncpy(rbuf, cbuf, cc);
            break;
         case STOP:		/* set stopflag to TRUE */
            strncpy(rbuf, cbuf, cc);
            stopflag = 1;
            program_state = STOP;
            printf("... PE%d is exitting!!\n", prob.IAmPEnum);
            break;
         case SRCH:		/* remote search query */
            frompe = faces[0];
if (DEBUG==TRUE) printf("handling remote search from PE%d\n", frompe);
            srchval = faces[1];
            zerocnt = faces[2];
            index = SearchList(plist, plistcnt, srchval, zerocnt);
            if (index >= 0) {	/* found match, return element values */	
               SendElement(SEND, frompe, plist, index);
            }
            else
               SendCommand(FAIL, frompe, 0, 0);
            break;
         case FAIL:		/* remote search failed */
            strncpy(rbuf, cbuf, cc);
/*            printf("search failed, sending msg %s down pipe\n", fail_msg);*/
            write(srchpipe[1], fail_msg, sizeof(fail_msg));
            break;
         case QTIME:		/* time query, return time values */
            strncpy(rbuf, cbuf, cc);
            SendCommand(RTIME, 0, 0, 0);  /* send them to PE0 as new command */
            break;
         case RTIME:		/* should never recv this command as slave */
            strncpy(rbuf, cbuf, cc);
            break;
         case ABORT:		/* kill all child processes and exit */
            strncpy(rbuf, cbuf, cc);
            program_state = ABORT;
            printf("ABORT RECVD !!!!!!\n");
            break;
         default:
            ErrPrint("HandleCommand: unknown command recvd by slave PE", 0);
      }
   }

/* echo command as ack */
/*   if (DEBUG==TRUE) printf("command ackd: %s\n", rbuf);*/

/*   if (write(fd, rbuf, cc) < 0)*/
/*      errexit("handlecommand write: %\n", sys_errlist[errno]);*/

   return(0);
} /* end of HandleCommand() */


/* SendElement - send cube element to specified PE */
int
SendElement(command, pe, list, index)
   int command;		/* command to be sent */
   int pe;		/* target PE */
   struct Element *list; /* pointer to element list */
   int index;		/* index to element in list */
{
   char sbuf[LINELEN];	/* send buffer */
   char rbuf[LINELEN];	/* recv buffer */
   int  s;		/* socket */
   int  n, i;		/* read count, index */
   int  outchars, inchars;  /* characters sent and received */
   int  retcmd;		/* returned command code */
   int  faces[6];	/* dummy array for faces return values */
   long timevals[4];	/* time values returned from slave */
   
/* connect to target PE as client */
   s = connectTCP(procaddr[pe].host, procaddr[pe].port);

/* form command string */
   for (i=0; i < LINELEN; i++) {	/* clear command string buffer */
      sbuf[i] = '\0';
      rbuf[i] = '\0';
   }

   if (command == SEND)
      sprintf(sbuf, "send %d %d %d %d %d %d ", 
                list[index].tp, list[index].bt, list[index].lf, 
                list[index].rt, list[index].fr, list[index].bk);
   else
      ErrPrint("SendElement: send command not specified", 0);

/*   if (DEBUG==TRUE) printf("cmd sent: %s\n", sbuf);*/

/* send command to target PE */
   sbuf[LINELEN] = '\0';		/* ensure line null-term'ed */
   outchars = strlen(sbuf);		/* number of chars to send */
   (void) write(s, sbuf, outchars);	/* send command string */

/*   if (DEBUG==TRUE) fprintf(logfile,"sent cmd %s to PE%d\n",sbuf,pe);*/

/* read back acknowledgement */
/*   for (inchars = 0; inchars < outchars; inchars+=n) {*/
/*      n = read(s, &rbuf[inchars], outchars - inchars);*/
/*      if (n < 0)*/
/*         errexit("socket read failed: %s\n", sys_errlist[errno]);*/
/*   }*/
/*   if (DEBUG==TRUE) printf("cmd recv: %s\n", rbuf);*/

/* check acknowledge against command sent */

/*   retcmd = ParseCmdBuf( rbuf, faces, timevals, 1);*/

/*   if (retcmd != command)*/
/*      ErrPrint("SendElement: cmd acknowledge is incorrect", 0);*/

/* shutdown connection in both directions */
   if (shutdown(s, 2) == -1)
      errexit("shutdown failed: %s\n", sys_errlist[errno]);

/* close connection to remote PE */
   if (close(s) == -1)
      errexit("close failed: %s\n", sys_errlist[errno]);

   return(0);
} /* end of SendElement() */


/* SendList - send cube element distribution list to specified PE */
int
SendList(command, pe)
   int command;		/* command to be sent */
   int pe;		/* target PE */
{
   char sbuf[LINELEN];	/* send buffer */
   int  s;		/* socket */
   int  n, i;		/* read count, index */
   int  outchars;  	/* characters sent and received */
   struct Element *list;

/* connect to target PE as client */
   s = connectTCP(procaddr[pe].host, procaddr[pe].port);

/* clear command string buffer */
   for (i=0; i < LINELEN; i++)
      sbuf[i] = '\0';

   list = dlist[pe];	/* copy pointer to distribution list */

if (DEBUG==TRUE) printf("sending list to PE%d\n", pe);

/* send all elements in specified PE's distribution list to that PE */
   for (i=0; i < dlistcnt[pe]; i++) {

      if (command == SEND)
         sprintf(sbuf, "send %d %d %d %d %d %d ", 
                list[i].tp, list[i].bt, list[i].lf, 
                list[i].rt, list[i].fr, list[i].bk);
      else
         ErrPrint("SendList: send command not specified", 0);

if (DEBUG==TRUE) printf("sending cmd: %s\n", sbuf);

      sbuf[LINELEN] = '\0';		/* ensure line null-term'ed */
      outchars = strlen(sbuf);		/* number of chars to send */
      if (write(s, sbuf, outchars) == -1);	/* send command string */
         errexit("SendList write: %s\n", sys_errlist[errno]);
   }

/* shutdown connection in both directions */
   if (shutdown(s, 2) == -1)
      errexit("SendList: shutdown failed: %s\n", sys_errlist[errno]);

/* close connection to remote PE */
   if (close(s) == -1)
      errexit("SendList: close failed: %s\n", sys_errlist[errno]);

   return(0);
} /* end of SendList() */



/* SignalSlaveDone - signal master PE that slave is done solving */
int
SignalSlaveDone()
{
   long einit,exmit,esolv,etotal;

   printf("Finished Solving Puzzle ...\n");

   MarkTime(DONE);
   program_state = DONE;

   fprintf(logfile,"Time Statistics:\n");
   fprintf(logfile,"  begin time = %s", ctime(&timearray[START]));
   fprintf(logfile,"  send time  = %s", ctime(&timearray[SEND]));
   fprintf(logfile,"  solve time = %s", ctime(&timearray[SOLVE]));
   fprintf(logfile,"  done time  = %s", ctime(&timearray[DONE]));

   einit = timearray[SEND] - timearray[START];
   exmit = timearray[SOLVE] - timearray[SEND];
   esolv = timearray[DONE] - timearray[SOLVE];
   etotal = timearray[DONE] - timearray[START];
   fprintf(logfile,"\n  elapsed init time  = %d\n", einit);
   fprintf(logfile,"  elapsed xmit time  = %d\n", exmit);
   fprintf(logfile,"  elapsed solve time = %d\n", esolv);
   fprintf(logfile,"  elapsed total time = %d\n", etotal);

   printf("  elapsed solve time = %d\n", esolv);
   printf("  elapsed total time = %d\n", etotal);

   SendCommand(RTIME, 0, 0, 0);  /* send times to PE0 as new command */
   SendCommand(DONE, 0, 0, 0);	/* send done command to master PE */

   return(0);
} /* end of SignalSlaveDone() */


/* SignalChildDone - signal parent process that child process is done solving */
int
SignalChildDone()
{
   long einit,exmit,esolv,etotal;

   printf("Finished Solving Puzzle ...\n");

   MarkTime(DONE);
   program_state = DONE;

   fprintf(logfile,"Time Statistics:\n");
   fprintf(logfile,"  begin time = %s", ctime(&timearray[START]));
   fprintf(logfile,"  send time  = %s", ctime(&timearray[SEND]));
   fprintf(logfile,"  solve time = %s", ctime(&timearray[SOLVE]));
   fprintf(logfile,"  done time  = %s", ctime(&timearray[DONE]));

   einit = timearray[SEND] - timearray[START];
   exmit = timearray[SOLVE] - timearray[SEND];
   esolv = timearray[DONE] - timearray[SOLVE];
   etotal = timearray[DONE] - timearray[START];
   fprintf(logfile,"\n  elapsed init time  = %d\n", einit);
   fprintf(logfile,"  elapsed xmit time  = %d\n", exmit);
   fprintf(logfile,"  elapsed solve time = %d\n", esolv);
   fprintf(logfile,"  elapsed total time = %d\n", etotal);

/* send signal to parent here !!! */
   SendCommand(RTIME, 0, 0, 0);  /* send times to PE0 as new command */
   SendCommand(DONE, 0, 0, 0);	/* send done command to master PE */

   return(0);
} /* end of SignalChildDone() */


/* CleanUp - handles automatic rejection of cube elements when already done solving */
int
CleanUp()
{
/*if (DEBUG==TRUE) printf("prog state is %d\n", program_state);*/

   if ((program_state == DONE) && (prob.dfactor > 0.0)) {
      EjectSurplus(3);
      EjectSurplus(2);
      EjectSurplus(1);
      EjectSurplus(0);
   }

   return(0);
} /* end of CleanUp() */


/* logcmd() - log commands received in log file */
int
logcmd(lf, cmd)
   FILE *lf;
   char *cmd;
{
   long timevar;

   time(&timevar);
   fprintf(lf,"%s received at %s", cmd, ctime(&timevar));
   return 0;
} /* end of logcmd() */


/* reaper - clean up zombie children */
int
reaper()
{
   union wait  status;
   
   program_state = DONE;

   while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0) {
      /* empty */
   }
}
