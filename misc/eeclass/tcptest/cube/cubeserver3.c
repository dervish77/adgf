/* cubeserver3.c - server, handlecommand, logcmd, main */

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

#include "tcplib.h"

#define QLEN         5     /* maximum connection queue length */
#define BUFSIZE      4096

int reaper();
int killserver();

int pid;                 /* pid of child server process */



/* errexit - print an error message and exit */

#include <varargs.h>

static int
errexit( format, va_alist)
char *format;
va_dcl
{
   va_list args;
   va_start(args);
   _doprnt(format, args, stderr);
   va_end(args);
   exit(1);
}


/* main - iterative TCP server for cubeserver service */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char     *port;               /* service name or port number */
   int      msock;               /* master server socket */
   FILE     *logfile;
   int      status;

   switch (argc) {
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: cubeserver3 <port>\n");
         exit(1);
   }

   logfile = fopen("logcmd.out", "w");
   
   msock = passiveTCP(port, QLEN);
   
   (void) signal(SIGCHLD, reaper);      /* cleanup zombies */
   (void) signal(SIGUSR1, killserver);
   
   switch(pid = fork()) {
      case -1:     /* couldn't fork for some reason */
         errexit("fork error: %s\n", sys_errlist[errno]);
      case 0:      /* child server process */
         (void) server( msock, logfile);
         exit(0);
      default:     /* parent process */
         printf("spawned off child server w/pid=%d\n", pid);
         (void) wait(&status);
         exit(0);
   }
}

/* server() - general iterative server */
server(msock, logfile)
   int msock;
   FILE *logfile;
{
   struct   sockaddr_in fsin;    /* the address of a client */
   int      alen;                /* length of client's address */
   int      ssock;               /* slave server socket */
   int      ppid;                /* parent's pid */
   int      code;

   while (1) {
      ppid = getppid();
      alen = sizeof(fsin);
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0) {
         if (errno == EINTR)
            continue;
         errexit("accept: %s\n", sys_errlist[errno]);
      }
      code = handlecommand(ssock, logfile);
      (void) close(ssock);
      if (code > 0)
         (void) kill(ppid, SIGUSR1);
   }
} /* end of server() */


/* handlecommand - echo commands received */
int
handlecommand(fd, logfile)
   int fd;
   FILE *logfile;
{
   char  buf[BUFSIZE];
   int   cc, code=0;       /* char count, return code */
   
   cc = read(fd, buf, sizeof(buf));                 /* read command */
   if (cc < 0)
      errexit("echo read: %s\n", sys_errlist[errno]);
   logcmd(logfile, buf);
   if (write(fd, buf, cc) < 0)                     /* echo command */
      errexit("echo write: %s\n", sys_errlist[errno]);

   if (strcmp(buf, "stop") == 0)
      code = 1;

   return(code);
} /* end of handlecommand() */


/* logcmd() - log commands recieved in log file */
int
logcmd(logfile, cmd)
   FILE *logfile;
   char *cmd;
{
   long timevar;

   time(&timevar);
   fprintf(logfile,"%s received at %s", cmd, ctime(&timevar));
   return 0;
} /* end of logcmd() */


/* reaper - clean up zombie children */
int
reaper()
{
/*
   union wait  status;
*/
   
/*
   while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0) 
   {

   }
*/
}


/* killserver - kills child server process */
int
killserver()
{
   printf("trapped SIGUSR1 from child server\n");
   (void) kill(pid, SIGKILL);
}
